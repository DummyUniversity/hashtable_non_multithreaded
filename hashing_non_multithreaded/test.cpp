#include "test.h"
#include <chrono>
using std::cout;

uint64_t getMillisecondsSinceEpoch()
{
	uint64_t milliseconds = 0;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::system_clock::duration duration_since_epoch = now.time_since_epoch();
	std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch);
	milliseconds = millis.count();
	return milliseconds;
}

int test(char* str)
{
	std::string test = str;

	if (test == "000")
	{
		cout << "Correct\n";
	}

	return 0;
}
