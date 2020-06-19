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
// VECTORS CROSS
bool vectorsCross(const std::vector<float>& x1, const std::vector<float>& y1, const std::vector<float>& x2, const std::vector<float>& y2, const float tol = pow(10.f, -6.f)) {
	bool cross = false; //!< Return variable for detecting whether they cross

	// Baseline check
	float minX1 = (x1[0] < x1[1]) ? x1[0] : x1[1];
	float maxX1 = (x1[0] > x1[1]) ? x1[0] : x1[1];
	float minY1 = (y1[0] < y1[1]) ? y1[0] : y1[1];
	float maxY1 = (y1[0] > y1[1]) ? y1[0] : y1[1];
	float minX2 = (x2[0] < x2[1]) ? x2[0] : x2[1];
	float maxX2 = (x2[0] > x2[1]) ? x2[0] : x2[1];
	float minY2 = (y2[0] < y2[1]) ? y2[0] : y2[1];
	float maxY2 = (y2[0] > y2[1]) ? y2[0] : y2[1];

	// Verify their 2D domains overlap, otherwise intersection not possible
	if(minX1 < maxX2 && minX2 < maxX1  && minY1 < maxY2 && minY2 < maxY1) {

		// Check if first vector is vertical
		bool vec1Vert = abs(x1[1] - x1[0]) < tol * std::max(abs(x1[0]), abs(x1[1])); //!< Check if the first vector is vertical to within relative tolerance
		bool vec1Horz = abs(y1[1] - y1[0]) < tol * std::max(abs(y1[0]), abs(y1[1])); //!< Check if the first vector is horizontal to within relative tolerance
		bool vec2Vert = abs(x2[1] - x2[0]) < tol * std::max(abs(x2[0]), abs(x2[1])); //!< Check if the second vector is vertical to within relative tolerance
		bool vec2Horz = abs(y2[1] - y2[0]) < tol * std::max(abs(y2[0]), abs(y2[1])); //!< Check if the second vector is horizontal to within relative tolerance

		// Choose which type of coordinate system based on whether the lines are horizontal
		if (vec1Vert || vec2Vert) {
			if (vec1Vert && vec2Vert) {
				// Both vertical - assume no intersection
				cross = false;
			}
			else if ((vec1Vert && !vec2Horz) || (vec2Vert && !vec1Horz)) {
				// Vertical Vector with no horizontal vectors
				// Switch x and y in point slope form
				float m1 = (x1[1] - x1[0]) / (y1[1] - y1[0]); //<! Slope of first vector, if treated like a line
				float b1 = x1[0] - m1 * y1[0]; //<! Intercept of the first vector, if treated like a line
				float m2 = (x2[1] - x2[0]) / (y2[1] - y2[0]); //<! Slope of second vector, if treated like a line
				float b2 = x2[0] - m2 * y2[0]; //<! Intercept of the second vector, if treated like a line
				float yCross = (b2 - b1) / (m1 - m2); //!< Solution to the interection of the two lines
				if (yCross >= minY1 && yCross >= minY2 && yCross <= maxY1 && yCross <= maxY2) {
					cross = true;
				}
			}
			else if ((vec1Vert && vec2Horz) || (vec1Horz && vec2Vert)) {
				// One vertical and one horizontal - assume intersection based on first check
				cross = true;
			}
			else {
				// Not account for state, dumping current state to see what's going on
				std::cout << "Error: not accounted for state. Dumping truth table:" << std::endl;
				std::cout << "Is Vector 1 vertical? " << vec1Vert << std::endl;
				std::cout << "Is Vector 1 horizontal? " << vec1Vert << std::endl;
				std::cout << "Is Vector 2 vertical? " << vec1Vert << std::endl;
				std::cout << "Is Vector 2 horizaontal? " << vec1Vert << std::endl;
			}
		}
		else if (vec1Horz && vec2Horz) {
			// Both horizontal - assume no intersection
			cross = false;
		}
		else {
			// Neither line is horizontal or vertical, use normal solution
			float m1 = (y1[1] - y1[0]) / (x1[1] - x1[0]); //<! Slope of first vector, if treated like a line
			float b1 = y1[0] - m1 * x1[0]; //<! Intercept of the first vector, if treated like a line
			float m2 = (y2[1] - y2[0]) / (x2[1] - x2[0]); //<! Slope of second vector, if treated like a line
			float b2 = y2[0] - m2 * x2[0]; //<! Intercept of the second vector, if treated like a line
			float xCross = (b2 - b1) / (m1 - m2); //!< Solution to the interection of the two lines
			if (xCross >= minX1 && xCross >= minX2 && xCross <= maxX1 && xCross <= maxX2) {
				cross = true;
			}
		}
	}
	return cross;
}

// LINE CROSS
bool linesCross(const std::vector<float>& x1, const std::vector<float>& y1, const std::vector<float>& x2, const std::vector<float>& y2) {
	// Check that the orientation of the two is different
	return ((y1[1] - y1[0]) * (x2[0] - x1[0]) < (y2[0] - y1[0]) * (x1[1] - x1[0])) != ((y1[1] - y1[0]) * (x2[1] - x1[0]) < (y2[1] - y1[0]) * (x1[1] - x1[0]));
}