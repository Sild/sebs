#include "../header/scrambler.h"

Scrambler::Scrambler(std::string private_key) {
	this->set_private_key_length(private_key.length());
	this->set_private_key(private_key);

}

const char *Scrambler::encode(const char *bite_stream) {

    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    std::string clean_data(bite_stream);
    std::string cipher_data;

    CryptoPP::AES::Encryption aesEncryption(this->private_key, this->private_key_length);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipher_data ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( clean_data.c_str() ), clean_data.length() );
    stfEncryptor.MessageEnd();
    
	return cipher_data.c_str();

}

const char *Scrambler::decode(const char *bite_stream) {

    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    std::string cipher_data(bite_stream);
    std::string clean_data;

    CryptoPP::AES::Decryption aesDecryption(this->private_key, this->private_key_length);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( clean_data ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipher_data.c_str() ), cipher_data.size() );
    stfDecryptor.MessageEnd();

    return clean_data.c_str();
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
	std::cout << need_to_key_length;

	if( need_to_key_length == 0) {
		this->private_key_length = value;
	} else {
		this->private_key_length = value + need_to_key_length;
	}
}
