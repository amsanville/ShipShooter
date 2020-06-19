#include "GameObject.h"
#include "Game.h"
#include <math.h>
#include <iostream>

// The use sprites flag
const bool GameObject::USE_SPRITES = false;
///////////////////////////////////////////////////////////////////////////////
// GAME OBJECT ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
GameObject::GameObject(const std::vector<float>& new_xBase, const std::vector<float>& new_yBase) : xPos(0.f), yPos(0.f), angle(0.f), xVel(0.f), yVel(0.f) {
	// Conditionally construct the underlying graphics system
	if (USE_SPRITES) {
		vectorGraphics = nullptr;
		spriteGraphics = new SpriteGraphics();
		std::cout << "Error: WIP" << std::endl;
	}
	else {
		spriteGraphics = nullptr;
		vectorGraphics = new VectorGraphics(new_xBase, new_yBase);
	}
}

// DESTRUCTOR
GameObject::~GameObject() {
	// Conditionally delete the underlying graphics system
	if (USE_SPRITES) {
		delete spriteGraphics;
		spriteGraphics = nullptr;
	}
	else {
		delete vectorGraphics;
		vectorGraphics = nullptr;
	}
}

// DRAW
void GameObject::draw() const {
	// Select which drawing method to use based on the USE_SPRITES flag
	if (GameObject::USE_SPRITES) {
		spriteGraphics->draw(xPos, yPos, angle);
	}
	else {
		vectorGraphics->draw(xPos, yPos, angle);
	}
}

// MUTATORS
void GameObject::setX(const float newX) { xPos = newX; }
void GameObject::setY(const float newY) { yPos = newY; }
void GameObject::setAngle(const float newAngle) { angle = newAngle; }
void GameObject::setXVel(const float new_xVel) { xVel = new_xVel; }
void GameObject::setYVel(const float new_yVel) { yVel = new_yVel; }

// ACCESSORS
float GameObject::getX() const { return xPos; }
float GameObject::getY() const { return yPos; }
float GameObject::getAngle() const { return angle; }
float GameObject::getXVel() const { return xVel; }
float GameObject::getYVel() const { return yVel; }

///////////////////////////////////////////////////////////////////////////////
// SHIP ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Base drawing shape for the ship
const std::vector<float> Ship::xBase = { 10, -4, -4 };
const std::vector<float> Ship::yBase = { 0, 3, -3 };

// Constructor
Ship::Ship() : GameObject(Ship::xBase, Ship::yBase){}

// Destructor
Ship::~Ship() {}


///////////////////////////////////////////////////////////////////////////////
// EXTERNAL ALGORITHMS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool vectorsCross(std::vector<float>& x1, std::vector<float>& y1, std::vector<float>& x2, std::vector<float>& y2, float tol = pow(10.f, -6.f) {
	return false;
}