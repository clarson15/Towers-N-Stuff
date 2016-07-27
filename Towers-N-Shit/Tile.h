#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
public:
	Tile();
	void reset();
	void toggle();
	bool getOccupied();
	~Tile();
private:
	bool occupied;
};

