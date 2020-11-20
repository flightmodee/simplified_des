#include <stdio.h>
#include <stdlib.h>
#include "keygen.h"

void print_bits(u_int16_t word, int range){

	int i;
	for (i = range - 1 ; i >= 0; i--)
		putchar(word & (1 << i) ? '1' : '0');
	printf("\n");

}

u_int16_t permutation(u_int16_t key, int perm){

	int i;
	u_int16_t result = 0;

	//P10
	if (perm == 10){
		int perm_table[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
		for (i = 0; i < 10; i++){
			result <<= 1;
			if (key & (1 << 10 - perm_table[i]))
			result |= 1;
		}
	}
	//P8
	else if (perm == 8){
		int perm_table[8] = {6, 3, 7, 4, 8, 5, 10, 9};
		for (i = 0; i < 8; i++){
			result <<= 1;
			if (key & (1 << 10 - perm_table[i]))
				result |= 1;
		}
	}

	// IP
	else if (perm == 1){
		int perm_table[8] = {2, 6, 3, 1, 4, 8, 5, 7};
		for (i = 0; i < 8; i++){
			result <<= 1;
			if (key & (1 << 8 - perm_table[i]))
				result |= 1;
		}
	}

	//IP -1
	else if (perm == -1){
		int perm_table[8] = {4, 1, 3, 5, 7, 2, 8, 6};
		for (i = 0; i < 8; i++){
			result <<= 1;
			if (key & (1 << 8 - perm_table[i]))
				result |= 1;
		}
	}

	//Permutation used within the F mapping (expansion + permutation);
	else if (perm == 6){
		int perm_table[8] = {4, 1, 2, 3, 2, 3, 4, 1};
		for (i = 0; i < 8; i++){
			result <<= 1;
			if (key & (1 << 4 - perm_table[i]))
				result |= 1;
		}
	}
	//P4, permutation used within the F mapping after the creation of a 4 bit word produced by the 
	//two sboxes.
	else if (perm == 4){
		int perm_table[4] = {2, 4, 3, 1};
		for (i = 0; i < 4; i++){
			result <<= 1;
			if (key & (1 << 4 - perm_table[i]))
				result |= 1;
		}
	}

	else{
		perror("Error, the permutation you're asking for doesn't exist.\n");
		exit(-1);
	}

	return (result);

}


u_int16_t circular_left_shift(u_int16_t key, unsigned int pos){

	u_int16_t left_part = 0;
	u_int16_t right_part = 0;
	//This mask will be used in our first circular left shift. We substract 1 in order
	//to convert 100000 into 011111
	u_int16_t bitmask = (1 << 5) - 1;
	int bits_in_each_part = 5; //We want to treat each part of the key as 5-bit long words
	int i;
	int j;

	
	// This block will copy the rightmost five bits of the key.
	for (i = 0; i < 5; i++)
		if (key & (1 << i))
			right_part |= (1 << i);


	//Circular left shift, using a mask in order to "erase" the bits from position 5 onwards
 	right_part = bitmask & ((right_part << pos) | (right_part >> bits_in_each_part - pos));



// ++++++ Copy of the leftmost bits of the key ++++++
	for (j = 0 ; j < 5; j++)
		if (key & (1 << j + i))
			left_part |= (1 << j + i);


	//We're changing the value of our bitmask to erase the bits from the tenth position onwards, 
	//so that the circular left shift is valid on the left part of our key.
	//Our bitmask is equal to 992, as its binary representation is 1111100000 
	//(which keeps the leftmost five bits untouched, and clears the other bits)
	bitmask = 992;

	// Circular left shift.
	left_part = bitmask & ((left_part << pos) | (left_part >> bits_in_each_part - pos));
	return(left_part + right_part);

}


u_int8_t first_subkey_generator(u_int16_t key){
	key = permutation(key, 10);
	key = circular_left_shift(key, 1);
	key = permutation(key, 8);
	return ((u_int8_t)key);
}


u_int8_t second_subkey_generator(u_int16_t key){
	key = permutation(key, 10);
	key = circular_left_shift(key, 1);
	key = circular_left_shift(key, 2);
	key = permutation(key, 8);
	return ((u_int8_t)key);
}
