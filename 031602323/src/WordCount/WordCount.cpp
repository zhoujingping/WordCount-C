#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;

int Char = 0, Word = 0, Line = 0;

map<string, int> cnt;
typedef pair<string, int> PAIR;
vector<PAIR> vec;
ifstream infile;

void readTxt(string fname)
{
	infile.open(fname, ifstream::in);
	if (!infile.is_open())
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	infile >> noskipws;   //不忽略空白符，也不忽略每行最后的'\n'
}

void charCount(ifstream &inf)		//inf.eof()多循环一次
{
	char c;
	while (inf.peek() != EOF)
	{
		inf >> c;
		Char++;
	}

	//	cout << Char << endl;
}

bool isWord(string w)
{
	int l = w.length();
	if (l < 4) return false;
	for (int i = 0;i < 4;i++)
	{
		if (!(w[i] >= 97 && w[i] <= 122)) return false;
	}
	for (int i = 4;i < l;i++)
	{
		if (!((w[i] >= 97 && w[i] <= 122) || (w[i] >= 48 && w[i] <= 57)))
			return false;
	}
	return true;
}

void wordCount(ifstream &inf)
{
	char c;

	inf.clear();
	inf.seekg(0);

	while (inf.peek() != EOF)
	{
		string w;
		inf >> c;
		while ((c != ' ') && (c != '\t') && (c != '\n'))
		{
			if (c >= 65 && c <= 90)   //大写转小写
				c = c + 32;

			w = w + c;				//越界
			inf >> c;
		}

		if (isWord(w))  //w是单词，将其加入map
		{
			//			cout << w << endl;
			Word++;
			if (cnt.count(w) == 0)
			{
				cnt[w] = 1;
			}
			else
			{
				cnt[w]++;
			}
		}
	}
}

void Delete(string &s, const string &mark)
{
	size_t nSize = mark.size();
	while (1)
	{
		size_t pos = s.find(mark);
		if (pos == string::npos)
		{
			return;
		}
		s.erase(pos, nSize);
	}
}

void lineCount(ifstream &inf)		//空白字符处理
{
	string s;

	inf.clear();
	inf.seekg(0);

	while (inf)
	{
		getline(inf, s);
		//		cout <<"1:"<< s << endl;

		//		remove(s.begin(), s.end(), ' ');
		//		remove(s.begin(), s.end(), '\t');

		Delete(s, " ");
		Delete(s, "\t");

		//		cout << "2:" << s << endl;

		if (!s.empty()) Line++;
		//		cout <<"Line:"<< Line << endl;
	}
}

int cmp(const PAIR &x, const PAIR &y)	//从大到小排序
{
	return x.second > y.second;
}

void seq()
{
	map<string, int>::iterator curr;

	for (curr = cnt.begin();curr != cnt.end();curr++)
	{
		vec.push_back(make_pair(curr->first, curr->second));
	}

	sort(vec.begin(), vec.end(), cmp);
}

void writeTxt()
{
	vector<PAIR>::iterator curr;

	cout << "characters: " << Char << endl;
	cout << "words: " << Word << endl;
	cout << "lines: " << Line << endl;

	for (curr = vec.begin();curr != vec.end();curr++)
	{
		cout << '<' << (*curr).first << '>' << ':' << (*curr).second << endl;
	}
}

int main(int argc, const char* argv[])
{
	for (int i = 1;i < argc;i++)
	{
		string fname = argv[i];
		readTxt(fname);
		charCount(infile);
		wordCount(infile);
		seq();
		lineCount(infile);
		writeTxt();
	}
	return 0;
}