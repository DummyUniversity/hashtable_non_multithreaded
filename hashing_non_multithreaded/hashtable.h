#ifndef HASH_TABLE_20260317_H
#define HASH_TABLE_20260317_H

#include <iostream>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::string;
using std::cout;

class Hash_Table
{
	uint32_t noOfSlots = 0;
	vector <list <string>* > slots;
	uint32_t (*str_hash_function)(string, uint32_t);	//https://www.geeksforgeeks.org/cpp/passing-a-function-as-a-parameter-in-cpp/
	//Function pointer so we can easily use any hash function that takes a string and no of slots (for producing a hash that is an index of an array (or slots)).

public:
	Hash_Table(uint32_t noOfSlots, uint32_t (*str_hash_function)(string, uint32_t));
	bool searchInList(list<string>* l, const string& str) const;
	bool search(const string str) const;
	bool insert(const string str);
	void printList(std::list<string>* l) const;
	void print() const;
	void printSlotSizes() const;
	~Hash_Table();
	bool operator == (const Hash_Table &other) const;
};

#endif
