#include "GameObject.h"
#include "Game.h"
#include <math.h>
#include <iostream>
#include <algorithm>

// The use sprites flag
const bool GameObject::USE_SPRITES = false;
///////////////////////////////////////////////////////////////////////////////
// GAME OBJECT ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
GameObject::GameObject(const std::vector<float>& xBase, const std::vector<float>& yBase) : xPos(0.f), yPos(0.f), angle(0.f), xVel(0.f), yVel(0.f) {
	// Conditionally construct the underlying graphics system
	if (USE_SPRITES) {
		vectorGraphics = nullptr;
		spriteGraphics = new SpriteGraphics();
		std::cout << "Error: WIP" << std::endl;
	}
	else {
		spriteGraphics = nullptr;
		vectorGraphics = new VectorGraphics(xBase, yBase);
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
		spriteGraphics->update(xPos, yPos, angle);
		spriteGraphics->draw();
	}
	else {
		spriteGraphics->update(xPos, yPos, angle);
		vectorGraphics->draw();
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

// COLLISIONS
bool GameObject::collide(GameObject& secondObject) {
	if (USE_SPRITES) {
		return spriteGraphics->collide(*secondObject.spriteGraphics);
	}
	else {
		return vectorGraphics->collide(*secondObject.vectorGraphics);
	}
}

///////////////////////////////////////////////////////////////////////////////
// SHIP ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Base drawing shape for the ship
const std::vector<float> Ship::xBase = { 10, -4, -4 };
const std::vector<float> Ship::yBase = { 0, 3, -3 };

// CONSTRUCTOR
Ship::Ship() : GameObject(Ship::xBase, Ship::yBase){}

// DESTRUCTOR
Ship::~Ship() {}

///////////////////////////////////////////////////////////////////////////////
// BULLET /////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Base drawing shape for the bullet
const std::vector<float> Bullet::xBase = { -1, 1 };
const std::vector<float> Bullet::yBase = { 0, 0 };

// CONSTRUCTOR
Bullet::Bullet() : GameObject(Bullet::xBase, Bullet::yBase) {}

// DESTRUCTOR
Bullet::~Bullet() {}

///////////////////////////////////////////////////////////////////////////////
// ASTEROID ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Base shape for the asteroid
const std::vector<float> Asteroid::xBase = {10, 5, -5, -10, -10, -5, 5, 10};
const std::vector<float> Asteroid::yBase = {5, 10, 10, 5, -5, -10, -10, -5};

// CONSTRUCTOR
Asteroid::Asteroid() : GameObject(Asteroid::xBase, Asteroid::yBase) {}

// DESTRUCTOR
Asteroid::~Asteroid() {}
