#include "include/List.h"
#include <iostream>

int main()
{
	MyList test;
	test.push_back_current_level("A");
	test.push_back_next_level("B");
	test.push_back_current_level("C");
	test.print();

	std::cout << "__________________" << std::endl;

	auto it = test.getBegin();
	it = it.nextLevel();
	it.it->print();

	std::cout << "__________________" << std::endl;

	auto a = test.pop();
	test.print();
}