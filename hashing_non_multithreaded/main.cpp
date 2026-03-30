#include <iostream>
#include <fstream>
#include "test.h"
#include "hashtable.h"
#include "hash_functions.h"
using namespace std;

int main(int argc, char** argv)
{
	int noOfThreads = 2;
	if (argc > 1)
	{
		noOfThreads = atoi(argv[1]);
	}

	int noOfSlots = 100;						//Hash slots or buckets or bins
	Hash_Table r(noOfSlots, &simpleStrHash);	//Reference table
	Hash_Table a(noOfSlots, &simpleStrHash);	//Test hash table

	vector<string> words;
//	std::string filename = "google-10000-english-usa-no-swears-long.txt";
	std::string filename = "words.txt";
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		std::string line;
		while (std::getline(myfile, line))
		{
			words.push_back(line);
		}
	}
	else
	{
		cout << "Error opening input file.\n";
	}

	uint64_t duration = getMillisecondsSinceEpoch();
	for (int i = 0; i < words.size(); i++)
	{
		r.insert(words[i]);
	}
	duration = getMillisecondsSinceEpoch() - duration;
	double standard_duration = duration;

	duration = getMillisecondsSinceEpoch();
	#pragma omp parallel for num_threads(noOfThreads)
	for (int i = 0; i < words.size(); i++)
	{
		a.insert(words[i]);
	}
	duration = getMillisecondsSinceEpoch() - duration;
	double parallelized_duration = duration;

	if (r == a)
	{
		cout << "Test 00 passed: The test hash table matches the reference hash table.\n";
	}
	else
	{
		cout << "Test 00 failed: The test hash table does not match the reference hash table.\n";
	}

	if (parallelized_duration < standard_duration / 1.25)
	{
		cout << "Test 01 passed: The test hash table is faster than 1.25x the reference hash table.\n";
	}
	else
	{
		cout << "Test 01 failed: The test hash table is slower than 1.25x the reference hash table.\n";
	}

	cout << "No of threads = " << noOfThreads << "\n";
	cout << "Standard (sequential for loop) hash table\t: " << standard_duration << " ms\n";
	cout << "Test (parallelized for loop) hash table\t\t: " << parallelized_duration << " ms\n";

	return 0;
}
