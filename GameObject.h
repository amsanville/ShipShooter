#pragma once
#include "VectorGraphics.h"
#include "SpriteGraphics.h"
#include <vector>
#include <math.h>
//! GameObject.
/*!
Contains the GameObject Class as well as it's child classes. The Game Objects are meant to be the individual game components that can interact on screen. This is a small project so an polymorphism/inheritance based model is used as opposed to an entity-component system. 
*/

//! Parent Game Object Class
/*!
Base class for all game objects that can be rendered and moved around on the screen. Contains a base outline for what each type of game object should be able to do.
*/
class GameObject {
private:
	static const bool USE_SPRITES; //!< Flag for using line art graphics or images
protected:
	VectorGraphics* vectorGraphics; //!< Vector graphics for the game object
	SpriteGraphics* spriteGraphics; //!< Sprite graphics for the game object
	float xPos; //!< x-position of the ship
	float yPos; //!< y-position of the ship
	float angle; //!< Angle of the object in radians
	float xVel;	//!< The x-velocity
	float yVel; //!< The y-velocity
public:
	//! Constructor
	/*!
	Starts the graphics system based on the USE_SPRITES flag.
	@param new_xBase
	@param new_yBase The base vectors 
	*/
	GameObject(const std::vector<float>& new_xBase, const std::vector<float>& new_yBase);

	//! Destructor
	/*!
	// TODO
	*/
	~GameObject();

	//! Draw
	/*!
	Draw the object according to whatever type of object it is. Uses the USE_SPRITES flag to determine how to draw the object.
	*/
	void draw() const;

	//! Draw Debug
	/*!
	A debugging method for drawing different objects. Meant to provide a way to examine what's actually happening when different game objects are drawn.
	*/
	//virtual void drawDebug() = 0;
	
	//////////////////////////////////////////////////////////////////////////////
	// MUTATORS //////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//! Set x-position
	/*!
	Sets the x-position to the provided value.
	*/
	void setX(const float newX);

	//! Set y-position
	/*!
	Sets the y-position to the provided value.
	*/
	void setY(const float newX);

	//! Set Angle
	/*!
	Sets the angle to the provided value.
	*/
	void setAngle(const float newX);

	//! Set x-Velocity
	/*!
	Sets the x-velocity of the Game Object.
	@param new_xVel The new x-velocity.
	*/
	void setXVel(const float new_xVel);

	//! Set y-velocity
	/*!
	Sets the y-velocity of the Game Object.
	@oaram new_yVel The new y-velocity
	*/
	void setYVel(const float new_yVel);
	
	//////////////////////////////////////////////////////////////////////////////
	// ACCESSORS /////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//! Get x-position
	/*!
	Returns the x-position of the ship
	*/
	float getX() const;

	//! Get y-position
	/*!
	Returns the y-position of the ship.
	*/
	float getY() const;

	//! Get x-position
	/*!
	Returns the angle the ship is at.
	*/
	float getAngle() const;

	//! Get x-velocity
	/*!
	Get the game objects x-velocity.
	@return The x-velocity of the Game Object.
	*/
	float getXVel() const;

	//! Get y-velocity
	/*!
	Get the game objects y-velocity.
	@return The y-velocity of the Game Object.
	*/
	float getYVel() const;
};

//! Ship Class
/*!
Player ship, meant to encapsulate all the behavior that the player's ship will need. Basic vector graphic is meant to be a triangle.
*/
class Ship : public GameObject {
private:
	static const std::vector<float> xBase; //!< Base shape for rendering, x-values of vectors
	static const std::vector<float> yBase; //!< Base shape for rendering, y-values of vectors
public:
	//! Constructor
	/*!
	// TODO
	*/
	Ship();

	//! Destructor
	/*!
	// TODO
	*/
	~Ship();
};

/*
class Bullet {
private:
public:
};

class Asteroid {
private:
public:
};

class Alien {
private:
public:
};
*/

///////////////////////////////////////////////////////////////////////////////
// EXTERNAL ALGORITHMS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Note: these are external because they can be applied more generally. The
// idea here is to explore different collision algorithms.
bool vectorsCross(std::vector<float>& x1, std::vector<float>& y1, std::vector<float>& x2, std::vector<float>& y2, float tol = pow(10.f, -6.f);