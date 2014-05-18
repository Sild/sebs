#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include <iostream>
#include <iomanip>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

class Scrambler {
public:
	Scrambler(std::string private_key);
	std::string encode(const char *bite_stream);
	std::string decode(const char *bite_stream);

private:
	void set_private_key(std::string value);
	void set_private_key_length(const int &value);
	byte *private_key;
	int private_key_length;
};

#endif