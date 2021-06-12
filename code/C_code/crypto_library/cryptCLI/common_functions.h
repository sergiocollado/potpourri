#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdlib.h>
#include <stdint.h>

#define READING_BLOCK (256)

struct crypt_context_t
{
  uint8_t* key;
  unsigned length;
  unsigned i;
};

typedef int (*crypt_)(struct crypt_context_t*, uint8_t*, uint8_t*, unsigned);

void* getlib(const char* libname, void* lib_handle);

void release_lib(int status, void* lib_handle);

void* get_fun(const char* fun_name, void* libhandle);

void fopen_error(FILE* fp, char* filename);

void get_key(char* key, char* key_file, uint8_t* key_string);

void cipher(FILE* fpinput, char* input_file, FILE* fpoutput, char* output_file, struct crypt_context_t* context, uint8_t* key_string, crypt_ crypt_buffer);

#endif //COMMON_FUNCTIONS_H
