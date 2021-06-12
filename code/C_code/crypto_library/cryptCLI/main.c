#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dlfcn.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "common_functions.h"

extern int   errno;
extern char* optarg;
extern int   optind;

int main(int argc, char **argv)
{
    void* lib_handle = NULL; 
    char* (*get_version)(void);
    int   (*crypt_buffer)(struct crypt_context_t*, uint8_t*, uint8_t*, unsigned);

    // retrieve the dynamic library
    lib_handle = getlib("libcrypt.so", lib_handle);
    *(void**) (&get_version)  = get_fun("get_version",  lib_handle); 
    *(void**) (&crypt_buffer) = get_fun("crypt_buffer", lib_handle);
    on_exit(&release_lib, lib_handle);

    // define crypt context
    struct crypt_context_t context = {NULL, 0, 0};

    // file descriptiors for input & output
    FILE* fpoutput = NULL;
    FILE* fpinput  = NULL;

    int opt;
    char* key         = NULL;
    char* key_file    = NULL;
    char* output_file = NULL;
    char* input_file  = NULL; 
    uint8_t key_string[256]; 
    memset(key_string, 0x00, 256);

    //parse of arguments
    while ((opt = getopt(argc, argv, "k:f:o:hv")) != -1) {
        switch (opt) {
        case 'k':
            key = optarg;
            break;
        case 'f':
            key_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        case 'h':
            fprintf(stdout, "crypt [-h] -k <key> | -f <key_file> [-o <output_file>] [<input_file>]\n");
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            printf("%s\n",get_version());
            exit(EXIT_SUCCESS);
            break;
        default: /* '?' */
            fprintf(stderr, "crypt [-h] -k <key> | -f <key_file> [-o <output_file>] [<input_file>]\n incorrect option: %s",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
   input_file = argv[optind];

   // handle key
   get_key(key, key_file, key_string);

   // handle input
   if (input_file != NULL) 
   {
       errno = 0;
       fpinput = fopen(input_file, "r");
       fopen_error(fpinput, input_file);
   }
   else
   {
       fpinput = stdin;
   }

   // cipher
   cipher(fpinput, input_file, fpoutput, output_file, &context, key_string, crypt_buffer);

   exit(EXIT_SUCCESS);
}
