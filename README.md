# hashtable_non_multithreaded

OpenMP multithreaded separate chaining hashtable for strings. The hashtable consists of an `std::vector` of `std::list <std::string>*`. The hashtable does not allow duplicates; on each insertion, it checks if the string does not already exist and only then inserts the string.

A function pointer is used for hash functions that take an `std::string` and the number of slots in the hash table. The function pointer is set in the constructor. This lets us use any hash function for a given table.

The comparison operator `==` is overloaded to check if slots of two tables, on a given index, contain all the same strings. The order of the strings does **not** matter.

The `words.txt` file contains 10,000 words that each contains 100 characters, ranging from ASCII-33 to ASCII-126 which are all readily readable characters (no whitespaces, etc.). There is a small chance that there are duplicate words in the file. The `random_word_generation` folder contains the code the file was generated through.

The main program creates two hashtables and fills them both with the same strings. The first table, referred to as the standard, is filled sequentially. The second is filled by for loop parallelisation. It contains two tests. The first checks if the hashtables are equivalent, using the comparision `==` operator. The second checks if the parallelised insertions are at least as fast as 1.25 times the sequential insertions.

Compile command: `g++ main.cpp hash_functions.cpp hashtable.cpp test.cpp -fopenmp -o a.out`

Run command: `./a.out numOfThreads`
