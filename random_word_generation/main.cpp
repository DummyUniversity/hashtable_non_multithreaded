#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char** argv)
{
	srand (time(NULL));

	int noOfWords = 10000;
	int wordLength = 100;	//-1 for random
	int minWordLength = 100;
	int maxWordLength = 100;
	char filename[] = "words.txt";
	char* outputFilename = filename;

	char** words = new char*[noOfWords];

	for (int i = 0; i < noOfWords; i++)
	{
		int thisWordLength = wordLength;
		if (wordLength < 0)
		{
			thisWordLength = rand() % (maxWordLength + 1) + minWordLength;
		}

		words[i] = new char[thisWordLength + 1];
		for (int j = 0; j < thisWordLength; j++)
		{
			words[i][j] = rand() % 94 + 33;	//ASCII-33 to ASCII-126
			//char c = rand() % 94 + 33;
		}

		words[i][thisWordLength] = '\0';
	}

	ofstream myfile(outputFilename);
	for (int i = 0; i < noOfWords; i++)
	{
		myfile << words[i] << "\n";
	}

	for (int i = 0; i < noOfWords; i++)
	{
		delete[] words[i];
	}
	delete[] words;

	return 0;
}
