#ifndef __KEYGEN_H__
#define __KEYGEN_H__

#include <stddef.h>

/** This header will contain the prototypes of all the functions that are used to generate 8-bit long subkeys
 *	from a 10-bit long key that is known by both the sender and the receiver of a message.
 */

/** Printing function used to display the binary representation of a decimal number.
 * It also has a range used to print 8 or 10-bit words, to add more clarity.
 * @param word a decimal word we want the binary representation of.
 * @param range the number of effective bits printed.
 */

void print_bits(u_int16_t word, int range);

/** This permutation function represents different functions used within the SDES one.
 * Depending on which permutation you want to apply to your key passed as an argument, it will
 * also take an unsigned integer to determine which permutation will be applied (8 for P8, 10 for P10, etc...)
 * @return a key which permutation depends on the second parameter passed.
 * @param key the original key.
 * @param perm the integer representing the permutation we want to apply to our key.
 */

u_int16_t permutation(u_int16_t key, int perm);

/** This function will perform a circular left shift of an amount of bits passed as
 * an argument, separately on the first five bits
 * and the second five bits of the argument.
 * @return the key thus formed.
 * @param key the key which bits will be rotated.
 * @param pos the amount of bit shifts realized on the key
 */


u_int16_t circular_left_shift(u_int16_t key, unsigned int pos);


/**Function used to generate the subkey that will be used within the first iteration of the fk function.
 * @return an 8-bit subkey.
 * @param key a 10-bit key known by both the sender and receiver of a ciphertext.
 */
u_int8_t first_subkey_generator(u_int16_t key);

/**Function used to generate the subkey used within the second iteration of the fk function.
 * @return an 8-bit subkey used in the second iteration of the fk function.
 * @param key a 10-bit key known by both the sender and receiver of a ciphertext.
 */
u_int8_t second_subkey_generator(u_int16_t key);


#endif
