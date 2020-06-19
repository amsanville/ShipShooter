#include "Game.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// GAME ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Initialize the Game static variables
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

// CONSTRUCTOR
Game::Game() : window(nullptr), currState(nullptr) {}

// DESTRUCTOR
Game::~Game() {
	this->clean();
}

// INIT
bool Game::init(const char* title, const int xpos, const int ypos, const int width, const int height, const bool fullscreen) {
	// Convert the fullscreen input flag into an SDL Flag
	int flags = 0; // Flag for SDL_CreateWindow
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	bool success = true; // Output variable

	// Attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!..." << std::endl;

		// Attempt to create a window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created!..." << std::endl;

			// Attempt to create the renderer
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				std::cout << "Renderer Created!..." << std::endl;

				// Set render draw color to black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

				// Setup other assets for the game
				currState = new TestState0();
			}
			else {
				// Output message and change flag
				std::cout << "Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
		}
		else {
			// Output message and change flag
			std::cout << "Failed to create window. SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
	}
	else {
		// Output message and change flag
		std::cout << "Failed to initialize subsystems. SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	return success;
}

// CLEAN
void Game::clean() {
	// Clean up state
	delete currState;
	currState = nullptr;

	// Clean up SDL assets
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	// Clean up SDL Systems
	SDL_Quit();
}

// GAME LOOP
void Game::gameLoop() {
	currState->runGame();
}

///////////////////////////////////////////////////////////////////////////////
// TEST STATE 0 ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR
TestState0::TestState0() {
	player = new Ship();
	player->setX(400);
	player->setY(320);
}

// DESTRUCTOR
TestState0::~TestState0() {
	delete player;
}

// HANDLE EVENTS
bool TestState0::handleEvents() {
	// Return variable
	bool quit = false;
	float vel = 0.05f;

	// Handle Events
	while (SDL_PollEvent(&Game::event)) {
		// Key pushed down - set the velocity appropriately
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
				player->setYVel(-vel);
				break;
			case SDLK_DOWN:
				player->setYVel(vel);
				break;
			case SDLK_LEFT:
				player->setXVel(-vel);
				break;
			case SDLK_RIGHT:
				player->setXVel(vel);
				break;
			default:
				break;
			}
		}

		// Key released - reset the velocity to 0
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
				player->setYVel(player->getYVel() + vel);
				break;
			case SDLK_DOWN:
				player->setYVel(player->getYVel() - vel);
				break;
			case SDLK_LEFT:
				player->setXVel(player->getXVel() + vel);
				break;
			case SDLK_RIGHT:
				player->setXVel(player->getXVel() - vel);
				break;
			default:
				break;
			}
		}

		// Check if quit
		if (Game::event.type == SDL_QUIT) {
			quit = true;
		}
	}
	return quit;
}

// UPDATE
void TestState0::update(const int frameDelay) {
	player->setX(player->getX() + player->getXVel());
	player->setY(player->getY() + player->getYVel());
}

// RENDER
void TestState0::render() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::renderer);
	player->draw();
	SDL_RenderPresent(Game::renderer);
}

// RUN GAME
int TestState0::runGame() {
	// Setup for game loop
	bool quit = false;
	float yVel = 0.0f;
	float xVel = 0.0f;

	// Setup the constant frame rate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	// Get the start of the frame
	frameStart = SDL_GetTicks();
	while (!quit) {
		// Handle events
		quit = this->handleEvents();
		// Update
		this->update(frameDelay);
		// Render
		this->render();

		// Calculate the amount of time for each frame
		frameTime = SDL_GetTicks() - frameStart;

		// If the frame needs to be delayed
		if (frameDelay > frameTime) {
			// Delay by the amount of time left
			SDL_Delay(frameDelay - frameTime);
		}
	}
	return -1;
}