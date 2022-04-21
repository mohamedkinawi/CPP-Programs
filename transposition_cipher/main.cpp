/* PROBLEM STATEMENTS
https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/transpCipher.html
https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/brute_force_decrypt.html
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<cctype>
#include<string>
#include<vector>
#include<set>
#include<map>
using namespace std;

/**********************FOR NORMAL ENCRYPTION AND DECRYPTION***********************/
const char PAD = '~';
const int SORTED_TO_ORIGINAL = false;
const int ORIGINAL_TO_SORTED = true;

typedef map<int,int>::iterator MapIter;

void encrypt_route();
string encrypt(string plaintext, string key);
void decrypt_route();
string decrypt(string ciphertext, string key);
void fill_map(const string& key, map<int,int>& mp, const bool& ORIGINAL_TO_SORTED);
int next_smallest(string key,const int index);

/**************************FOR BRUTE FORCE DECRYPTION****************************/
const string DICTIONARY_FILE_NAME = "dictionary.txt";
const int MAX_KEY_LEN = 9;
const int TOP_X = 5;

struct DecryptionGuess {
    string potentialPlaintext;
    double wordPercentage;
};

void decrypt_brute_route();
vector<DecryptionGuess> bruteForce(string ciphertext);
void read_dictionary(const string file_name, set<string>& dictionary);
string get_key_characters(int length);
void permute(string s, vector<string>& permutations);
void permuteHelper(string& characters_left, string& permutation, vector<string>& permutations);
void check_and_add(const string& plaintext, vector<DecryptionGuess>& guesses, const set<string>& dictionary);
ostream& operator<<(ostream& out, const DecryptionGuess& guess);
string alphaAndSpaceOnly(string s);

/*************************SRING MANIPULATION FUNCTIONS**************************/
bool isempty(const string& phrase);
string take_input(string prompt);

int main()
{
	while(1)
	{
		cout<<"Welcome to the Transposition Cipher Machine!\n"
		 <<"Please choose:\n"
		 <<"1) encrypt text\n"
		 <<"2) decrypt text\n"
		 <<"3) brute force decrypt without the key\n"
		 <<"Please type your choice, 0 to end: ";
		unsigned int action;
		cin>>action;
		switch(action)
		{
			case 0:
				cout<<"Goodbye!\n";
				return 0;
			case 1:
				encrypt_route();
				break;
			case 2:
				decrypt_route();
				break;
			case 3:
				decrypt_brute_route();
				break;
		}
	}
	return 0;
}


/**********************FOR NORMAL ENCRYPTION AND DECRYPTION***********************/

void encrypt_route()
{
	string plaintext = take_input("Please enter the text to encrypt: ");
	string key = take_input("Please type in a key: ");
	/* padding plaintext */
	while(plaintext.length()%key.length()!=0)
		plaintext = plaintext + PAD;
	cout<< "Encrypted text:\n\n\"";
	cout<< encrypt(plaintext,key);
	cout<< "\"\n\n";
}

/****************
iterate through sorted sequence of characters in key
and output according to that position in key.
****************/
string encrypt(string plaintext, string key)
{
	map<int,int> sorted_to_original;
	fill_map(key, sorted_to_original, SORTED_TO_ORIGINAL);
	const int rows = plaintext.length()/key.length();
	string ciphertext = "";
	for(MapIter i=sorted_to_original.begin() ; i!=sorted_to_original.end() ; i++)
	{
		for(int q=0 ; q<rows ; q++)
		{
			ciphertext+=plaintext[i->second+(key.length()*q)];
		}
	}
	return ciphertext;
}

void decrypt_route()
{
	string ciphertext = take_input("Please enter the text to decrypt: ");
	string key = take_input("Please type in a key: ");
	if(ciphertext.length()%key.length()!=0)
	{
		cout<<"\n\nCiphertext length is not divisible by key length!\n\n";
		exit(1);
	}
	cout<< "Decrypted text:\n\n\"";
	cout<< decrypt(ciphertext,key);
	cout<< "\"\n\n";
}

/****************
iterate through normal sequence of characters in key
and output according to position of that character in the sorted key.
****************/
string decrypt(string ciphertext, string key)
{
	map<int,int> original_to_sorted;
	fill_map(key, original_to_sorted, ORIGINAL_TO_SORTED);
	const int rows = ciphertext.length()/key.length();
	string plaintext = "";
	for(int r=0; r<rows; r++)
	{
		for(MapIter i=original_to_sorted.begin() ; i!=original_to_sorted.end() ; i++)
		{
			char next = ciphertext[i->second*rows+r];
			if(next!=PAD) plaintext+=next;
		}
	}
	return plaintext;
}

void fill_map(const string& key, map<int,int>& mp, const bool& ORIGINAL_TO_SORTED)
{
	int index_of_next_smallest = -1;
	for(int i=0 ; i<key.length() ; i++)
	{
		index_of_next_smallest = next_smallest(key,index_of_next_smallest);
		if(ORIGINAL_TO_SORTED)
			mp[index_of_next_smallest] = i;
		else
			mp[i] = index_of_next_smallest;
	}
}

