/*
 * wordcount 031602541
 * 2018-09-07 trial
 * 14-16
*/

#include "stdafx.h"
#include "wc.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#define DBUG
using namespace std;

string text;
string tline;
vector <wcn> cwr;

int main(int argc, char* argv[])
{
	long characters = 0;
	long words = 0;
	long lines = 0;
	vector <wcn>::iterator p;
	if (argc < 2)
	{
		cout << "no filename\n";
		return 0;
	}
	if (argc > 2)
	{
		cout << "The program \n";
	}
	words = cword(argv[1]);
	characters = cchar(argv[1]);
	cwr = c10(argv[1]);
	text.clear();
	ifstream infile(argv[1]);
	ofstream oufile;
	while(getline(infile,text))
	{
		++ lines;
	}
	infile.close();
	oufile.open("result.txt",ios::out);
	
	oufile << "characters: " << characters<< endl;
	oufile << "words: " << words << endl;
	oufile << "lines: " << lines << endl;
	p = cwr.begin();
	while (p != cwr.end())
	{
		oufile << '<' << p->w << ">: " << p->c << endl;
		++p;
	}
	return 0;
}
