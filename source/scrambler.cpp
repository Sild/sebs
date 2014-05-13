#include "../header/scrambler.h"
#include <iostream>
char * encode(char *block, int len) {
	char *enc_block;
	char key = 73;
	enc_block = new char[len];
	int i = 0;
	while(*block++) {
		enc_block[i++] = (char)(~(int)*block);
	}
	return enc_block;
}

char * decode(char *block, int len) {
	char *dec_block;
	dec_block = encode(block, len);
	return dec_block;

}