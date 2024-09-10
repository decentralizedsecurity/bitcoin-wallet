#ifndef PRIVATEKEY_H
#define PRIVATEKEY_H

#include <stdlib.h>

char* to_hexadecimal(unsigned char* hash, size_t size); // Convierte un hash en bytes a una cadena hexadecimal
char* generate_private_key(); // Genera una clave privada aleatoria
char* convert_private_key_to_wif(const char* hex_priv_key, int mainnet); // Convierte una clave privada en formato hexadecimal a formato WIF (Wallet Import Format)

#endif //PRIVATEKEY_H
