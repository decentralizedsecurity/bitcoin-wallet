#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <stdint.h>
#include <stddef.h>
#include <psa/crypto.h>

#define APP_SUCCESS (0)
#define APP_ERROR   (-1)

#define NRF_CRYPTO_EXAMPLE_ECDSA_TEXT_SIZE (100)
#define NRF_CRYPTO_EXAMPLE_ECDSA_PUBLIC_KEY_SIZE (65)
#define NRF_CRYPTO_EXAMPLE_ECDSA_SIGNATURE_SIZE (64)
#define NRF_CRYPTO_EXAMPLE_ECDSA_HASH_SIZE (32)

int crypto_init(void);
int crypto_finish(void);
int generate_ecdsa_keypair(void);
int import_ecdsa_pub_key(void);
int sign_message(void);
int verify_message(void);

#endif // CRYPTO_H_
