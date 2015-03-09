
// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <cstdio>
#include <iostream>
#include <osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include <cryptlib.h>
using CryptoPP::Exception;

#include <hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <des.h>
using CryptoPP::DES_EDE2;

#include <modes.h>
using CryptoPP::CBC_Mode;

#include <secblock.h>
using CryptoPP::SecByteBlock;
#include <iostream>
#include <string>
#include <modes.h>
#include <aes.h>
#include <filters.h>

#include "sstream"
/*
CryptoPP::SecByteBlock HexDecodeString(const char *hex)
{
CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
CryptoPP::SecByteBlock result((size_t)ss.MaxRetrievable());
ss.Get(result, result.size());
return result;
}*/

using namespace CryptoPP;


int AESCTR(int argc, char* argv[]) {
	
	std::string recovered;
	 //question 1
    std::string cipher_hex = "0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329";
    std::string key_hex = "36f18357be4dbd77f050515c73fcf9f2";
    std::string iv_hex  = "69dda8455c7dd4254bf353b773304eec";
	

	/* question 2
	std::string cipher_hex = "e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451";
    std::string key_hex = "36f18357be4dbd77f050515c73fcf9f2";
    std::string iv_hex  = "770b80259ec33beb2561358a9f2dc617";
	*/
	
    char *temp;
    temp = (char*) malloc(cipher_hex.length() + 1);
	strcpy(temp, cipher_hex.c_str());
	const char* hex_str = temp;
	std::string cipher;
	unsigned int ch ;
	for( ; std::sscanf(hex_str , "%2x", &ch ) == 1 ; hex_str += 2 )
		cipher += ch ;
	
	
	char key[16];
	for(int i=0; i<16; i++){
		string t = key_hex.substr(i*2, 2);
		int ti  = stoi(t,nullptr,16);
		cout << t << endl;
		key[i] =  ti;
	}


	char iv[16];
	for(int i=0; i<16; i++){
		string t = iv_hex.substr(i*2, 2);
		int ti  = stoi(t,nullptr,16);
		cout << t << endl;
		iv[i] =  ti;
	}

	/* encryption
	std::string plaintext = "name macmilan age 24 ciy bonn country germany";
	std::string ciphertext;
	AES::Encryption aesEncryption((byte *)key.c_str(), 16);
	CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, (byte *)iv.c_str() );

	StreamTransformationFilter stfEncryptor(cbcEncryption, new StringSink( ciphertext ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
	stfEncryptor.MessageEnd();
	cout << "cipher text plain: " << ciphertext << endl;
	cout << ciphertext.length() << endl;
	system("pause");

	*/

	/*
	// Pretty print
	string encoded;
	encoded.clear();
	 StringSource(ciphertext, true,
	 new HexEncoder(
	 new StringSink(encoded)
	) // HexEncoder
	); // StringSource
	cout << "cipher text In HEX FORM (Modified):: " << encoded << endl;
	cout << endl;
	cout << endl;
	 char *name2;
	name2 = (char*) malloc(encoded.length() + 1); // don't forget to free!!!!
	 //s2 = Database_row_count; // I forget if the string class can implicitly be converted to char*
	 //s2[0] = '1';
	strcpy(name2, encoded.c_str());

	 const char* hex_str = name2;

	std::string result_string ;
	 unsigned int ch ;
	 for( ; std::sscanf( hex_str, "%2x", &ch ) == 1 ; hex_str += 2 )
	result_string += ch ;
	cout << "HEX FORM to cipher text :: " ;
	std::cout << result_string << '\n' ;
	cout << result_string.length() << endl;
	cout << endl;
	cout << endl;
	 /*********************************\
	\*********************************/
	
    CTR_Mode< AES >::Decryption d;
	d.SetKeyWithIV((byte*)key, 16, (byte*)iv);
	StringSource ss3( cipher, true, 
        new StreamTransformationFilter( d,
            new StringSink( recovered )
        ) // StreamTransformationFilter
    ); // StringSource

	std::cout << "Decrypted Text: " << endl;
	std::cout << recovered << endl;
    std::cout << recovered.length() << endl;
    system("pause");
	
    return 0;
	
	
}

