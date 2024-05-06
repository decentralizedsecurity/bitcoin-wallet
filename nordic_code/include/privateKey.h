#ifndef PRIVATEKEY_H
#define PRIVATEKEY_H

#include <stdlib.h>

char* to_hexadecimal(unsigned char* hash, size_t size);
char* generate_private_key();
//char* convert_private_key_to_wif(const char* hex_priv_key);

#endif //PRIVATEKEY_H
