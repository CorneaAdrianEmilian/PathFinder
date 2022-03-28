#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "ball.h"
#include <memory>
#include <algorithm>

class Path
{
	int width, height;
	std::vector<std::string>theGrid;
	std::vector<std::shared_ptr<ball>> ballsFound;
	//vector that helps the pathFinder method
	std::vector<std::shared_ptr<route>>currentRoute;
	//recursive method that finds all the possible paths for a given ball
	void pathFinder(int row, int column, int value,int currentMoves, std::vector<std::vector<std::shared_ptr<route>>>&routes,bool up,bool down,bool right,bool left,std::vector<std::shared_ptr<route>>& pHoles);
	//method to check if a path can be taken without violating the rules
	bool pathCheck(std::vector<std::shared_ptr<route>>& theRoute);
	//recursive method to change multiple balls's hole thus providing a free hole for the given ball
	bool changePath(std::shared_ptr<ball>currentBall);
	void removeRoute(std::vector<std::shared_ptr<route>> currentPath);
	void writeRoute(std::shared_ptr<ball> currentBall, std::vector<std::shared_ptr<route>> currentRoute);
	//assures that the rules are met in between the "checkpoints" of the path
	bool sequenceCheck(int row, int column, int sRow, int sColumn);
	//method that changes one ball's path that collide with the given one's path thus providing a free route
	void pathCollision(std::shared_ptr<ball> currentBall);
	// method that finds the owner of a path
	std::shared_ptr<ball> findOwner(int row, int column);
	void writeInitialRoutes(std::shared_ptr<ball> currentBall);
public:
	Path(int a,int b);
	void makeGrid();
	void searchBalls();
	void ballManager();
	void printGrid();
	
};

