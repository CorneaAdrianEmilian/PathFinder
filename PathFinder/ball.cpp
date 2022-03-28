#include "ball.h"
ball::ball(int a,int b,int val) {
	row = a;
	column = b;
	value = val;
}

bool ball::operator < (const ball& otherBall) const
{
	return (value < otherBall.value);
}


