/*
 * CSc103 Project 5: Syntax highlighting, part two.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:
 */

#include "fsm.h"
using namespace cppfsm;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <set>
using std::set;
#include <map>
using std::map;
#include <initializer_list> // for setting up maps without constructors.

// enumeration for our highlighting tags:
enum {
	hlstatement,  // used for "if,else,for,while" etc...
	hlcomment,    // for comments
	hlstrlit,     // for string literals
	hlpreproc,    // for preprocessor directives (e.g., #include)
	hltype,       // for datatypes and similar (e.g. int, char, double)
	hlnumeric,    // for numeric literals (e.g. 1234)
	hlescseq,     // for escape sequences
	hlerror,      // for parse errors, like a bad numeric or invalid escape
	hlident       // for other identifiers.  Probably won't use this.
};

// usually global variables are a bad thing, but for simplicity,
// we'll make an exception here.
// initialize our map with the keywords from our list:
map<string, short> hlmap = {
#include "res/keywords.txt"
};
// note: the above is not a very standard use of #include...

// map of highlighting spans:
map<int, string> hlspans = {
	{hlstatement, "<span class='statement'>"},
	{hlcomment, "<span class='comment'>"},
	{hlstrlit, "<span class='strlit'>"},
	{hlpreproc, "<span class='preproc'>"},
	{hltype, "<span class='type'>"},
	{hlnumeric, "<span class='numeric'>"},
	{hlescseq, "<span class='escseq'>"},
	{hlerror, "<span class='error'>"}
};
// note: initializing maps as above requires the -std=c++0x compiler flag,
// as well as #include<initializer_list>.  Very convenient though.
// to save some typing, store a variable for the end of these tags:
string spanend = "</span>";

string translateHTMLReserved(char c) {
	switch (c) {
		case '"':
			return "&quot;";
		case '\'':
			return "&apos;";
		case '&':
			return "&amp;";
		case '<':
			return "&lt;";
		case '>':
			return "&gt;";
		case '\t': // make tabs 4 spaces instead.
			return "&nbsp;&nbsp;&nbsp;&nbsp;";
		default:
			char s[2] = {c,0};
			return s;
	}
}

string createSpan(string str, int state){
	string output="";
	switch(state){
		case 0:
			output+=str;
			break;
		case 1:
			output+=hlspans[hlmap[str]] + str + spanend;
			break;
		case 2:

		case 3:

		case 4:

		case 5:

		case 6:

		case 7:
		break;
	}
	return output;
	/*
	//for testing, comment out the return and
	//remove the block comment limits
	//this shows state of input and input itself for troubleshooting
	cout<<"{"<<state<<","<<str<<"}"<<"\n";
	return "";
	*/
}

string htmler(string s){
	string output;
	string temp="";
	int cstate = start;
	for (unsigned long i = 0; i < s.length(); i++) {
		int laststate=updateState(cstate,s[i]);
		cout<<cstate;
		if (cstate!=laststate){
			if(temp!=""){
				output+=createSpan(temp,laststate);
				temp="";
				temp+=s[i];
			}else{
				temp+=s[i];
			}
		}else{
			if(i!=s.length()-1){
				temp+=s[i];
			}else{
				output+=createSpan(temp+s[i],laststate);
			}
		}
	}
	return output;
}

int main() {
	string input;
	string output;
	while(getline(cin,input)){
		output+=htmler(input);
	}
	cout << output <<"\n";
	return 0;
}
