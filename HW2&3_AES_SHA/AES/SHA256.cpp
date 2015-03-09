#include <cstdio>
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

#include "sha.h"
#include <fstream>
#include <vector>
int SHA256block(int argc, char* argv[]) {
	std::ifstream fvideo("v1.mp4", std::ios::in|std::ios::binary);
	if(!fvideo.is_open()){
		cout << "can't open file!" << endl;
		return 0;
	}
	fvideo.seekg(0, fvideo.end);
	int size = fvideo.tellg();
	int blocknum = size/1024;
	int lastblock_size = size%1024;
	cout << "file size = " <<  size << endl;
	cout << "block num = " <<  blocknum << endl;
	cout << "last block size = " << lastblock_size << endl;
	

	int blockcount = blocknum;
	char* lastblock = new char[lastblock_size];
	memset(lastblock, 0, lastblock_size * sizeof(char));
	//read last block
	fvideo.seekg(blocknum*1024, fvideo.beg);	
	cout << fvideo.tellg() << endl << endl;
	fvideo.read(lastblock, lastblock_size);
	//cout << "Last block: \n" << lastblock << endl << endl;
	//system("pause");

	string y = string(lastblock);
	cout << y.length() << endl;
	CryptoPP::SHA256 hash;
	byte const* pbData = (byte*)lastblock;
    unsigned int nDataLen = lastblock_size;
    byte abDigest[CryptoPP::SHA256::DIGESTSIZE];
	CryptoPP::SHA256().CalculateDigest(abDigest, pbData, nDataLen);
	cout << abDigest << endl;
	cout << CryptoPP::SHA256::DIGESTSIZE << endl << endl;
	
	blockcount--;

	while(blockcount >=0){
		char* block = new char[1024+32];
		memset(block, 0, 1056 * sizeof(char));
		fvideo.seekg(blockcount*1024, fvideo.beg);	
		fvideo.read(block, 1024);
		//cout << block << endl << endl;
		//system("pause");
		for(int i=0; i<32; i++){
			block[1024+i] = (char) abDigest[i]; 
		}
		
		pbData = (byte*)block;
		nDataLen = 1024+32;
		CryptoPP::SHA256().CalculateDigest(abDigest, pbData, nDataLen);
		free(block);
		blockcount--;
	}
	//cout << abDigest << endl;
	 for( int i = 0; i < 32; i++ ) {
		std::cout << std::hex << (0xFF &  abDigest[i]) << " ";
	 }
	 
	
	system("pause");
}