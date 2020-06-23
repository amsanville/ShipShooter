#include "VectorGraphics.h"
#include "Game.h"
#include <math.h>
#include <iostream>
#include <algorithm>

// CONSTRUCTOR
VectorGraphics::VectorGraphics(const std::vector<float>& xBase, const std::vector<float>& yBase) {
	if (xBase.size() != yBase.size()) {
		// TODO
		// Throw an appropriate exception

		// Error message
		std::cout << "Error: size mismatch." << std::endl;
	}
	else {
		// Allocate exactly enough space
		xCurr.reserve(xBase.size());
		yCurr.reserve(xBase.size());

		// Copy the elements
		for (size_t i = 0; i < xBase.size(); i++) {
			xCurr.push_back(xBase[i]);
			yCurr.push_back(yBase[i]);
		}
	}
}

// DESTRUCTOR
VectorGraphics::~VectorGraphics() {}

// UPDATE
void VectorGraphics::update(const std::vector<float>& xBase, const std::vector<float>& yBase, const float xPos, const float yPos, const float angle) {
	transform(xBase, yBase, xCurr, yCurr, xPos, yPos, angle);
}

// COLLIDE
bool VectorGraphics::collide(const VectorGraphics& otherGraphics) {
	// Initialize
	bool collision = false; //!< Whether or not a collision has happened, return variable
	std::vector<float> x1(2, 0.f), y1(2, 0.f), x2(2, 0.f), y2(2, 0.f); //!< Pairs of values for the line-crossing algorithm
	int n1 = xCurr.size() - 1; //!< Index of the last element of this vector representation
	int n2 = otherGraphics.xCurr.size() - 1; //!< Index of last element of otherGraphics vector representation

	// Loop until either a collision is found or all pairs tested
	for (int i = 0; i < n1 && !collision; i++) {
		for (int j = 0; j < n2 && !collision; j++) {
			// See if there is a collision
			collision = linesCross({ xCurr[i], xCurr[i + 1] }, { yCurr[i], yCurr[i + 1] }, { otherGraphics.xCurr[i], otherGraphics.xCurr[i + 1] }, { otherGraphics.yCurr[i], otherGraphics.yCurr[i + 1] });
		}
		collision = linesCross({ xCurr[i], xCurr[i + 1] }, { yCurr[i], yCurr[i + 1] }, { otherGraphics.xCurr[n2], otherGraphics.xCurr[0] }, { otherGraphics.yCurr[n2], otherGraphics.yCurr[0] });
	}

	// If no collision, yet
	if (!collision) {
		// Last vector for this object
		for (int j = 0; j < n2 && !collision; j++) {
			// See if there is a collision
			collision = linesCross({ xCurr[n1], xCurr[0] }, { yCurr[n1], yCurr[0] }, { otherGraphics.xCurr[i], otherGraphics.xCurr[i + 1] }, { otherGraphics.yCurr[i], otherGraphics.yCurr[i + 1] });
		}
		collision = linesCross({ xCurr[n1], xCurr[0] }, { yCurr[n1], yCurr[0] }, { otherGraphics.xCurr[n2], otherGraphics.xCurr[0] }, { otherGraphics.yCurr[n2], otherGraphics.yCurr[0] });
	}

	return collision;
}

// DRAW
void VectorGraphics::draw() {
	// Set the render draw color
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

	// Draw
	size_t n = xCurr.size();
	for (size_t i = 0; i < n - 1; i++) {
		SDL_RenderDrawLineF(Game::renderer, xCurr[i], yCurr[i], xCurr[i + 1], yCurr[i + 1]);
	}
	SDL_RenderDrawLineF(Game::renderer, xCurr[n - 1], yCurr[n - 1], xCurr[0], yCurr[0]);
}

// DRAW DEBUG
void VectorGraphics::drawDebug(const bool collide) {
	// Set draw color
	if (collide) {
		// White if no collision
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
	}
	else {
		// Yellow if collision, as dictated by the flag
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}

	size_t n = xCurr.size();
	for (size_t i = 0; i < n - 1; i++) {
		SDL_RenderDrawLineF(Game::renderer, xCurr[i], yCurr[i], xCurr[i + 1], yCurr[i + 1]);
	}
	SDL_RenderDrawLineF(Game::renderer, xCurr[n - 1], yCurr[n - 1], xCurr[0], yCurr[0]);

	// Draw the vertices in red
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	for(size_t i = 0; i < n; i++){
		SDL_RenderDrawPointF(Game::renderer, xCurr[i], yCurr[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////
// EXTERNAL ALGORITHMS ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// TRANSFORM
void transform(const std::vector<float>& xBase, const std::vector<float>& yBase, std::vector<float>& xFinal, std::vector<float>& yFinal, const float xPos, const float yPos, const float angle, const float scale) {
	for (size_t i = 0; i < xBase.size(); i++) {
		xFinal[i] = scale * (xBase[i] * cos(angle) - yBase[i] * sin(angle)) + xPos;
		yFinal[i] = scale * (xBase[i] * sin(angle) + yBase[i] * cos(angle)) + yPos;
	}
}

// TRANSFORM WEIRD
void transformWeird(const std::vector<float>& xBase, const std::vector<float>& yBase, std::vector<float>& xFinal, std::vector<float>& yFinal, const float xPos, const float yPos, const float angle, const float scale) {
	for (size_t i = 0; i < xBase.size(); i++) {
		xFinal[i] = scale * (xBase[i] * cos(angle) - yBase[i] * sin(angle)) + xPos;
		yFinal[i] = scale * (xBase[i] * sin(angle) - yBase[i] * cos(angle)) + yPos;
	}
}

// VECTORS CROSS
bool vectorsCross(const std::vector<float>& x1, const std::vector<float>& y1, const std::vector<float>& x2, const std::vector<float>& y2, const float tol) {
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
	if (minX1 < maxX2 && minX2 < maxX1 && minY1 < maxY2 && minY2 < maxY1) {

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