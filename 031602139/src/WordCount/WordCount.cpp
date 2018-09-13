
#include "pch.h"

int main(int argc, char *argv[])
{
	counter *myCounter = new counter;
	myCounter->initInFilename(argv[1]);
	//char tempName[] = "input.txt";
	//myCounter->initInFilename(tempName);
	
	//	cout<<__LINE__<<endl;
	myCounter->countCharLine();
	//	cout<<__LINE__<<endl;
	myCounter->countWord();
	//	cout<<__LINE__<<endl;
	myCounter->frequency();
	//	cout<<__LINE__<<endl;

	char outFilename[] = "result.txt";
	myCounter->print(outFilename);

	delete myCounter;
	//  getchar();
	return 0;
}

