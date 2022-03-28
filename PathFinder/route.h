#pragma once
// data used to create checkpoints for paths based on the ball's value
class route
{
	int row, column;
public:
	route(int Row, int Column);
	inline void setRow(int a) { row = a; };
	inline void setColumn (int a) { column = a; };
	inline int getRow() { return row; };
	inline int getColumn() { return column; };

};

