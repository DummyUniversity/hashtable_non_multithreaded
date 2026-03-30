#include "hash_functions.h"

#include <iostream>
using namespace std;

uint32_t simpleStrHash(const string str, const uint32_t noOfSlots)
{
	uint32_t index = 0;

	for (int i = 0; i < str.size(); i++)
	{
		index += str[i];
	}

	index = index % noOfSlots;
	return index;
}
