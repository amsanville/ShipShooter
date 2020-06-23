#pragma once
#include "GameObject.h"
#include<SDL.h>
//! Game.h
/*!
Contains the Game class, which operates as the super class holding all the different game components. Also contains the State class and it's child classes, which each have their own internal gameplay loops allowing for the UI to behave differently in different conditions.
*/

/*!
Enumeration of the various game states. Each unique constant provides different behavior for the game.
*/
const enum {TESTSTATE0, MAINMENU, INGAME};

// Forward declare State class
class State;

//! Game Class
/*!
Class that hold the SDL components and manages them as well as controls the game state.
*/
class Game {
private:
	SDL_Window* window; //!< Window space where we render the game
	State* currState; //!< State the game is in
public:
	static SDL_Renderer* renderer; //!< Renderer for all objects in the game
	static SDL_Event event; //!< Listener for all input events in the game

	//! Constructor
	/*!
	Only initializes fields with equivalent of null. Left empty on purpose to allow initialization with the init method at the appropriate time.
	*/
	Game();

	//! Destructor
	/*!
	Uses the clean method to close down SDL Subsystems and destroy SDL features created by the game.
	*/
	~Game();

	//! Initializer
	/*!
	Initializes the SDL Subsystems and initializes game features.
	@param title The title on the window
	@param xpos The starting x-position of the window
	@param ypos The starting x-position of the window
	@param width The width of the window
	@param height The height of the window
	@param fullscreen True for fullscreen mode
	@return True, if successfully starts SDL and other subsystems.
	*/
	bool init(const char* title, const int xpos, const int ypos, const int width, const int height, const bool fullscreen);

	//! Clean
	/*!
	Unloads all assets and uses SDL destructor methods to clean up SDL features.
	*/
	void clean();

	//! Game Loop
	/*!
	Runs the game loop by managing the different states.
	*/
	void gameLoop();
};

//! Parent State Class
/*!
Pure virtual State class. Each state manages a discrete chunk of UI for the game. The idea is to comparmentalize the different aspects of UI behavior into states and then leave that UI state for another based on the program resolving what's going on.
*/
class State {
protected:
	//! Handle Events
	/*!
	Handle user input
	@return True for quiting/changing state.
	*/
	virtual bool handleEvents() = 0;

	//! Update
	/*!
	Simulate the physics through one tick using whatever time is left in the gameplay loop.
	@param frameDelay The delay between rendering frames
	*/
	virtual void update(const int frameDelay) = 0;

	//! Render
	/*!
	Draws to the screen according to the current state.
	*/
	virtual void render() = 0;
public:
	//! Run Game
	/*!
	Runs the game according to each state.
	*/
	virtual int runGame() = 0;
};

//! TestState0
/*!
Each test state represents a distinct chunk of test code for testing different concepts in UI, rendering, or other gameplay elements. The collection of test states acts as an archive for cross-comparison of different ideas for performance and gameplay analysis. The final product is going to be an amalgamation of these different test states.

TestState0: create a player ship that the player can move around the screen. Meant to test basic methods of moving the ship around the screen as well as give the player a basic game play experience.
*/
class TestState0 : public State {
private:
	Ship* player; //!< Player's ship.
protected:
	//! Handle Events
	/*!
	Handles moving the ship around as well as quiting.
	@return True for the game should quit.
	*/
	bool handleEvents();

	//!
	/*!
	Updates the position of the ship.
	@param frameDelay The delay between rendering frames
	*/
	void update(const int frameDelay);

	//! Render
	/*!
	Draw the ship on the screen.
	*/
	void render();
public:
	//! Constructor
	/*!
	Creates the player's ship.
	*/
	TestState0();

	//! Destructor
	/*!
	Cleans up the player's ship.
	*/
	~TestState0();

	//! Run Game
	/*!
	Runs the state.
	*/
	int runGame();
};

class TestState1 : public State {
protected:
	bool handleEvents();
	void update(const int frameDelay);
	void render();
public:
	TestState1();
	~TestState1();
	int runGame();
};

/*
class MainMenu : public State {
public:
	int runGame();
	void handleEvents();
	void update();
	void render();
};

class InGame : public State {
public:
	int runGame();
	void handleEvents();
	void update();
	void render();
};
*/