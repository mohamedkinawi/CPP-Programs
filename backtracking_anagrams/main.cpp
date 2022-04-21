/* PROBLEM STATEMENT
https://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assn/anagrams.html
*/

#include<iostream>
#include<fstream>
#include<cctype>
#include<set>
#include<map>
#include<vector>
using namespace std;

typedef set<string>::iterator DictIter;

int findAnagrams(const string& phrase, int max, const set<string>& dictionary);
void to_letterInventory(const string& phrase, map<char, int>& letter_inventory);
void findAnagramsHelper(map<char,int>& letter_inventory, const DictIter& start, const DictIter& end, int& nOfAnagrams, vector<string>& found, const int& max);
bool add(const string& word, map<char,int>& letter_inventory, vector<string>& found);
void remove_last(vector<string>& found, map<char,int>& letter_inventory);

/***************************************HELPER FUNCTIONS (NOT CORE TO PROBLEM)**************************************/
void read_dictionary(const string file_name, set<string>& dictionary);
bool isempty(const string& phrase);
ostream& operator<<(ostream& out, const vector<string>& v);

int main()
{
	string dictionary_name;
	set<string> dictionary;
	cout<<"Welcome to the CS 106X Anagram Solver!\n"
	   <<"Dictionary file name: ";
	cin>>dictionary_name;
	cout<<"Reading dictionary...\n";
	read_dictionary(dictionary_name,dictionary);
	cout<<"Dictionary contains "<<dictionary.size()<<" unique words.\n";
	while(1)
	{
		while(cin.get()!='\n');
		string phrase;
		int max_words, nOfAnagrams;
		cout<<"\nPhrase to scramble (or Enter to quit): ";
		getline(cin,phrase);
		if(isempty(phrase))
			break;
		cout<<"Max words to include (0 for all): ";
		cin>>max_words;
		cout<<"Searching for anagrams...\n\n";
		nOfAnagrams = findAnagrams(phrase, max_words, dictionary);
		cout<<"Total anagrams found: "<<nOfAnagrams<<endl;
	}
	cout<<"Have a nice day.\n";
	return 0;
}

int findAnagrams(const string& phrase, const int max, const set<string>& dictionary)
{
	map<char,int> letter_inventory;
	to_letterInventory(phrase,letter_inventory);
	DictIter start = dictionary.begin();
	DictIter end = dictionary.end();
	int nOfAnagrams = 0;
	vector<string> found;
	findAnagramsHelper(letter_inventory,start,end,nOfAnagrams,found,max);
	return nOfAnagrams;
}

void to_letterInventory(const string& phrase, map<char, int>& letter_inventory)
{
	for(int i=0;i<phrase.length();i++)
	{
		if(!isspace(phrase[i]))
		{
			letter_inventory[phrase[i]]++;
		}
	}
}

void findAnagramsHelper(map<char,int>& letter_inventory, const DictIter& start, const DictIter& end,int& nOfAnagrams, vector<string>& found, const int& max)
{
		bool leaf = true;
		if(max==0 || found.size()<max)
		{
			for(DictIter iter = start; iter!=end; iter++)
			{
				if(add(*iter,letter_inventory,found))
				{
					findAnagramsHelper(letter_inventory,start,end,nOfAnagrams,found,max);
					remove_last(found, letter_inventory);
					leaf = false;
				}
			}
		}
		if(found.size()>0 && leaf)
		{
			nOfAnagrams++;
			cout<<found;
		}
}

bool add(const string& word, map<char,int>& letter_inventory, vector<string>& found)
{
	for(int i=0;i<word.length();i++)
	{
		if(!(letter_inventory[word[i]]--))
		{
			while(i>=0)
			{
				letter_inventory[word[i--]]++;
			}
			return false;
		}
	}
	found.push_back(word);
	return true;
}

void remove_last(vector<string>& found, map<char,int>& letter_inventory)
{
	string word = found[found.size()-1];
	for(int i=0;i<word.length();i++)
	{
		letter_inventory[word[i]]++;
	}
	found.pop_back();
}


/***************************************HELPER FUNCTIONS (NOT CORE TO PROBLEM)**************************************/

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

bool isempty(const string& phrase)
{
	for(int i=0;i<phrase.length();i++)
	{
		if(!isspace(phrase[i])) return false;
	}
	return true;
}

ostream& operator<<(ostream& out, const vector<string>& v)
{
	out<<"{";
	for(int i=0;i<v.size();i++)
	{
		out<<"\""<<v[i]<<"\"";
		if(i<v.size()-1) out<<",";
	}
	out<<"}"<<endl;
	return out;
}
