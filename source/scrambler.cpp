#include "../header/scrambler.h"
#include <iostream>


char * encode(char *block, int len) {
	char *enc_block;
	enc_block = new char[len];
	for(int i = 0; i < len; i++) {
		enc_block[i] = *block + 1;
		block++;
	}
	return enc_block;

}

char * decode(char *block, int len) {
	char *dec_block;
	dec_block = new char[len];
	for(int i = 0; i < len; i++) {
		dec_block[i] = *block - 1;//(char)(~(int)*block);
		block++;
	}
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