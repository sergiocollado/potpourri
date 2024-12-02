// SPDX-License-Identifier: GPL-2.0

/*
 * mkfs.c - this is the SPFS mkfs command. It writes the following structures
 *          to disk:
 *
 *          - superblock
 *          - root inode with entries for ".", ".." and "lost+found"
 *          - lost+found inode with entries for "." and ".." 
 *
 * Copyright 2023-2024 Steve D. Pate
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <linux/fs.h>
#include <sys/stat.h>
#include "../kern/spfs.h"


/**
 * S: NOTE: all the functions start at the beginning of the
 * line, so if you want to get to main(), you search /^main
 */


int devfd;

/*
 * fill_in_inode() - write an inode to disk. We will in the fields of
 *                   the disk inode, lseek to the right location on
 *                   disk and write it. The first inode is stored at
 *                   SP_INODE_BLOCK. Since inodes 0 and 1 are not used,
 *                   the root inode (2) is stored at block SP_INODE_BLOCK + 2
 *                   and so on. Inode fields not shown are filled in by
 *                   the caller.
 */

void
fill_in_inode(struct sp_inode *inode, int type, int uid, int gid,
			  int nlink, int inum)
{
	time_t	tm;

	time(&tm);
	inode->i_atime = (__u32)tm;
	inode->i_mtime = (__u32)tm;
	inode->i_ctime = (__u32)tm;
	inode->i_uid = (__u32)uid;
	inode->i_gid = (__u32)gid;
	inode->i_mode = (__u32)type;
	inode->i_nlink = (__u32)nlink;

	// S: seek to where the inode has to be written
	lseek(devfd, (SP_INODE_BLOCK + inum) * SP_BSIZE, SEEK_SET);
	// S: write to disk
	write(devfd, (char *)inode, sizeof(struct sp_inode));
}

/*
 * main() - Quite simple. Write the superblock, fill in inode structures,
 *          write them to disk and then write relevant blocks which are the
 *          directory entries for root and lost+found.
 */

