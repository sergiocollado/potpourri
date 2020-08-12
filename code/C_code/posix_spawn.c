#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

//reference: https://linux.die.net/man/3/posix_spawn
//http://coliru.stacked-crooked.com/a/a5d8a82784e0409d
/*
*The posix_spawn() and posix_spawnp() functions shall create a new process (child process)^
* from the specified process image. The new process image shall be constructed from a regula
* r executable file called the new process image file.
*/

/*posix_spawn() is another way to launch processes, different from fork-exec(), or system() calls*/

/*
#include < spawn.h >

int posix_spawn(pid_t *restrict pid, const char *restrict path,
 const posix_spawn_file_actions_t *file_actions,
 const posix_spawnattr_t *restrict attrp,
 char *const argv[restrict],
 char *const envp[restrict]);
*/


extern char **environ;

void run_cmd(char *cmd)
{
    pid_t pid;
    char *argv[] = {(char*)"bash", (char*)"-c", cmd, NULL};
    int status;
    printf("Run command: %s\n", cmd);
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        printf("Child pid: %i\n", pid);
        if (waitpid(pid, &status, 0) != -1) {
            printf("Child exited with status %i\n", status);
        } else {
            perror("waitpid");
        }
    } else {
        printf("posix_spawn: %s\n", strerror(status));
    }
}

int main(int argc, char* argv[])
{
    run_cmd((char*)"echo HelloWorld!");
    run_cmd((char*)"which bash");
    run_cmd((char*)"which uname");
    run_cmd((char*)"uname -a");
    run_cmd((char*)"date");
    return 0;
}

/* output example: 
gcc -std=c89 -Wall -pedantic main.cpp && ./a.out
cc1plus: warning: command line option '-std=c90' is valid for C/ObjC but not for C++
HelloWorld!
/bin/bash
/bin/uname
Linux stacked-crooked 4.4.0-57-generic #78-Ubuntu SMP Fri Dec 9 23:50:32 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux
Wed Aug 12 18:56:02 UTC 2020
Run command: echo HelloWorld!
Child pid: 32139
Child exited with status 0
Run command: which bash
Child pid: 32140
Child exited with status 0
Run command: which uname
Child pid: 32142
Child exited with status 0
Run command: uname -a
Child pid: 32144
Child exited with status 0
Run command: date
Child pid: 32146
Child exited with status 0
*/
