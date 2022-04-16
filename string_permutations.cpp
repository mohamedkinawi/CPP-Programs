#include<iostream>
#include<string>
using namespace std;

string swap(const string& s, int i1, int i2)
{
	string n = s;
	char temp = n[i1];
	n[i1] = n[i2];
	n[i2] = temp;
	return n;
}

void permute(const string& s, const int AT)
{
	if(AT==s.length()-1)
	{
		cout<<s[AT]<<endl;
	}
	else
	{
		for(int i = AT ; i < s.length() ; i++)
		{
			if(i!=AT)
				for(int p=0;p<AT;p++)
					cout<<s[p];
			string n = swap(s,AT,i);
			cout<<n[AT];
			permute(n,AT+1);
		}
	}
}

int main()
{
	string input;
	cout<<"Enter a string: ";
	cin>>input;
	permute(input,0);
	return 0;
}
