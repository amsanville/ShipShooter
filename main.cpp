#include "Game.h"
#include "VectorGraphics.h"
#include <vector>
#define PI 3.14159265
/** @mainpage
 *
 */

/* TODOs
Game - Create state management system
Game - Better UI
State - update documentation
TestState0 - Implement UI for controlling the ship/game loop 
TestState0 - Update documentation
GameObject - Use Constructors to manage the graphics systems
GameObject - Do I even need polymorphism?
SpriteGraphics - The whole things (see lazyfoo on how to do loading, clipping, blitting, etc.)
VectorGraphics - Scaling 
VectorGraphics - Throw Exception Properly
*/

int main(int argc, char* argv[]) {
    /*/
    // Setup the constant frame rate
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    */

    // Create the game
    Game asteroids;
    asteroids.init("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    asteroids.gameLoop();
    /*
    // Make a square
    std::vector<float> x = { 10., -10., -10., 10. };
    std::vector<float> y = { 10., 10., -10., -10. };
    VectorGraphics test = VectorGraphics(x, y);

    int n = 0;
    float currAngle = 0;
    while (n < 300) {
        // Get the start of the frame
        frameStart = SDL_GetTicks();

        // Draw the player
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);
        test.drawDebug(400, 320, currAngle);
        currAngle += PI / 60.0;
        SDL_RenderPresent(Game::renderer);

        // Calculate the amount of time for each frame
        frameTime = SDL_GetTicks() - frameStart;

        // If the frame needs to be delayed
        if (frameDelay > frameTime) {
            // Delay by the amount of time left
            SDL_Delay(frameDelay - frameTime);
        }

        n++;
    }
    */

    /*
    // Create a ship
    Ship player;
    player.setX(400);
    player.setY(320);
    player.setAngle(0.0);

    while (asteroids.running()) {
        // Get the start of the frame
        frameStart = SDL_GetTicks();

        // Draw the player
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);
        player.draw();
        SDL_RenderPresent(Game::renderer);
        player.setAngle(player.getAngle() + PI / 60.0);

        // Calculate the amount of time for each frame
        frameTime = SDL_GetTicks() - frameStart;

        // If the frame needs to be delayed
        if (frameDelay > frameTime) {
            // Delay by the amount of time left
            SDL_Delay(frameDelay - frameTime);
        }
    }
    */

    return 0;
}