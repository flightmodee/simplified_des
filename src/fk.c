#include <stdio.h>
#include <stdlib.h>
#include "keygen.h"

int **sbox_creation(int type){

	int **sbox;
	if ((sbox = (int **)malloc(4 * sizeof(int*))) == NULL){
		perror("Memory allocation failed. Exit.\n");
		exit(-1);
	}
	int i, j;
	for (i = 0; i < 4; i++)
		if ((sbox[i] = (int *)malloc(4 * sizeof(int))) == NULL){
			perror("Memory allocation failed. Exit.\n");
			exit(-1);
		}

	//We'll be using two text files that contain the values of each slot of each sbox, 
	//in order to fill them.
	FILE *f;
	char *filename;

	if (type == 0)
		filename = "../sbox1.txt";
	else if (type == 1)
		filename = "../sbox2.txt";
	
	if ((f = fopen(filename, "r")) == NULL){
		perror("Something went wrong. Abort.\n");
		exit(-1);
	}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			sbox[i][j] = fgetc(f) - '0'; //To retrieve the actual integer and not an ASCII code

	fclose(f);
	return(sbox);

}



u_int8_t rightmost_four_bits(u_int8_t word){

	int i;
	u_int8_t rightmost_bits = 0;

	for (i = 0; i < 4; i++)
		if (word & (1 << i))
			rightmost_bits |= (1 << i);

	return (rightmost_bits);
}



u_int8_t leftmost_four_bits(u_int8_t word){

	int i;
	u_int8_t leftmost_bits = 0;

	for (i = 0; i < 4; i++)
		if (word & (1 << 4 + i))
			leftmost_bits |= (1 << i);

	return (leftmost_bits);
}



u_int8_t f_mapping(u_int8_t right_part, u_int8_t subkey){

	//Expansion and permutation of the first argument
	u_int8_t expanded = permutation(right_part, 6);

	//The 8-bit subkey is added to the expanded value using XOR.
	expanded ^= subkey;

	//Creation of the two s_boxes.
	int **sbox_zero = sbox_creation(0);
	int **sbox_one = sbox_creation(1);
	u_int8_t output_zero, output_one, f_output;
	int i;

	//Here we declare an array where two back-to-back elements represent the row and column fed to their respective sboxes.
	//rows_and_columns[0] and [1] thus contain (P0,0 P0,3), and so on.
	u_int8_t rows_and_columns[4] = {0};

	for (i = 0; i < 2; i++){
		if (expanded & (1 << 4 - 4*i)) //Pi, 3
			rows_and_columns[2*i] |= (1 << 0);
		if (expanded & (1 << 7 - 4*i)) //Pi, 0
			rows_and_columns[2*i] |= (1 << 1); //rows_and_columns[2*i] now contains (Pi,0 Pi,3)
		if (expanded & (1 << 5 - 4*i)) //Pi, 2
			rows_and_columns[2*i + 1 ] |= (1 << 0);
		if (expanded & (1 << 6 - 4*i)) //Pi, 1
			rows_and_columns[2*i + 1] |= (1 << 1); //rows_and_columns[2*i + 1] now contains (Pi,1 Pi, 2)
	}

	//We retrieve the output of each sbox we fed a 2-bit word.
	output_zero = sbox_zero[rows_and_columns[0]][rows_and_columns[1]];
	output_one = sbox_one[rows_and_columns[2]][rows_and_columns[3]];


	f_output = (output_zero << 2) | output_one; //We now have a 4-bit word made of the bits produced by the two sboxes.
	//We perform the P4 permutation on the 4-bit word
	f_output = (u_int8_t)permutation(f_output, 4);

	return (f_output);
}



u_int8_t fk(u_int8_t input, u_int8_t subkey){

	u_int8_t left = leftmost_four_bits(input);
	u_int8_t right = rightmost_four_bits(input);
	u_int8_t f_output = f_mapping(right, subkey);
	u_int8_t output;

	//We perform a bit-by-bit XOR between the leftmost four bits of our input and the output of the F mapping on
	//the rightmost four bits of our input and our subkey
	left ^= f_mapping(right, subkey);

	//We perform four left shifts on the left then "add" the right part of the rightmost four bits of our input
	//using a bit-by-bit OR.
	output = (left << 4) | right;

	return (output);
}



u_int8_t left_right_switch(u_int8_t input){

	u_int8_t left_part = leftmost_four_bits(input);
	//We use a bitmask equal to 00001111 to clear the leftmost four bits of the input.
	//Afterwards, we perform 4 left shifts, to effectively push the right part to the left.
	//Subsequently, we perform a bitwise OR on that word and the left part of our initial input.
	input = ((input & 15) << 4) | left_part;

	return (input);
}

