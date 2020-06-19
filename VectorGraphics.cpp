#include "VectorGraphics.h"
#include "Game.h"
#include <math.h>
#include <iostream>

// CONSTRUCTOR
VectorGraphics::VectorGraphics(const std::vector<float>& new_xBase, const std::vector<float>& new_yBase) {
	if (new_xBase.size() != new_yBase.size()) {
		// TODO
		// Throw an appropriate exception

		// Error message
		std::cout << "Error: size mismatch." << std::endl;
	}
	else {
		// Allocate exactly enough space
		xBase.reserve(new_xBase.size());
		yBase.reserve(new_xBase.size());
		xCurr.reserve(new_xBase.size());
		yCurr.reserve(new_xBase.size());

		// Copy the elements
		for (size_t i = 0; i < new_xBase.size(); i++) {
			xBase.push_back(new_xBase[i]);
			yBase.push_back(new_yBase[i]);
			xCurr.push_back(new_xBase[i]);
			yCurr.push_back(new_yBase[i]);
		}
	}
}

// DESTRUCTOR
VectorGraphics::~VectorGraphics() {}

// DRAW
void VectorGraphics::draw(const float xPos, const float yPos, const float angle, const float scale) {
	// Transform the base
	transform(xBase, yBase, xCurr, yCurr, xPos, yPos, angle, scale);

	// Set the render draw color
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

	// Draw
	size_t n = xBase.size();
	for (size_t i = 0; i < n - 1; i++) {
		SDL_RenderDrawLineF(Game::renderer, xCurr[i], yCurr[i], xCurr[i + 1], yCurr[i + 1]);
	}
	SDL_RenderDrawLineF(Game::renderer, xCurr[n - 1], yCurr[n - 1], xCurr[0], yCurr[0]);
}

// DRAW DEBUG
void VectorGraphics::drawDebug(const float xPos, const float yPos, const float angle, const float scale) {
	// Transform the base
	transform(xBase, yBase, xCurr, yCurr, xPos, yPos, angle);

	// Draw the connecting lines in white
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	size_t n = xBase.size();
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
// EXTERNAL FUNCTIONS /////////////////////////////////////////////////////////
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