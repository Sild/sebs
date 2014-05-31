#include "../header/scrambler.h"

Scrambler::Scrambler(std::string private_key) {
	this->set_private_key_length(private_key.length());
	this->set_private_key(private_key);
	this->iv = new byte[ CryptoPP::AES::BLOCKSIZE ];
	memset( this->iv, 0x00, CryptoPP::AES::BLOCKSIZE );

}

char *Scrambler::encode(const char *bite_stream, const int length) {

    char *cipher_bite_stream = new char[length];

	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(this->private_key,this->private_key_length, this->iv);
	cfbEncryption.ProcessData((byte*)cipher_bite_stream, (byte*)bite_stream, length);

	return cipher_bite_stream;

}

char *Scrambler::decode(const char *cipher_bite_stream, const int length) {

    char *bite_stream = new char[length];

    CryptoPP::CFB_Mode<CryptoPP::AES >::Decryption cfbDecryption(this->private_key,this->private_key_length, this->iv);
    cfbDecryption.ProcessData((byte*)bite_stream, (byte*)cipher_bite_stream, length);

    return bite_stream;
}

void Scrambler::set_private_key( std::string value ) {
	int diff = this->private_key_length - value.length();

	for(int i = 0; i < diff; i++) {
		value += value[i];
	}
	this->private_key = new byte[this->private_key_length];
	memcpy(this->private_key, value.c_str(), this->private_key_length);
	
}

void Scrambler::set_private_key_length( const int &value ) {
	int need_to_key_length = 8 - value % 8;
	if( need_to_key_length == 0) {
		this->private_key_length = value;
	} else {
		this->private_key_length = value + need_to_key_length;
	}
}
