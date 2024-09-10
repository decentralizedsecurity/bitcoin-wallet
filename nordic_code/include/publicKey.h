#ifndef PUBLIC_KEY_H
#define PUBLIC_KEY_H

#include <stdlib.h> // para size_t

int generate_public_key_from_hex(const char *private_key_hex, unsigned char *public_key, size_t *public_key_len);
void compress_pubkey(const unsigned char *uncompressed_key, unsigned char *compressed_key); // La api de nordic no tiene esta función, por lo que tenemos que implementarla

#endif // PUBLIC_KEY_H
