#pragma once
class Enemy
{
public:
	Enemy();
	void setPosition(float x, float y);
	void move(); //add params
	float getX();
	float getY();
	~Enemy();
private:
	bool direction; //	0 = left right	1 = up down
	float x, y, vel, dist;
};

