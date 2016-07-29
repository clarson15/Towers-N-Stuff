#include "Enemy.h"



Enemy::Enemy()
{
}

void Enemy::setPosition(float X, float Y)
{
	x = X;
	y = Y;
}

void Enemy::move()
{
	if (direction)
		y += vel;
	if (!direction)
		x += vel;
	dist += vel;
	//if statement to change direction, needs params
}

float Enemy::getX()
{
	return x;
}

float Enemy::getY()
{
	return y;
}


Enemy::~Enemy()
{
}
