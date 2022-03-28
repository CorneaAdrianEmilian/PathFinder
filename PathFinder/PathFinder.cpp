
#include <iostream>
#include "path.h"

int main()
{
	int width, height;
	std::cin >> width >> height;
	std::unique_ptr<Path> test = std::make_unique<Path>(width, height);
	test->makeGrid();
	test->searchBalls();
	test->ballManager();
	test->printGrid();

}