int next_smallest(string key,const int index)
{
	int index_of_next_smallest;
	int value_at_index_of_next_smallest = 256;
	for(int i=0;i<key.length();i++)
	{
		if(i!=index && (index==-1 || (key[i]>key[index] || (key[i]>=key[index] && i>index))) && key[i]<value_at_index_of_next_smallest)
		{
			index_of_next_smallest = i;
			value_at_index_of_next_smallest = key[index_of_next_smallest];
		}
	}
	return index_of_next_smallest;
}


/**************************FOR BRUTE FORCE DECRYPTION****************************/

void decrypt_brute_route()
{
	string ciphertext = take_input("Please enter the text to attempt to decrypt: ");
	vector<DecryptionGuess> possible_plaintexts = bruteForce(ciphertext);
	cout<<"\n\nMy best guess for the top 5 decryption possibilities:\n\n";
	for(int i=0;i<possible_plaintexts.size();i++)
	{
		cout<<endl<<endl<<possible_plaintexts[i]<<endl<<endl;
	}
}

/* This function produces a vector of DecryptionGuess structs that holds
 * the top X number of best-guesses based on a brute force decryption
 * of a ciphertext.
 */
vector<DecryptionGuess> bruteForce(string ciphertext)
{
	set<string> dictionary;
	read_dictionary(DICTIONARY_FILE_NAME,dictionary);
	vector<DecryptionGuess> guesses;
	for(int i=1;i<=MAX_KEY_LEN;i++)
	{
		if(ciphertext.length()%i==0)
		{
			cout<<"Testing keys of length "<<i<<endl;
			string key_characters = get_key_characters(i);
			vector<string> key_permutations;
			permute(key_characters,key_permutations);
			for(int q=0;q<key_permutations.size();q++)
			{
				string plaintext = decrypt(ciphertext,key_permutations[q]);
				check_and_add(plaintext,guesses,dictionary);
			}
		}
	}
	return guesses;
}

void read_dictionary(const string file_name, set<string>& dictionary)
{
	
	ifstream infile;
	infile.open(file_name);
	if(infile.fail())
	{
	    cout<<"Failed to read dictionary!\n";
	    exit(1);
	}
	else
	{
		string next;
		while(infile>>next)
		{
			dictionary.insert(next);
		}
		infile.close();
	}
}

string get_key_characters(int length)
{
	string key_characters("");
	unsigned char c;
	for(int i=0;i<length;i++)
	{
		c=i;
		key_characters+=c;
	}
	return key_characters;
}

void permute(string characters_left, vector<string>& permutations)
{
	string permutation("");
	permuteHelper(characters_left, permutation, permutations);
}

void permuteHelper(string& characters_left, string& permutation, vector<string>& permutations)
{
	if(characters_left.length())
	{
		for(int i=0;i<characters_left.length();i++)
		{
			char next = characters_left[i];
			characters_left.erase(i,1);
			permutation.push_back(next);
			permuteHelper(characters_left,permutation,permutations);
			characters_left.insert(i,1,next);
			permutation.pop_back();
		}
	}
	else
	{
		permutations.push_back(permutation);
	}
}

void check_and_add(const string& plaintext, vector<DecryptionGuess>& guesses, const set<string>& dictionary)
{
	DecryptionGuess guess;
	guess.potentialPlaintext = plaintext;
	istringstream iss(alphaAndSpaceOnly(plaintext));
	string word;
	int nofwords = 0 ;
	double nofdictionarywords = 0;
	while(iss>>word && ++nofwords)
		if(dictionary.find(word)!=dictionary.end() && ++nofdictionarywords);
	guess.wordPercentage = (nofdictionarywords/nofwords) * 100;
	vector<DecryptionGuess>::iterator insertat;
	for(insertat=guesses.begin();insertat!=guesses.end();insertat++)
	{
		if(guess.wordPercentage>insertat->wordPercentage)
		{
			break;
		}
	}
	guesses.insert(insertat,guess);
	if(guesses.size()>TOP_X) guesses.pop_back();
}

ostream& operator<<(ostream& out, const DecryptionGuess& guess)
{
	out<<guess.potentialPlaintext<<" ("<<guess.wordPercentage<<"%)";
	return out;
}

/* This function returns a string with the following properties:
 * 1. It only has alphabetic characters and spaces, and
 * 2. All space-like characters (newline, tab) have been
 *    converted to spaces (' ')
 * 3. All lower case
 */
string alphaAndSpaceOnly(const string s)
{
	string cleaned("");
	for(int i=0;i<s.length();i++)
	{
		if(isspace(s[i])) cleaned+=' ';
		else if(isalpha(s[i]))
		{
			char c = s[i];
			if(s[i]<='Z' && s[i]>='A')
				c=s[i]-'A'+'a';
			cleaned+=c;
		}
	}
	return cleaned;
}


/*************************SRING MANIPULATION FUNCTIONS**************************/

bool isempty(const string& phrase)
{
	for(int i=0;i<phrase.length();i++)
	{
		if(!isspace(phrase[i])) return false;
	}
	return true;
}

string take_input(string prompt)
{
	cout<<prompt;
	string input(" ");
	while(isempty(input))
		getline(cin,input);
	return input;
}
