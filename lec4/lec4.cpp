#include <iostream>
#include <vector>
#include "UniquePointer.h"

int main()
	{
	UniquePointer<std::vector<int>> up(new std::vector<int>);

	return 0;
	}