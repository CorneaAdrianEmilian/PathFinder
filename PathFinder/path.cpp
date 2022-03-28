#include "path.h"

Path::Path(int a,int b)
{
	width = a;
	height = b;
}
void Path::makeGrid()
{
	for(int i=0;i<height;i++)
	{
		std::string temp;
		std::cin >>temp;
		theGrid.emplace_back(temp);
	}
}

void Path::searchBalls()
{
	for(int i=0;i<height;i++)
	{
		for (int j = 0; j < width; j++)
		{
		std::string temp = theGrid.at(i).substr(j, 1);
			if (temp.at(0) > 47 && temp.at(0) < 58)
			{
			std::shared_ptr<ball> var = std::make_shared<ball>(i, j, std::stoi(temp));
			ballsFound.emplace_back(var);
			}
		}
	}
}

void Path::ballManager()
{
	for (int i = 0; i < ballsFound.size(); i++)
	{
		pathFinder(ballsFound.at(i)->getRow(), ballsFound.at(i)->getColumn(), ballsFound.at(i)->getValue(), 0, ballsFound.at(i)->routes,true,true,true,true,ballsFound.at(i) ->potentialHoles);
	}
	std::sort(ballsFound.begin(), ballsFound.end(), [](const std::shared_ptr<ball>& first, const std::shared_ptr<ball>& second) {
		return first->routes.size() < second->routes.size(); }
	);
	for(int i=0;i<ballsFound.size();i++)
	{
		writeInitialRoutes(ballsFound.at(i));
	}
}

void Path::pathFinder(int row, int column, int value, int currentMoves, std::vector<std::vector<std::shared_ptr<route>>>& routes, bool up, bool down, bool right, bool left, std::vector<std::shared_ptr<route>>& pHoles)
{
	std::shared_ptr<route>temp = std::make_shared<route>(row, column);
	currentRoute.emplace_back(temp);
	if (theGrid.at(row).at(column) == 'H')
	{
			routes.emplace_back(currentRoute);
			currentRoute.pop_back();
			pHoles.emplace_back(std::make_shared<route>(row, column));
	}
	else 
	{
		if (theGrid.at(row).at(column) != 'X')
		{
			if (value > 0) 
			{
				if (up) {
					if (row - value > -1)
					{
						if(sequenceCheck(row-1,column,row-value,column))
						pathFinder(row - value, column, value - 1, ++currentMoves, routes, true, false, true, true,pHoles);
					}
				}
				if (down) {
					if (row < height - value)
					{
						if (sequenceCheck(row+1, column, row + value, column))
						pathFinder(row + value, column, value - 1, ++currentMoves, routes, false, true, true, true, pHoles);
					}
				}
				if (left) {
					if (column - value > -1)
					{
						if (sequenceCheck(row, column-1, row, column-value))
						pathFinder(row, column - value, value - 1, ++currentMoves, routes, true, true, false, true, pHoles);
					}
				}
				if (right) {
					if (column < width - value)
					{
						if (sequenceCheck(row, column+1, row, column+value))
						pathFinder(row, column + value, value - 1, ++currentMoves, routes, true, true, true, false, pHoles);
					}
				}
				currentRoute.pop_back();
			}
			else {
				currentRoute.pop_back();
			}

		}else
			currentRoute.pop_back();

	}
}
bool Path::pathCheck(std::vector<std::shared_ptr<route>>& theRoute)
{
	if (theGrid.at(theRoute.back()->getRow()).at(theRoute.back()->getColumn()) != 'H')
		return false;
	std::string temp;
	std::vector<std::shared_ptr<route>>::iterator it;
	for (it = theRoute.begin(); it != theRoute.end() - 1; it++) {
		int currentRow = (*it)->getRow(), currentColumn = (*it)->getColumn(), nextRow= (*(it+1))->getRow(), nextColumn= (*(it + 1))->getColumn();
		while (currentRow != nextRow || currentColumn != nextColumn)
		{
			if (currentRow < nextRow)
			{
				temp = theGrid.at(++currentRow).substr(currentColumn, 1);
				if (temp.at(0) > 47 && temp.at(0) < 58)
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '>')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '<')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == 'v')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '^')
					return false;
			}
			else if (currentRow > nextRow)
			{
				temp = theGrid.at(--currentRow).substr(currentColumn, 1);
				if (temp.at(0) > 47 && temp.at(0) < 58)
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '>')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '<')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == 'v')
					return false;
				else if (theGrid.at(currentRow).at(currentColumn) == '^')
					return false;
			}
			else
			{
				if (currentColumn < nextColumn)
				{
					temp = theGrid.at(currentRow).substr(++currentColumn, 1);
					if (temp.at(0) > 47 && temp.at(0) < 58)
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '>')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '<')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == 'v')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '^')
						return false;
				}
				else if (currentColumn > nextColumn)
				{
					temp = theGrid.at(currentRow).substr(--currentColumn, 1);
					if (temp.at(0) > 47 && temp.at(0) < 58)
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '>')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '<')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == 'v')
						return false;
					else if (theGrid.at(currentRow).at(currentColumn) == '^')
						return false;
				}
			}
		}
	}
	return true;
}

