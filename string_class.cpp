#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;


class String{
	public:
		String(); 		//default constructor
		String(const char q[]); IMPORTANT:::: the const modifier is a must, without it on VS, the program won't run. Running from the command line using g++ produces warnings
		// big 3
		String(const String& obj); 		//copy constructor
		String& operator = (const String& rhs); //returns calling object for a chain of assignments
		~String(); 				//destructor
		//
		friend istream& operator >>(istream& ins, String& obj);
		friend ostream& operator <<(ostream& out, const String& obj);
		friend bool operator ==(const String& lhs, const String& rhs);
		friend String operator +(const String& lhs, const String& rhs);
		/*
		you thought about returning a String& reference from the operator+ function claiming that it
		is more efficient. There is one problem tho. The String object that you create inside the function	
		will have its destructor automatically called at the end of the function call. That is why you have
		to create a new independent copy by returning String with appropriate copy constructor.
		*/
		friend String operator *(const String& lhs, int m);
		friend String operator *(int m, const String& rhs);
	private:
		char* s;
};


int main(){

	String obj1 = "i am you and you are me"; 	//this should call the second constructor
	String obj2("and we are us"); 			//this should call the second constructor

	( String("piss off") + " " + "and chill out :)" )*4;
	//copy constructor is called 3 times (2 due to returning String value in 2 operator+ calls, and 1 due to returning )
	String obj3 = (String("piss off") + " " + "and chill out :)") * 4;
	//copy constructor is called also 3 times which is not expected. I expected one more call because of the obj3 initialization
	// IN BOTH:
	//the operator + function is called 2 times
	//the constructor with the array parameter is called 6 times (3 in front of you, 2 inside operator+, 1 inside operator*)
	//the operator * function is called 1 time

	cout<<"obj1 ="<<obj1<<endl;
	cout<<"obj2 ="<<obj2<<endl;
	cout<<"obj3 ="<<obj3<<endl;

	obj1 = obj2 = obj3 = "final symbols";

	cout<<"obj1 ="<<obj1<<endl;
	cout<<"obj2 ="<<obj2<<endl;
	cout<<"obj3 ="<<obj3<<endl;

	String s1,s2;
	do{
		cout<<"Enter 2 words or exit:"<<endl;
		cin>>s1;
		if(s1=="exit") break;
		cin>>s2;
		cout<<"You entered: "<<s1<<" "<<s2<<endl;
	}while(true);

	
	obj1=s1;
	cout<<obj1<<endl<<s1<<endl;
	obj1=obj1;
	cout<<obj1<<endl;
	
	return 0;
}




String::String() :s(new char[1]) {
	s[0] = '\0';
}

String::String(const char q[]) : s(new char[strlen(q) + 1]) {
	//cout << "second constructor" << endl;
	//q must be a c string i.e. either quoted string, or array variable (automatic or dynamic) with null character inside array
	strcpy(s, q);
}

String::String(const String& obj) : s(new char[strlen(obj.s) + 1]) {
	//cout << "copy constructor" << endl;
	strcpy(s, obj.s);
}

String& String::operator=(const String& rhs) {
	//cout<<"OUUUUUUUUUUUUUUUUUUT"<<endl;
	if (rhs.s != s) { 		//check if rhs is same object as calling object
		//cout<<"HEEEEEEEEEERE"<<endl;
		delete[] s;
		s = new char[strlen(rhs.s) + 1];
		strcpy(s, rhs.s);
	}
	return *this;
}

String::~String() {
	delete[] s;
}

istream& operator >>(istream& ins, String& obj) { //implementing the extraction operator as it normally works (skips blanks)
	delete[] obj.s;


	obj.s = new char[1000];
	while (!(ins >> obj.s)) {}
	char* ss = new char[strlen(obj.s) + 1]; //minimize excess unused memory
	strcpy(ss, obj.s);
	delete[] obj.s;
	obj.s = ss;


	/* to make it exactly fit whatever is entered from the first time :::not complete (account if file input or keyboard input)
	int next, wordfound = 0, numberofchars = 0;
	while( !wordfound ){
		ins.get(next);
		if(next != EOF && next!=' ' && next!='\n' && next!='\t'){
			wordfound=1;
		}
	}
	*/

	return ins;
}

ostream& operator <<(ostream& out, const String& obj) {
	out << obj.s;
	return out;
}
bool operator ==(const String& lhs, const String& rhs) {
	return !strcmp(lhs.s, rhs.s);
}
String operator +(const String& lhs, const String& rhs) {
	//cout << "operator +" << endl;
	char* all = new char[strlen(lhs.s) + strlen(rhs.s) + 1];
	strcpy(all, lhs.s);
	strcat(all, rhs.s);
	String temp(all);
	delete[] all;
	return temp;
}
String operator *(const String& lhs, int m) {
	//cout << "operator *" << endl;
	char* all = new char[strlen(lhs.s) * m + 1];
	all[0] = '\0';
	for (int i = 1; i <= m; i++)
		strcat(all, lhs.s);
	String temp(all);
	delete[] all;
	return temp;
}
String operator *(int m, const String& rhs) {
	char* all = new char[strlen(rhs.s) * m + 1];
	all[0] = '\0';
	for (int i = 1; i <= m; i++)
		strcat(all, rhs.s);
	String temp(all);
	delete[] all;
	return temp;
}