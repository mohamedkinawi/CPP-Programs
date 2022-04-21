/*
CAN BE EASILY ADAPTED TO GET PERMUTATIONS OF ALL ITEMS IN A LIST (VECTOR/ARRAY) INSTEAD OF A STRING (EXAMPLE IS BACKTRACKING_ANAGRAMS)
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

void permute(string s, vector<string>& permutations);
void permuteHelper(string& characters_left, string& permutation, vector<string>& permutations);

ostream& operator<<(ostream& out, const vector<string>& v);

int main()
{
	string input;
	cout<<"Enter a phrase: ";
	getline(cin,input);
	vector<string> permutations;
	permute(input,permutations);
	cout<<permutations;
	return 0;
}

void permute(string characters_left, vector<string>& permutations)
{
	cout<<"Calculating...\n";
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

ostream& operator<<(ostream& out, const vector<string>& v)
{
	for(int i=0;i<v.size();i++)
	{
		out<<v[i]<<endl;
	}
	return out;
}
