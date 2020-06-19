#pragma once
#include <vector>

//! Vector Graphics Class
/*!
Implements a graphics system based on drawing lines from point to point, as stored in vectors. The premise is that the user should provide a base shape centered at (0,0) created out of vertices. The shape is drawn by connecting the dots in the sequence provided, closing the shape by connecting the last and the first coordinates. The shape can then be translated and rotated into place before rendering.
*/
class VectorGraphics {
private:
	std::vector<float> xBase; //!< x-coordinates of the vectors that make the base line art for the object
	std::vector<float> yBase; //!< y-coordinates of the vectors that make the base line art for the object
	std::vector<float> xCurr; //!< Current list of x-positions
	std::vector<float> yCurr; //!< Current list of y-positions
public:
	//! Constructor
	/*!
	Builds base vectors out of provided base vectors.
	@param new_xBase The x-positions of the vectors of the base shape
	@param new_yBase The y-positions of the vectors of the base shape
	*/
	VectorGraphics(const std::vector<float>& new_xBase, const std::vector<float>& new_yBase);
	
	//! Destuctor
	/*!
	Expect empty destructor as class contains all variables.
	*/
	~VectorGraphics();

	//! Draw
	/*!
	Draws the provided lists of vectors by first transforming (rotating and translating them) to the appropriate position based in the inputted value and then drawing them using SDL_RenderDrawLineF. Draws in white.
	@param xPos The x-position for translation.
	@param yPos The y-position for translation.
	@param angle The final angle. Note: angles based on screen coordinate system (0 horizontal to the right with positive values increasing clockwise). Angles should be in radians.
	*/
	void draw(const float xPos, const float yPos, const float angle);

	//! Draw for debugging
	/*!
	Uses the same method as draw but highlights all the vertices in red.
	*/
	void drawDebug(const float xPos, const float yPos, const float angle);
};

//! Transform
/*!
Creates a transformed copy of the provided base vectors based on the given rotation angle and provided translation. The idea is that the base is a provided constant and this transformed copy will be used for renderering.
@param xBase The base x-values of the vectors
@param yBase The base y-values of the vectors
@param xPos The x-position for translation
@param yPos The y-position for translation
@param angle The angle of rotation, due to the coordinate system of computer screens this zero is a horizontal line to the right and increasing angle is clockwise rotation
@param xFinal The transformed x-values of the vectors
@param yFinal The transformed y-values of the vectors
*/
void transform(const std::vector<float>& xBase, const std::vector<float>& yBase, const float xPos, const float yPos, const float angle, std::vector<float>& xFinal, std::vector<float>& yFinal);

//! Transform - weird
/*!
From a sign error bug, I accidentally created a weird spinning animation. This is just that same code.
@param xBase The base x-values of the vectors
@param yBase The base y-values of the vectors
@param xPos The x-position for translation
@param yPos The y-position for translation
@param angle The angle of rotation, due to the coordinate system of computer screens this zero is a horizontal line to the right and increasing angle is clockwise rotation
@param xFinal The transformed x-values of the vectors
@param yFinal The transformed y-values of the vectors
*/
void transformWeird(const std::vector<float>& xBase, const std::vector<float>& yBase, const float xPos, const float yPos, const float angle, std::vector<float>& xFinal, std::vector<float>& yFinal);