//
// Created by makrron on 15/04/24.
//

#ifndef GENERATEADDRESS_H
#define GENERATEADDRESS_H

char* P2PKH_address(const char* public_key_hash_hex, int network); // Función para generar una dirección P2PKH. Recibe el hash de la clave pública y la red (0 para mainnet y 1 para testnet).

#endif //GENERATEADDRESS_H