void Path::writeInitialRoutes(std::shared_ptr<ball> currentBall)
{

	bool routeDelivered = false;
	
	for (int i = 0; i < currentBall->routes.size(); i++)
	{
		if (pathCheck(currentBall->routes[i]))
		{
			writeRoute(currentBall,currentBall->routes.at(i));
			routeDelivered = true;
			break;
		}
	}
	if (!routeDelivered) {
		if (!changePath(currentBall))
			pathCollision(currentBall);
	}

}
bool Path::changePath(std::shared_ptr<ball>currentBall)
{
	if (currentBall->potentialHoles.size() == 1)
		return false;
	removeRoute(currentBall->getCurrentPath());

	for (int i = 0; i <currentBall->potentialHoles.size(); i++)
	{

		if(currentBall->getCurrentHole()!=nullptr)
		{
			if (currentBall->getCurrentHole()->getColumn() == currentBall->potentialHoles.at(i)->getColumn() && currentBall->getCurrentHole()->getRow() == currentBall->potentialHoles.at(i)->getRow())
				continue;
			else 
			{
				if (pathCheck(currentBall->routes.at(i)))
				{
					writeRoute(currentBall,currentBall->routes.at(i));
					return true;
				}
				else {
					for (int j = 0; j < ballsFound.size(); j++)
					{
						if (ballsFound.at(j)->getCurrentHole() != nullptr) {
							if (ballsFound.at(j)->getCurrentHole()->getColumn() == currentBall->potentialHoles.at(i)->getColumn() && ballsFound.at(j)->getCurrentHole()->getRow() == currentBall->potentialHoles.at(i)->getRow()) {
								if (changePath(ballsFound.at(j))) 
								{
									if (pathCheck(currentBall->routes.at(i)))
									{
										writeRoute(currentBall,currentBall->routes.at(i));
										return true;
									}

								}
							}
						}
					}
				}
			}

		}
		else 
		{
			if (pathCheck(currentBall->routes.at(i)))
			{
				writeRoute(currentBall, currentBall->routes.at(i));
				return true;
			}
			else {
				for (int j = 0; j < ballsFound.size(); j++)
				{
					if (ballsFound.at(j)->getCurrentHole() != nullptr) {
						if (ballsFound.at(j)->getCurrentHole()->getColumn() == currentBall->potentialHoles.at(i)->getColumn() && ballsFound.at(j)->getCurrentHole()->getRow() == currentBall->potentialHoles.at(i)->getRow())
						{
							if (changePath(ballsFound.at(j)))
							{
								if (pathCheck(currentBall->routes.at(i)))
								{
									writeRoute(currentBall, currentBall->routes.at(i));
									return true;

								}
							}	
						}
					}
				}
			}
		}
	}
	writeRoute(currentBall, currentBall->getCurrentPath());
	return false;
}


