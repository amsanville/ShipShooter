#pragma once
#include <vector>

//! Vector Graphics Class
/*!
Implements a graphics system based on drawing lines from point to point, as stored in vectors. The premise is that the user should provide a base shape centered at (0,0) created out of vertices. The shape is drawn by connecting the dots in the sequence provided, closing the shape by connecting the last and the first coordinates. The shape can then be translated and rotated into place before rendering. Because the graphical system determines what hit boxes reasonably look-like, collision handling is also incorporated into graphics.

I chose to separate this from the base GameObject as a means of allowing for both a sprite-based and direct pixel drawing based graphics systems. By creating a separate class entirely, this allows me to easily swap in and out the graphics system of choice. Note, this design model works along the same lines as the ECS model.
*/
class VectorGraphics {
private:
	std::vector<float> xCurr; //!< The x-component of the up-to-date transformed version of the base vector
	std::vector<float> yCurr; //!< The y-component of the up-to-date transformed version of the base vector
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

	//! Update
	/*!
	Translates the base shape the position and orientation provided, storing it in xCurr and yCurr.
	@param xPos The x-position for translation.
	@param yPos The y-position for translation.
	@param angle The final angle. Note: angles based on screen coordinate system (0 horizontal to the right with positive values increasing clockwise). Angles should be in radians.
	*/
	void update(const std::vector<float>& new_xBase, const std::vector<float>& new_yBase, const float xPos, const float yPos, const float angle = 0.f);

	//! Collision detection
	/*!
	Detects collision objects between two objects represented with vector graphics. Finds whether any of the vectors provided for the object cross. If they do, then the two objects collide. This means that all pairs of vectors between the two objects are tested, resulting in n*k tests, where n and k are the number of vectors in each 2D shape.

	There is a robust fast algorithm for collision detection for convex polygons. This algorithm represents a first pass at collision detection and it works whether or not a polygon is convex. Note, though, if one object can entirely contain another with no lines crossing, this is not considered a collision.
	*/
	bool collide(const VectorGraphics& otherGraphics);

	//! Draw
	/*!
	TODO
	Draws the provided lists of vectors by first transforming (rotating and translating them) to the appropriate position based in the inputted value and then drawing them using SDL_RenderDrawLineF. Draws in white.
	*/
	void draw();

	//! Draw for debugging
	/*!
	Uses the same method as draw but highlights all the vertices in red.
	@param collision Flag that highlights the object in yellow. Meant to provide a means of testing collisions.
	*/
	void drawDebug(const bool collision = false);
};
///////////////////////////////////////////////////////////////////////////////
// EXTERNAL ALGORITHMS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Note: these are external because they can be applied more generally. The
// idea here is to explore different collision algorithms.

//! Transform
/*!
Creates a transformed copy of the provided base vectors based on the given rotation angle and provided translation. The idea is that the base is a provided constant and this transformed copy will be used for renderering.
@param xBase The base x-values of the vectors
@param yBase The base y-values of the vectors
@param xFinal The transformed x-values of the vectors
@param yFinal The transformed y-values of the vectors
@param xPos The x-position for translation
@param yPos The y-position for translation
@param angle The angle of rotation, due to the coordinate system of computer screens this zero is a horizontal line to the right and increasing angle is clockwise rotation
@param scale The scale of the final object compared to the original
*/
void transform(const std::vector<float>& xBase, const std::vector<float>& yBase, std::vector<float>& xFinal, std::vector<float>& yFinal, const float xPos = 0.f, const float yPos = 0.f, const float angle = 0.f, const float scale = 1.f);

//! Transform - weird
/*!
From a sign error bug, I accidentally created a weird spinning animation. This is just that same code.
@param xBase The base x-values of the vectors
@param yBase The base y-values of the vectors
@param xFinal The transformed x-values of the vectors
@param yFinal The transformed y-values of the vectors
@param xPos The x-position for translation
@param yPos The y-position for translation
@param angle The angle of rotation, due to the coordinate system of computer screens this zero is a horizontal line to the right and increasing angle is clockwise rotation
@param scale The scale of the final object compared to the original
*/
void transformWeird(const std::vector<float>& xBase, const std::vector<float>& yBase, std::vector<float>& xFinal, std::vector<float>& yFinal, const float xPos = 0.f, const float yPos = 0.f, const float angle = 0.f, const float scale = 1.f);

//! Check if provided vectors Cross
/*!
Inefficient algorithm based on point-slope form. The idea is that I can turn the vectors into lines and see where the lines intersect. If the lines intersect within the domain of each vector, then the vectors do cross. To avoid dividing by small numbers, a lot of conditionals were added.
@param x1 The x-coordinates of the first vector
@param y1 The y-coordinates of the first vector
@param x2 The x-coordinates of the second vector
@param y2 The y-coordiantes of the second vector
@param tol The tolerance for being too close to zero to avoid dividing by small numbers.
@return True if the vectors cross
*/
bool vectorsCross(const std::vector<float>& x1, const std::vector<float>& y1, const std::vector<float>& x2, const std::vector<float>& y2, const float tol = 0.000001f);

//! Line Segment Crossing Algorithm
/*!
This algorithm is based on the relative orientation of the end points. First, form a triangle using the two end points segment AB and one of the end points of the segment CD. As I move A-B-C, the orientation falls under one of three cases, clockwise, counter-clockwise, or collinear. Collinear means they intersect, at exactly point C. By checking the triangle formed with point D (A-B-D) and comparing it's orientation to that of the first triangle, I can determine intersection. If the orientations are the same, there is no intersection. If the orientations are different, there is an intersection.

Next, to see find the orientation of each triangle, I compare the slope of AB to the slope of AC. If the slope from A to B is larger than the slope from A to C, the triangle is oriented clockwise. The opposite is true of the opposite condition. Note, collinear, would have the slopes be exactly equal. Because this is meant to be a collision algorithm in a dynamic system and this is floating point arithmetic, this case is ignored. To avoid dividing potentially dividing by a small number, I multiply both sides of the inequality by the bottom number. Finally, by applying a XOR gate, I get intersection.

To see how this works, I suggest drawing it out on a piece of paper. I pulled this algorithm from the internet and take no credit for it's creation. The implementation, however, is mine.
@param x1 The x-coordinates of the first vector
@param y1 The y-coordinates of the first vector
@param x2 The x-coordinates of the second vector
@param y2 The y-coordiantes of the second vector
@return True if the vectors cross
*/
bool linesCross(const std::vector<float>& x1, const std::vector<float>& y1, const std::vector<float>& x2, const std::vector<float>& y2);