#include "hashtable.h"
#include "hash_functions.h"

#include <chrono>
#include <thread>

Hash_Table::Hash_Table(uint32_t noOfSlots, uint32_t (*str_hash_function)(string, uint32_t))
{
	this->noOfSlots = noOfSlots;
	for (int i = 0; i < noOfSlots; i++)
	{
		slots.push_back(new list<string>);
	}
	
	this->str_hash_function = str_hash_function;

}

bool Hash_Table::searchInList(list<string>* l, const string& str) const
{
	for (const string s : *l)
	{
		if (s == str)
		{
			return true;
		}
	}

	return false;
}

bool Hash_Table::search(const string str) const
{
	int index = str_hash_function(str, noOfSlots);
	return searchInList(slots[index], str);
}

bool Hash_Table::insert(const string str)
{
	bool doesAlreadyExit = false;

	int index = str_hash_function(str, noOfSlots);
//	std::list<std::string>* p = slots[index];

//	if (!searchInList(p, str))
	if (!searchInList(slots[index], str))
	{
//		std::this_thread::sleep_for(std::chrono::milliseconds(11));	//For demonstration purposes
		//https://www.reddit.com/r/cpp_questions/comments/1kruwl9/this_threadsleep_for_and_this_threadsleep_until/		

//		p->push_back(str);	//Actual insertion
		slots[index]->push_back(str);
		doesAlreadyExit = false;
	}
	else
	{
		doesAlreadyExit = true;
	}

	return !doesAlreadyExit;
}

bool Hash_Table::operator == (const Hash_Table &other) const
{

/*Order of words in a slot does not matter*/

	if (slots.size() == other.slots.size())
	{
		for (int i = 0; i < noOfSlots; i++)
		{
			if (slots[i]->size() == other.slots[i]->size())
			{
				for (list<string>::iterator ait = slots[i]->begin(), bit = other.slots[i]->begin();
				ait != slots[i]->end(), bit != other.slots[i]->end();
				ait++, bit++)
				{
					if (!searchInList(slots[i], *bit))
					{
						cout << "Conflict\n";
						return false;
					}
				}
			}
			else
			{
				cout << "Different slot sizes at slot no. " << i << "\n";
				return false;
			}
		}
	}
	else
	{
		cout << "Different sizes\n";
		return false;
	}
	
	return true;
}

void Hash_Table::printList(list<string>* l) const
{
	for (const string str : *l)
	{
		cout << str << " ";
	}
}

void Hash_Table::print() const
{
	for (int i = 0; i < noOfSlots; i++)
	{
		cout << i << ": ";
		printList(slots[i]);
		cout << "\n";
	}
}

void Hash_Table::printSlotSizes() const
{
	for (int i = 0; i < noOfSlots; i++)
	{
		cout << i << ": " << slots[i]->size() << " items\n";
	}
}

Hash_Table::~Hash_Table()
{
	for (int i = 0; i < noOfSlots; i++)
	{
		delete slots[i];
	}
}

