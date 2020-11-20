#ifndef __SDES_H__
#define __SDES_H__

#include <stddef.h>

/**This library will contain the actual SDES functions, the one used to convert a plaintext
 * into a ciphertext, and the other doing the opposite.
 */

/**This is the SDES function used to produce an 8-bit ciphertext from an 8-bit plaintext.
 * It can be described as a composition of following functions:
 * ciphextext = IP⁻1(fk2(SW(fk1(IP(plaintext)))))
 * @return an 8-bit ciphertext
 * @param plaintext an 8-bit word we want to encrypt.
 * @param key a 10-bit key known by both the receiver and the sender.
 */
u_int8_t sdes_ciphertext(u_int8_t plaintext, u_int16_t key);


/**This is the SDES function used to produce an 8-bit ciphertext from an 8-bit plaintext.
 * It can be described as a composition of following functions:
 * ciphextext = IP⁻1(fk1(SW(fk2(IP(ciphertext)))))
 * @return an 8-bit plaintext
 * @param ciphertext an 8-bit word we want to decrypt.
 * @param key a 10-bit known by bpth the receiver and the sender.
 */

u_int8_t sdes_plaintext(u_int8_t ciphertext, u_int16_t key);

#endif
