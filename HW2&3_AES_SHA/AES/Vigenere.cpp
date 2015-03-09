#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream fin;
	fin.open("ciphertext.txt", ios::ate);
	if(!fin.is_open()){
		cout << "can't open file!" << endl;
		return 0;
	}
	int length = fin.tellg();
	char* ciphertext = new char[length];
	char* plaintext = new char[length];
	fin.seekg(0, fin.beg);
	fin.read(ciphertext,length);

	const int num_try = 15;
	int stat[26];
	double result[num_try];
	memset(stat, 0, 26*sizeof(int));
	memset(result, 0, num_try*sizeof(double));
	double prob[26] = {8.2, 1.5, 2.8, 4.2, 12.7, 2.2, 2.0, 6.1, 7.0, 0.1, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.0, 2.8, 1.0, 2.4, 2.0, 0.1, 0.1};
	
	//step 1: calculate key length
	int key_pos = 0;
	for(int L=2; L<2 + num_try; L++){
		while(key_pos < L){
			int count=0;
			for(int i=key_pos; i<length; i=i+L){
				int index = ciphertext[i] - 'A';
				stat[index]++;
				count++;
			}
			for(int i=0; i<26; i++){
				result[L-2] += double(stat[i]*stat[i])/count/count;
			}
			memset(stat, 0, 26*sizeof(int));
			key_pos++;
		} 
		result[L-2] = result[L-2]/L;
		key_pos=0;
	}
	
	int best_length = 0;
	double min=100;
	cout << "result" << endl;
	for(int i=0; i<num_try; i++){
		cout << result[i] << " ";
		if(fabs(result[i]-0.063) < min){
			best_length = i+2;
			min = fabs(result[i] - 0.063);
		}
	}
	cout << endl;
	cout<< "best length = " << best_length << endl;
	

	//step 2: find shift for each key position
	memset(stat, 0, 26*sizeof(int));
	key_pos = 0;
	while(key_pos < best_length){
		double sum_pq[26];
		memset(sum_pq, 0, 26*sizeof(double));
		for(int shift=0; shift<26; shift++){
			int count=0;
			for(int i=key_pos; i<length; i=i+best_length){
				int index = ciphertext[i] - 'A';
				stat[(index+shift)%26]++;
				count++;
			}
			for(int i=0; i<26; i++){
				double q = double(stat[i])/count/100;
				sum_pq[shift] +=  q * prob[i];
			}
			memset(stat, 0, 26*sizeof(int));
		}
		//calc best shift
		int best_shift = 0;
	    double min=100;
		for(int shift=0; shift<26; shift++){
			if(fabs(sum_pq[shift]-0.063)<min){
				min = fabs(sum_pq[shift]-0.063);
				best_shift = shift;
			}
		}
		cout << "best shift for key position " << key_pos << " is " << best_shift << endl;
		//recover plaintext
		for(int i=key_pos; i<length; i=i+best_length){
			plaintext[i] = ciphertext[i] + best_shift;
			if(plaintext[i] > 90){
				plaintext[i] = 'A' + (plaintext[i] - 91);
			}
		}

		key_pos++;
	}
	cout << endl << endl;

	//output
	for(int i=0; i<length; i++){
		cout << plaintext[i];
	}
	cout <<endl;


	system("pause");
}