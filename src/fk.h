#ifndef __FK_H__
#define __FK_H__

#include <stddef.h>

/** This library contains all the functions used to implement the fk function.
 */


/** This function creates an SBOX whose content depends on the integer passed 
 * as an argument. If it is equal to 0, it'll produce the SBOX 0. Similarly, it produces
 * S1 if 1 is passed as an argument.
 * @return a pointer array representing the SBOX.
 * @param type the integer representing the sbox we want to generate.
 */
int **sbox_creation(int type);


/** This function will retrieve the leftmost four bits of an 8-bit input.
 * @return the leftmost four bits of the input.
 * @param word the word we want the leftmost four bits of.
 */
u_int8_t leftmost_four_bits(u_int8_t word);


/**This function will retrieve the rightmost four bits of an 8-bit input.
 * @return the rightmost four bits of the input.
 * @param word the word we want the rightmost four bits of.
 */
u_int8_t rightmost_four_bits(u_int8_t word);


/** This function is the F mapping used within the fk function.
 * It basicall takes the rightmost four bits of a permuted plaintext and a subkey. The way it functions is explained in the source code.
 * @return a 4-bit word.
 * @param right_part the rightmost four bits of a permuted plaintext.
 * @param subkey a subkey previously generated.
 */
u_int8_t f_mapping(u_int8_t right_part, u_int8_t subkey);


/** This is the fk function used within the S_DES secure encryption algorithm.
 * It's actually pretty simple: the first operation is a bitwise XOR between the leftmost four bits of the input, 
 * and the output of the F mapping function called on the rightmost four bits of the input, and a subkey.
 * Subsequently, we perform four left shifts on the word previously obtained, then perform a bitwise OR between said word and
 * the rightmost four bits of the input, which is the final result of this function.
 * @return an 8-bit word obtained through the operations described above.
 * @param input an 8-bit input.
 * @param subkey an 8-bit subkey.
 */
u_int8_t fk(u_int8_t input, u_int8_t subkey);


/** The fk function only alter the leftmost 4 bits of an input.
 * The switch function will interchange the left and right 4 bits so that
 * the second instance of fk operates on a 4 different bits.
 * @return the 8-bit input whose left and right 4 bits have been
 * interchanged.
 * @param input an 8-bit input
 */
u_int8_t left_right_switch(u_int8_t input);

#endif
