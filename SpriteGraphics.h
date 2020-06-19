#pragma once
#include <SDL.h>

//! Sprite Graphics Class
/*!
Implements a sprite based graphics system.
*/
class SpriteGraphics {
private:
	SDL_Texture* sheet; //!< The sprite sheet
public:
	//! Constructor
	SpriteGraphics();

	//! Destructor
	~SpriteGraphics();

	//! Load
	/*!
	Load the sprite sheet from the provided file.
	@param 
	@return True, if successful.
	*/
	bool load(char* filename);

	//! Draw
	/*!
	Draws the sprite in the position and at the angle provided.
	@param xPos The x-position desired for the sprite
	@param yPos The y-position desired for the sprite
	@angle angle The angle the sprite should be rendered at.
	*/
	void draw(const float xPos, const float yPos, const float angle = 0.0f);
};