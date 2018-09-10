// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//






#include <iostream>
#include<string>
#include<fstream>
#include<cassert>
#include<map> 
#include<cstdlib>
using namespace std;

class testfile
{
public:
	void init();
	int characters;
	int words;
	int lines;
	char *content;
};

void testfile::init()
{
	characters = 0;
	words = 0;
	lines = 0;
	content = (char*)malloc(sizeof(char*));
}

int countcha();//计算字符数
int countword();//计算单词数
int countline();//计算行数

int countcha(char *t, testfile f1, int characters)
{
	ifstream myfile;
	myfile.open(t);
	if (!myfile.is_open())
	{
		cout << "文件打开失败" << endl;

	}
	char c;
	myfile >> noskipws;//强制读入空格和换行符
	while (!myfile.eof())
	{
		myfile >> c;
		if (myfile.eof())
			break;//防止最后一个字符输出两次
		if (c == '\n')
			f1.content[characters++] = ' ';
		else
			f1.content[characters++] = c;//文件数据存入content
	}
	myfile.close();
	return characters;
}

int countline(char *t, testfile f1)
{
	ifstream myfile;
	myfile.open(t, ios::in);
	int i = 0;
	string temp;//作为getline参数使用
	if (!myfile.is_open())
	{
		cout << "文件打开失败" << endl;

	}
	while (getline(myfile, temp))
	{
		i++;
	}

	myfile.close();
	return i;
}

void clchange(char *t, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (t[i] >= 65 && t[i] <= 90)
			t[i] += 32;
	}
}

map<string, int> mapword1;

void loadword(char w[])
{
	string wr;
	wr = w;
	map<string, int>::iterator it1 = mapword1.find(wr);
	if (it1 == mapword1.end())
		mapword1.insert(pair<string, int>(wr, 1));
	else
		++it1->second;
}


int countword(char *t, int n)
{
	char temp[4];
	int i = 0, j = 0, flag = 0, words = 0, m = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (!((t[i] >= 48 && t[i] <= 57) || (t[i] >= 97 && t[i] <= 122)))
			continue;
		else
		{
			for (j = 0; j < 4 && i < n; j++)
			{
				if (!((t[i] >= 48 && t[i] <= 57) || (t[i] >= 97 && t[i] <= 122)))
					break;
				temp[j] = t[i++];//temp中存入四个非空格字符
			}
			if (j == 4)
			{
				for (m = 0; m < 4; m++)
				{
					if (temp[m] < 97 || temp[m]>122)
					{
						flag = 1;
						break;//判断这四个字符是否都是字母
					}
				}
				if (flag == 0)//四个字符都是字母的情况，判断为一个单词
				{
					char *w = new char[100];//存放单词 
					for (m = 0; m < 4; m++)
					{
						w[k++] = temp[m];//temp中字符存入w
					}
					while (((t[i] >= 48 && t[i] <= 57) || (t[i] >= 97 && t[i] <= 122)) && i < n)//继续存入单词剩余字符
					{
						w[k++] = t[i++];
					}
					w[k] = '\0';
					loadword(w);//把单词存入map并统计出现频率 
					delete[]w;
					words++;
					k = 0;
				}
				else
				{
					flag = 0;
					j = 0;
				}
			}
		}
	}
	return words;
}

struct sWord
{
	string w;
	int count;

};

void bubble_sort(sWord *s, int len)
{
	int i, j;  sWord temp;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			if (s[j].count < s[j + 1].count)
			{
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
}



int main(int argc, char *argv[])
{
	int i, num = 0, j;
	testfile f1;
	f1.init();
	if (!argv[1])
	{
		cout << "请输入文件名" << endl;
		return 0;
	}
	f1.characters = countcha(argv[1], f1, f1.characters);
	f1.lines = countline(argv[1], f1);
	clchange(f1.content, f1.characters);//大写转小写 
	f1.words = countword(f1.content, f1.characters);
	sWord *ww = new sWord[f1.words];
	map<string, int>::iterator it;
	it = mapword1.begin();
	for (it; it != mapword1.end(); it++)
	{
		ww[num].w = it->first;
		ww[num].count = it->second;
		num++;
	}
	bubble_sort(ww, num);

	cout << "characters: " << f1.characters << endl;
	cout << "words: " << f1.words << endl;
	cout << "lines: " << f1.lines << endl;
	if (num < 10)
	{
		for (i = 0; i < num; i++)
			cout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
	}
	else
	{
		for (i = 0; i < 10; i++)
			cout << "<" << ww[i].w << ">" << ": " << ww[i].count << endl;
	}
	ofstream fout;
	fout.open("result.txt");
	if (!fout)
		cout << "文件打开失败" << endl;
	else
	{
		for (i = 0; i < num; i++)
			fout << ww[i].w << " ";
	}

	delete[]ww;
	free(f1.content);
	return 0;
}



