#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fk.h"
#include "keygen.h"
#include "sdes.h"


int main(){

	srand(time(NULL));

	u_int8_t plaintext, ciphertext;


	//10-bit key
	u_int16_t key = 642;
	plaintext = rand() %256; //This will generate a number between 2^0 and 2^8 - 1
	printf("The randomly generated plaintext is ");
	print_bits(plaintext, 8);

	// encryption of the plaintext
	ciphertext = sdes_ciphertext(plaintext, key);
	printf("\nThe ciphertext generated from the plaintext is ");
	print_bits(ciphertext, 8);

	//decryption of the ciphertext
	plaintext = sdes_plaintext(ciphertext, key);
	printf("\nThe original plaintext is ");
	print_bits(plaintext, 8);


	return(0);




}
