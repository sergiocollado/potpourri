#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "crypt.h"

char version[20] = "version 1.0.1";

char* get_version(void)
{
    return version; 
}

int crypt_buffer(struct crypt_context_t* context, uint8_t *output,
                 const uint8_t *input, unsigned length)
{
    if (context == NULL || output == NULL || input == NULL || length == 0) 
    {
        return -1;
    }

    uint8_t* key = context->key;
    
    for (unsigned j = 0; j < length; ++j)
    {  
       key[context->i] += context->i;
       output[j] = input[j]^key[context->i];
       context->i++; 
       context->i = (context->i)%(context->length);
    }
    return 0;
}
