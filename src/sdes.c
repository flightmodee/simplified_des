#include <stdlib.h>
#include "fk.h"
#include "keygen.h"
#include "sdes.h"


u_int8_t sdes_ciphertext(u_int8_t plaintext, u_int16_t key){

	u_int8_t subkey_one, subkey_two, fk_one_output, fk_two_output, ciphertext, permuted_input;

	//Generation of the two subkeys
	subkey_one = first_subkey_generator(key);
	subkey_two = second_subkey_generator(key);

	//Initial permutation performed on the plaintext
	permuted_input = (u_int8_t)permutation(plaintext, 1);

	//Call to fk1
	fk_one_output = fk(permuted_input, subkey_one);
	//Call to SW
	fk_one_output = left_right_switch(fk_one_output);
	//Call to fk2
	fk_two_output = fk(fk_one_output, subkey_two);
	//IP⁻1
	ciphertext = permutation(fk_two_output, -1);

	return(ciphertext);
}



u_int8_t sdes_plaintext(u_int8_t ciphertext, u_int16_t key){

	u_int8_t subkey_one, subkey_two, fk_one_output, fk_two_output, plaintext, permuted_input;

	//Generation of the two subkeys
	subkey_one = first_subkey_generator(key);
	subkey_two = second_subkey_generator(key);

	//Initial permutation performed on the ciphertext
	permuted_input= (u_int8_t)permutation(ciphertext, 1);

	//Call to fk2
	fk_two_output = fk(permuted_input, subkey_two);
	//Call to SW
	fk_two_output = left_right_switch(fk_two_output);
	//Call to fk2
	fk_one_output = fk(fk_two_output, subkey_one);
	//IP⁻1
	plaintext = permutation(fk_one_output, -1);

	return(plaintext);

}

