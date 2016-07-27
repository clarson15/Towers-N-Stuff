#include "Tile.h"



Tile::Tile()
{
	occupied = false;
}
void Tile::reset() {
	occupied = false;
}
void Tile::toggle() {
	occupied = true;
}
bool Tile::getOccupied() {
	return occupied;
}
Tile::~Tile()
{
}
