#include <iostream>
#include <vector>
#include "UniquePointer.h"

int main()
	{
	UniquePointer<std::vector<int>> up(new std::vector<int>), n;
	up.swap(n);
	return 0;
	}