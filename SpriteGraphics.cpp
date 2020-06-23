#include "SpriteGraphics.h"
#include <iostream>

// CONSTURCTOR
SpriteGraphics::SpriteGraphics() : sheet(nullptr) {}

// DESTRUCTOR
SpriteGraphics::~SpriteGraphics() {}

// LOAD
bool SpriteGraphics::load(char* filename) { return false; }

// UPDATE
void update(const float xPos, const float yPos, const float angle) {
	std::cout << "Error: WIP" << std::endl;
}

// COLLIDE
bool SpriteGraphics::collide(const SpriteGraphics& otherGraphics) {
	std::cout << "Error: WIP" << std::endl;
}

// DRAW
void SpriteGraphics::draw() {
	std::cout << "Error: WIP" << std::endl;
}