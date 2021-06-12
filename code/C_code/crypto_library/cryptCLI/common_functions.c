#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include "common_functions.h"

extern int   errno;

void* getlib(const char* libname, void* lib_handle) {
    lib_handle = dlopen(libname, RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    return lib_handle;
}

void release_lib(int status, void* lib_handle)
{
    dlclose(lib_handle);
}

void* get_fun(const char* fun_name, void* libhandle)
{
    dlerror();
    char* error = NULL;
    void* fun_handler = dlsym(libhandle, fun_name);
    if ((error = dlerror()) != NULL)  
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    return fun_handler;
}

void fopen_error(FILE* fp, char* filename)
{
    if (NULL == fp)
    {
        fprintf(stderr, "Error opening %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void get_key(char* key, char* key_file, uint8_t* key_string)
{
   if (key == NULL &&  key_file == NULL) 
   {
      fprintf(stderr, "No key found\n");
      exit(EXIT_FAILURE);
   }
   else if (key != NULL && key_file != NULL)
   {
      fprintf(stderr, "key and key file defined\n");	   
      exit(EXIT_FAILURE);
   }
   else if (key_file != NULL && key == NULL)
   {
       errno = 0;
       FILE* fpkey = fopen(key_file, "r");
       fopen_error(fpkey, key_file);
       char keybuffer[256];
       unsigned readbytes = fread(keybuffer, 1, 257, fpkey);
       if (readbytes == 0) 
       {
           fprintf(stderr, "Error in key file: %s is empty\n", key_file);
	   fclose(fpkey);
           exit(EXIT_FAILURE);
       }
       else if (readbytes > 256)
       {
           fprintf(stderr, "Error in key file %s: key file longer than expected- max key size is 256 bytes\n", key_file);
	   fclose(fpkey);
           exit(EXIT_FAILURE);
       }
       memcpy(key_string, keybuffer, readbytes);
       key_string[readbytes-1] = '\0';
       fclose(fpkey);
   }
   else if (key != NULL && key_file == NULL)
   {
     memcpy(key_string, key, strlen(key));
   }
}

void cipher(FILE* fpinput, char* input_file, FILE* fpoutput, char* output_file, struct crypt_context_t* context, uint8_t* key_string, crypt_ crypt_buffer) 
{
   if (fpinput != NULL) {  
       errno = 0;
       fopen_error(fpinput, input_file);
       if (output_file != NULL) 
       {   
	   errno = 0;
           fpoutput = fopen(output_file, "a");
           fopen_error(fpoutput, output_file);
       }
       uint8_t  inputbuffer [256]; 
       uint8_t  outputbuffer[256];
       unsigned readbytes = 0;
       unsigned input_length = 0;

       context->key = (uint8_t*)key_string;
       context->length = strlen((char*)key_string);

       clearerr(fpinput);
       while(!feof(fpinput)){
           readbytes = fread(inputbuffer, 1, READING_BLOCK, fpinput);
	   if (ferror(fpinput)) 
	   {
               fprintf(stderr, "Error reading file %s\n", input_file);
	       fclose(fpinput);
               exit(EXIT_FAILURE);
	   }
	   input_length = readbytes;
           crypt_buffer(context, outputbuffer, (uint8_t*)inputbuffer, input_length);
	   if (input_length < READING_BLOCK) { outputbuffer[input_length-1] = '\0';}
	   if (output_file != NULL && fpoutput != NULL) 
	   {
	       fwrite(outputbuffer, 1, input_length, fpoutput);
           }
	   else
	   {
	       fprintf(stdout, "%s", outputbuffer);
	   }
	}

       fclose(fpinput);
       if (output_file != NULL) { fclose(fpoutput); }
   } 
}

