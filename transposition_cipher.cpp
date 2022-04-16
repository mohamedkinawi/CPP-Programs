/* PROBLEM STATEMENT @ https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/transpCipher.html */

#include<iostream>
#include<string>
using namespace std;

const char PAD = '~';

struct KeyUnit
{
	char letter;
	int index;
};

/* This function simply converts a key of type string to an array with each element (of type KeyUnit)
in the array storing a single letter and the index of that letter in the key. */
KeyUnit* createKeyChain(string key)
{
	const int key_length = key.length();
	KeyUnit* keyChain = new KeyUnit[key_length];
	for(int i=0 ; i<key_length ; i++)
	{
		keyChain[i].letter = key[i];
		keyChain[i].index = i;
	}
	return keyChain;
}

/* ENCRYPT ROUTE FUNCTIONS */
void encrypt();
void encrypt_sort(KeyUnit* key , int length);
void encrypt_output(string plaintext,int key_length, KeyUnit* keyChain);

/* DECRYPT ROUTE FUNCTIONS */
void decrypt();
int* decrypt_sort(string key);
void decrypt_output(string ciphertext,int key_length, int* sorted_indices);

/* FUNCTIONS THAT ARE NOT CORE TO THE PROBLEM I.E. THEIR IMPLEMENTATIONS ARE PLACED AT END OF FILE */
string take_input(string prompt);
void swap(KeyUnit* key, int i1, int i2);
int index_of_smallest(KeyUnit* key, const int start, const int length);

int main()
{
	while(1)
	{
		cout<<"Welcome to the Transposition Cipher Machine!\n"
		 <<"Please choose:\n"
		 <<"1) encrypt text\n"
		 <<"2) decrypt text\n"
		 <<"Please type your choice, 0 to end: ";
		unsigned int action;
		cin>>action;
		switch(action)
		{
			case 0:
				cout<<"Goodbye!\n";
				return 0;
			case 1:
				while(cin.get()!='\n');
				encrypt();
				break;
			case 2:
				while(cin.get()!='\n');
				decrypt();
				break;
		}
	}
	return 0;
}


/* ENCRYPT ROUTE FUNCTIONS */

void encrypt()
{
	string plaintext = take_input("Please enter the text to encrypt: ");
	string key = take_input("Please type in a key: ");
	const int key_length = key.length();
	KeyUnit* keyChain = createKeyChain(key);
	encrypt_sort(keyChain,key_length);
	/* padding plaintext */
	while(plaintext.length()%key_length!=0)
		plaintext = plaintext + PAD;
	encrypt_output(plaintext,key_length,keyChain);
	delete[] keyChain;
}

void encrypt_sort(KeyUnit* keyChain , int key_length) //selection sort
{
	for(int i=0 ; i<key_length ; i++)
	{
		int smallest = index_of_smallest(keyChain,i,key_length);
		swap(keyChain,i,smallest);
	}
}

void encrypt_output(string plaintext,int key_length, KeyUnit* keyChain)
{
	int rows = plaintext.length()/key_length;
	cout<<"Encrypted text:\n\n\"";
	for(int i=0 ; i<key_length ; i++)
	{
		for(int q=0 ; q<rows ; q++)
		{
			cout<<plaintext[keyChain[i].index+(key_length*q)];
		}
	}
	cout<<"\"\n\n";
}



/* DECRYPT ROUTE FUNCTIONS */

void decrypt()
{
	string ciphertext = take_input("Please enter the text to decrypt: ");
	string key = take_input("Please type in a key: ");
	if(ciphertext.length()%key.length()!=0)
	{
		cout<<"\n\nCiphertext length is not divisible by key length!\n\n";
		return;
	}
	int* sorted_indices = decrypt_sort(key);
	decrypt_output(ciphertext,key.length(),sorted_indices);
	delete[] sorted_indices;
}

int* decrypt_sort(string key)
{
	KeyUnit* keyChain = createKeyChain(key);
	const int key_length = key.length();
	int* sorted_indices = new int[key_length];
	for(int i=0 ; i<key_length ; i++)
	{
		int smallest = index_of_smallest(keyChain,i,key_length);
		sorted_indices[keyChain[smallest].index] = i;
		swap(keyChain,i,smallest);
	}
	delete[] keyChain;
	return sorted_indices;
}

void decrypt_output(string ciphertext,int key_length, int* sorted_indices)
{
	int rows = ciphertext.length()/key_length;
	cout<<"Decrypted text:\n\n\"";
	for(int r=0; r<rows; r++)
	{
		for(int i=0 ; i<key_length ; i++)
		{
			char next = ciphertext[sorted_indices[i]*rows+r];
			if(next!=PAD) cout<<next;
		}
	}
	cout<<"\"\n\n";
}



/* FUNCTIONS THAT ARE NOT CORE TO THE PROBLEM */

string take_input(string prompt)
{
	string input;
	cout<<prompt;
	getline(cin,input);
	return input;
}

void swap(KeyUnit* keyChain, int i1, int i2)
{
	KeyUnit temp = keyChain[i1];
	keyChain[i1] = keyChain[i2];
	keyChain[i2] = temp;
}

int index_of_smallest(KeyUnit* keyChain, const int start, const int key_length)
{
	int smallest = start;
	for(int q=start+1 ; q<key_length ; q++)
	{
		if(keyChain[q].letter<keyChain[smallest].letter)
		{
			smallest = q;
		}
	}
	return smallest;
}