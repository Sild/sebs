#include "../header/scrambler.h"
#include <iostream>


char * encode(char *block, int len) {
	char *enc_block;
	enc_block = new char[len];
	int i = 0;
	while(*block++) {
		enc_block[i++] = (char)(~(int)*block);
	}
	std::cout << block << std::endl;
	std::cout << enc_block << std::endl;
	std::cout << encode2(enc_block, len) << std::endl;
	std::cout << "------------------------" << std::endl;
	return enc_block;

}

char * decode(char *block, int len) {
	char *dec_block;
	dec_block = encode(block, len);
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