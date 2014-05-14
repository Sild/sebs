#include "../header/scrambler.h"
#include <iostream>


char * encode(char *block, int len) {
	char *enc_block;
	enc_block = new char[len];
	int i = 0;
	while(*block) {
		// std::cout << *block << " " << ~(int)*block << " | ";
		enc_block[i++] = (~(int)*block);
		block++;
	}
	// std::cout << i << std::endl;
	return enc_block;

}

char * decode(char *block, int len) {
	char *dec_block;
	dec_block = new char[len];
	int i = 0;
	while(*block) {
		// std::cout << *block << " " << ~(int)*block << " | ";
		dec_block[i++] = (char)(~*block);
		block++;
	}
	
	// std::cout << i << std::endl;
	return dec_block;

}

char * encode2(char *block, int len) {
	char *enc_block;
	enc_block = new char[len];
	int i = 0;
	while(*block++) {
		enc_block[i++] = (char)(~(int)*block);
	}
	return enc_block;

}