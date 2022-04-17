#include<iostream>
#include<string>
#include<vector>
#include<cctype>
using namespace std;

void combinationsHelper(string combination, int next_element, vector<string>& combinations, const string& s, const int& number_of_elements)
{
	if(combination.length()==number_of_elements)
	{
		combinations.push_back(combination);
	}
	else
	{
		for(int i=next_element;i<s.length();i++)
		{
			combinationsHelper(combination+s[i],i+1,combinations,s,number_of_elements);
		}
	}
}

vector<string> combinations(const string& s,const int& number_of_elements)
{
	vector<string> combinations;
	for(int i=0;i<s.length();i++)
	{
		combinationsHelper(s.substr(i,1),i+1,combinations,s,number_of_elements);
	}
	return combinations;
}

int main()
{
	while(1)
	{
		string input;
		char c;
		int number_of_elements;
		cout<<"\nEnter a string (unique characters only if you don't want duplicate characters in the combinations), empty string to exit: ";
		while(isspace(c=cin.get()) && c!='\n');
		if(c=='\n') break;
		else cin.putback(c);
		cin>>input;
		cout<<"Enter number of elements in a combination: ";
		cin>>number_of_elements;
		while((c=cin.get())!='\n');
		vector<string> result = combinations(input,number_of_elements);
		for(int i=0;i<result.size();i++)
			cout<<result[i]<<endl;
		cout<<"There are "<<result.size()<<" combinations."<<endl;
	}
	return 0;
}