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

	if (!searchInList(slots[index], str))
	{
//		std::this_thread::sleep_for(std::chrono::milliseconds(11));	//For demonstration purposes
		//https://www.reddit.com/r/cpp_questions/comments/1kruwl9/this_threadsleep_for_and_this_threadsleep_until/		

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
				for (list<string>::iterator bit = other.slots[i]->begin(); bit != other.slots[i]->end(); bit++)
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

/*

Edit (2026 05 24):

The line 

				for (list<string>::iterator bit = other.slots[i]->begin(); bit != other.slots[i]->end(); bit++)

initially read

				for (list<string>::iterator ait = slots[i]->begin(), bit = other.slots[i]->begin();
				ait != slots[i]->end() , bit != other.slots[i]->end();
				ait++, bit++)

and caused this warning

				warning: ignoring return value of 
				‘bool std::operator!=(const _List_iterator<__cxx11::basic_string<char> >::_Self&, const _List_iterator<__cxx11::basic_string<char> >::_Self&)’, 
				declared with attribute ‘nodiscard’ [-Wunused-result]

That is because 

				ait != slots[i]->end() , bit != other.slots[i]->end();

would not cause the loop to terminate even if this->slots[i] is smaller than other.slots[i] because with the comma operator between the two 
conditions, only the second is actually checked.

				ait != slots[i]->end() 

is evaluated, but its bool result is completely ignored.

The way the code is written, this should never be a problem because the loop is preceded by

				if (slots[i]->size() == other.slots[i]->size())

It is still best to replace the comma operator with the && operator.

				for (list<string>::iterator ait = slots[i]->begin(), bit = other.slots[i]->begin();
				ait != slots[i]->end() && bit != other.slots[i]->end();
				ait++, bit++)

However, it is even better to replace it with

				for (list<string>::iterator bit = other.slots[i]->begin(); bit != other.slots[i]->end(); bit++)

I had realized this particular bit when I initially wrote this code but I was too frustrated at that point to improve it. In any case, 
I have updated it now.

*/


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

