#include "SpriteGraphics.h"
#include <iostream>

// CONSTURCTOR
SpriteGraphics::SpriteGraphics() : sheet(nullptr) {}

// DESTRUCTOR
SpriteGraphics::~SpriteGraphics() {}

// LOAD
bool SpriteGraphics::load(char* filename) { return false; }

// DRAW
void SpriteGraphics::draw(float xPos, float yPos, float angle) {
	std::cout << "Error: WIP" << std::endl;
}