int
main(int argc, char **argv)
{
        struct sp_dirent        dir;
        struct sp_superblock    sb;
        struct sp_inode         inode;
        time_t                  tm;
        off_t                   nsectors = SP_MAXBLOCKS;
        int                     error, i;
        int                     map_blks, inum;
        char                    block[SP_BSIZE];

	//S: Check if the device is passed as an argument
        if (argc != 2) {
                fprintf(stderr, "SPFS mkfs: Need to specify device\n");
                return(1);
        }
	//S: Check if the device can be open for writing
	//note, that it is not checked if the device is in use,
	//it should be done
        devfd = open(argv[1], O_WRONLY);
        if (devfd < 0) {
                fprintf(stderr, "SPFS mkfs: Failed to open device\n");
                return(1);
        }
	// S: Next is seek where the end of the file system is.
	//#define SP_BSIZE 2048 - defined at kern/spfs.h
I	//nsectors = SP_MAXBLOCKS
	error = lseek(devfd, (off_t)(nsectors * SP_BSIZE) - 1, SEEK_SET);
	// check that it is possible to seek till the end of the filesystem.
        if (error == -1) {
                fprintf(stderr, "SPFS mkfs: Cannot create filesystem"
                        " of default size\n");
                return(1);
        }
	// S: seek back
        lseek(devfd, 0, SEEK_SET);
	// We seek back to the beginning because there is where
	// the superblock has to be written

        /*
         * Fill in the fields of the superblock and write it out to the.
         * first block of the device. Observers will note that we should
         * actually write everything else first to avoid corruption.
         */

        memset((void *)&sb, 0, sizeof(struct sp_superblock));

	// S: as a result of this memset to zero, the inodes and blocks
	// will be marked as 0, because 0 is the given value to define as free
	// in common/kern/spfs.h:
	//	#define SP_INODE_FREE     0
	//	#define SP_BLOCK_FREE     0

	// S: define the rest of the flags:
        sb.s_magic = SP_MAGIC;
        sb.s_mod = SP_FSCLEAN;
        sb.s_nifree = SP_MAXFILES - 4;  /* 0 & 1 unused, root and lost+found */
        sb.s_nbfree = SP_MAXBLOCKS - SP_FIRST_DATA_BLOCK - 2; /* dirents */
	// S: dirent = directory entry!!

	//#define SP_FIRST_DATA_BLOCK     129
	// 2 are taken away bcause block 129 contains the directory for
	// and entries for root, and block 130 the directroy entries for
	// lost & found

        /*
         * First 4 inodes are in use. Inodes 0 and 1 are not
         * used by anything, 2 is the root directory and 3 is
         * lost+found. Others were marked FREE (0) by memset above.
	 * ... see below:
         */

	// mark those inodes as being in use:
        sb.s_inode[0]  = SP_INODE_INUSE;
        sb.s_inode[1]  = SP_INODE_INUSE;
        sb.s_inode[2]  = SP_INODE_INUSE;
        sb.s_inode[3]  = SP_INODE_INUSE;

        /*
         * The first two blocks are allocated for the directory entries
         * for the root and lost+found directories. Others were
		 * marked FREE (0) by memset above.
         */

        sb.s_block[0] = SP_BLOCK_INUSE; /* root directory entries */
        sb.s_block[1] = SP_BLOCK_INUSE; /* lost_found directory entries */

	// S: now write to disk
        write(devfd, (char *)&sb, sizeof(struct sp_superblock));

        /*
         * The root directory and lost+found directory inodes
         * must be initialized and written to disk.
		 *
		 * Link count for root is 3 - ".", ".." and "lost+found"
		 * Link count for lost+found is 2 - "." and ".."
		 *
		 * We call fill_in_inode(*inode, type, uid, gid, nlink, inum)
         */

		memset((void *)&inode, 0, sizeof(struct sp_inode));
        inode.i_size = 3 * sizeof(struct sp_dirent);
        inode.i_blocks = 1;
        inode.i_addr[0] = SP_FIRST_DATA_BLOCK;
		// S: check the function /^fill_in_inode
		fill_in_inode(&inode, S_IFDIR | 0755, 0, 0, 3, 2);

		memset((void *)&inode, 0, sizeof(struct sp_inode));
        inode.i_size = 2 * sizeof(struct sp_dirent);
        inode.i_blocks = 1;
        inode.i_addr[0] = SP_FIRST_DATA_BLOCK + 1;
		fill_in_inode(&inode, S_IFDIR | 0755, 0, 0, 2, 3);

        /*
         * Fill in the directory entries for root
         */

	// S: Seek to where the entries has to be written
        lseek(devfd, SP_FIRST_DATA_BLOCK * SP_BSIZE, SEEK_SET);
	// S: zero out the block, so remove any garbage is there
        memset((void *)block, 0, SP_BSIZE);
	// S: write that zero to disk
        write(devfd, block, SP_BSIZE);
	// S: seek back to the first location
        lseek(devfd, SP_FIRST_DATA_BLOCK * SP_BSIZE, SEEK_SET);
        dir.d_ino = 2;
        strcpy(dir.d_name, ".");
        write(devfd, (char *)&dir, sizeof(struct sp_dirent));
        dir.d_ino = 2;
        strcpy(dir.d_name, "..");
        write(devfd, (char *)&dir, sizeof(struct sp_dirent));
        dir.d_ino = 3;
        strcpy(dir.d_name, "lost+found");
        write(devfd, (char *)&dir, sizeof(struct sp_dirent));

        /*
         * Fill in the directory entries for lost+found
         */

        lseek(devfd, (SP_FIRST_DATA_BLOCK * SP_BSIZE) + SP_BSIZE, SEEK_SET); // S: block 130
        memset((void *)block, 0, SP_BSIZE);
        write(devfd, block, SP_BSIZE);
        lseek(devfd, SP_FIRST_DATA_BLOCK * SP_BSIZE + SP_BSIZE, SEEK_SET);
        dir.d_ino = 3;
        strcpy(dir.d_name, ".");
        write(devfd, (char *)&dir, sizeof(struct sp_dirent));
        dir.d_ino = 2;
        strcpy(dir.d_name, "..");
        write(devfd, (char *)&dir, sizeof(struct sp_dirent));
}
