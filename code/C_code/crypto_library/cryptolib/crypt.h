#ifndef CRYPTOLIB_H_
#define CRYPTOLIB_H_

#include <stdio.h>
#include <stdint.h>

struct crypt_context_t
{
  uint8_t* key;
  unsigned length;
  unsigned i;
};

char* get_version(void);

int crypt_buffer(struct crypt_context_t* context, uint8_t *output,
                 const uint8_t *input, unsigned length);

#endif /*CRYPTOLIB_H_*/
