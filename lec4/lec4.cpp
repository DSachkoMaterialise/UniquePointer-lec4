#include <iostream>
#include <vector>
#include "UniquePointer.h"
#include "SharedPointer.h"

int main(int argc, char** args)
	{
	SharedPointer<std::vector<int>> up(new std::vector<int>());
	auto ptr = up;
	ptr->push_back(1);
	std::cout << ptr.use_count();
	return 0;
	}