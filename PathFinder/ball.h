#pragma once
#include "route.h"
#include <vector>
#include <string>
#include <memory>
class ball
{
	int row, column, value;
	std::shared_ptr<route> currentHole;
	std::vector<std::shared_ptr<route>> currentPath;
public:
	inline std::vector<std::shared_ptr<route>> getCurrentPath() { return currentPath; };
	inline void setCurrentPath(std::vector<std::shared_ptr<route>> x) { currentPath = x; };

	std::vector<std::shared_ptr<route>> potentialHoles;
	std::vector<std::vector<std::shared_ptr<route>>>routes;

	const inline std::shared_ptr <route> getCurrentHole() { return currentHole; };
	inline void setCurrentHole(std::shared_ptr<route> x) { currentHole = x; };
	ball(int a, int b,int val);
	const inline int getRow() {return row;};
	const inline int getColumn() { return column; };
	inline void setRow(int a) { row = a; };
	inline void setColumn(int a) { column = a; };
	const inline int getValue() { return value; };
	bool operator <(const ball& otherBall) const;
};