void Path::removeRoute(std::vector<std::shared_ptr<route>>  currentPath)
{
	if (currentPath.size() != 0)
	{
			std::vector<std::shared_ptr<route>>::iterator it = currentPath.begin();
			for (it; it != currentPath.end() - 1; it++)
			{
				int row1 = (*it)->getRow(), row2 = (*(it + 1))->getRow(), column1 = (*it)->getColumn(), column2 = (*(it + 1))->getColumn();
				while (row1 != row2 || column1 != column2)
				{

					if (row1 < row2)
					{
						theGrid.at(row1++).at(column1) = '.';
					}
					else if (row1 > row2)
					{
						theGrid.at(row1--).at(column1) = '.';
					}
					else
					{
						if (column1 < column2)
						{
							theGrid.at(row1).at(column1++) = '.';
						}
						else
						{
							theGrid.at(row1).at(column1--) = '.';
						}
					}
				}
				if (it == currentPath.end() - 2)
				{
					theGrid.at((*(it + 1))->getRow()).at((*(it + 1))->getColumn()) = 'H';
				}
			}
	}
}
void Path::writeRoute(std::shared_ptr<ball> currentBall,std::vector<std::shared_ptr<route>> currentRoute)
{
	if (currentRoute.size() > 0) {
		std::vector<std::shared_ptr<route>>::iterator it;
		for (it = currentRoute.begin(); it != currentRoute.end() - 1; it++)
		{
			int row1 = (*it)->getRow(), row2 = (*(it + 1))->getRow(), column1 = (*it)->getColumn(), column2 = (*(it + 1))->getColumn();
			while (row1 != row2 || column1 != column2)
			{

				if (row1 < row2)
				{
					theGrid.at(row1++).at(column1) = 'v';
				}
				else if (row1 > row2)
				{
					theGrid.at(row1--).at(column1) = '^';
				}
				else
				{
					if (column1 < column2)
					{
						theGrid.at(row1).at(column1++) = '>';
					}
					else
					{
						theGrid.at(row1).at(column1--) = '<';
					}
				}
			}
			if (it == currentRoute.end() - 2) {
				theGrid.at((*(it + 1))->getRow()).at((*(it + 1))->getColumn()) = '.';

				if (currentBall->getCurrentHole() == nullptr)
				{
					currentBall->setCurrentHole(std::make_shared<route>((*(it + 1))->getRow(), (*(it + 1))->getColumn()));
				}
				else {
					currentBall->getCurrentHole()->setRow((*(it + 1))->getRow());
					currentBall->getCurrentHole()->setColumn((*(it + 1))->getColumn());
				}
				currentBall->setCurrentPath(currentRoute);
			}
		}
	}
}
bool Path::sequenceCheck(int row, int column, int sRow, int sColumn)
{
	char var = theGrid.at(sRow).at(sColumn);
	if (var > 47 && var < 58)
		return false;
	while (row != sRow || column != sColumn) 
	{
		if (row < sRow) 
		{
			char temp = theGrid.at(row).at(column);
			if (theGrid.at(row).at(column) == 'H')
				return false;
			else if (temp > 47 && temp < 58)
				return false;
			row++;
		}
		else if(row>sRow)
		{
			char temp = theGrid.at(row).at(column);
			if (theGrid.at(row).at(column) == 'H')
				return false;
			else if (temp > 47 && temp < 58)
				return false;
			row--;
		}
		else 
		{
		if(column<sColumn)
		{
			char temp = theGrid.at(row).at(column);
			if (theGrid.at(row).at(column) == 'H')
				return false;
			else if (temp > 47 && temp < 58)
				return false;
			column++;
		}else if(column>sColumn)
			{
			char temp = theGrid.at(row).at(column);
			if (theGrid.at(row).at(column) == 'H')
				return false;
			else if (temp > 47 && temp < 58)
				return false;
			column--;
			}
		}
	}
	return true;
}
void Path::pathCollision(std::shared_ptr<ball> currentBall)
{
	bool conditon = false;
	for (int i = 0; i < currentBall->potentialHoles.size(); i++)
	{
		if (conditon)
			break;
		if (theGrid.at(currentBall->potentialHoles.at(i)->getRow()).at(currentBall->potentialHoles.at(i)->getColumn()) != 'H')
			continue;
		else 
		{
			std::vector<std::shared_ptr<route>>::iterator it;
			for (it =currentBall->routes.at(i).begin(); it != currentBall->routes.at(i).end() - 1; it++)
			{
				if (conditon)
					break;
				int row1 = (*it)->getRow(), row2 = (*(it + 1))->getRow(), column1 = (*it)->getColumn(), column2 = (*(it + 1))->getColumn();
				while (row1 != row2 || column1 != column2)
				{

					if (row1 < row2)
					{
						if(theGrid.at(row1).at(column1) == 'v')
						{
							if (changePath(findOwner(row1, column1))) 
							{
								writeRoute(currentBall, currentBall->routes.at(i));
								conditon = true;
								break;
							}
						}
						else if (theGrid.at(row1).at(column1) == '^') 
						{
							if (changePath(findOwner(row1, column1)))
							{
								writeRoute(currentBall, currentBall->routes.at(i));
								conditon = true;
								break;
							}
						}
						else if (theGrid.at(row1).at(column1) == '>')
						{
							if (changePath(findOwner(row1, column1)))
							{
								writeRoute(currentBall, currentBall->routes.at(i));
								conditon = true;
								break;
							}
						}
						else if (theGrid.at(row1).at(column1) == '<')
						{
							if (changePath(findOwner(row1, column1)))
							{
								writeRoute(currentBall, currentBall->routes.at(i));
								conditon = true;
								break;
							}
						}
						row1++;
					}
					else if (row1 > row2)
					{
						{
							if (theGrid.at(row1).at(column1) == 'v')
							{
								if (changePath(findOwner(row1, column1)))
								{
									writeRoute(currentBall, currentBall->routes.at(i));
									conditon = true;
									break;
								}
							}
							else if (theGrid.at(row1).at(column1) == '^')
							{
								if (changePath(findOwner(row1, column1)))
								{
									writeRoute(currentBall, currentBall->routes.at(i));
									conditon = true;
									break;
								}
							}
							else if (theGrid.at(row1).at(column1) == '>')
							{
								if (changePath(findOwner(row1, column1)))
								{
									writeRoute(currentBall, currentBall->routes.at(i));
									conditon = true;
									break;
								}
							}
							else if (theGrid.at(row1).at(column1) == '<')
							{
								if (changePath(findOwner(row1, column1)))
								{
									writeRoute(currentBall, currentBall->routes.at(i));
									conditon = true;
									break;
								}
							}
							row1--;
						}
					}
					else
					{
						if (column1 < column2)
						{
							{
								if (theGrid.at(row1).at(column1) == 'v')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '^')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '>')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '<')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								column1++;
							}
						}
						else
						{
							{
								if (theGrid.at(row1).at(column1) == 'v')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '^')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '>')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								else if (theGrid.at(row1).at(column1) == '<')
								{
									if (changePath(findOwner(row1, column1)))
									{
										writeRoute(currentBall, currentBall->routes.at(i));
										conditon = true;
										break;
									}
								}
								column1--;
							}
						}
					}
				}
			}
		}
	}
}
std::shared_ptr<ball> Path::findOwner(int row, int column)
{
	char currentPosition = theGrid.at(row).at(column);
	bool condition = true;
	while (condition) 
	{
		switch (currentPosition)
		{
		case 'v':
			if (theGrid.at(++row).at(column) == '.')
			{
				condition = false;
				break;
			}
			else
				currentPosition = theGrid.at(row).at(column);
			break;
		case '^':
			if (theGrid.at(--row).at(column) == '.')
			{
				condition = false;
				break;
			}
			else
				currentPosition = theGrid.at(row).at(column);
			break;
		case '>':
			if (theGrid.at(row).at(++column) == '.')
			{
				condition = false;
				break;
			}
			else
				currentPosition = theGrid.at(row).at(column);
			break;
		case '<':
			if (theGrid.at(row).at(--column) == '.')
			{
				condition = false;
				break;
			}
			else
				currentPosition = theGrid.at(row).at(column);
			break;
		}
	}
	for (int i = 0; i < ballsFound.size();i++) 
	{
		if (ballsFound.at(i)->getCurrentHole() != nullptr) {
			if (ballsFound.at(i)->getCurrentHole()->getColumn() == column && ballsFound.at(i)->getCurrentHole()->getRow() == row)
				return ballsFound.at(i);
		}
	}
}
void Path::printGrid()
{
	for(int i=0;i<theGrid.size();i++)
	{
	for(int j =0;j<width;j++)
	{
		if (theGrid.at(i).at(j) == 'X')
			theGrid.at(i).at(j) = '.';
	}
	}
	for(int i=0;i<theGrid.size();i++)
	{
		std::cout << theGrid.at(i)<< std::endl;
	}
}
