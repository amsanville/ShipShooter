#include "Game.h"
#include "GameObject.h"
#include "VectorGraphics.h"
#include <vector>
#define PI 3.14159265
/** @mainpage
 *
 */

/* TODOs
Game - Create state management system
TestState0 - Better UI
GameObject - Do I even need polymorphism?
SpriteGraphics - The whole thing (see lazyfoo on how to do loading, clipping, blitting, etc.)
VectorGraphics - Scaling 
VectorGraphics - Throw Exception Properly
main - test collisions algorithm
main - settings file
makefile - actually write it
*/

//! Test Collision Algorithms
/*!
Test the code for the two different collision algorithms written.
*/
void testCollisions() {
    std::vector<float> xBase1;
    std::vector<float> yBase1;
    VectorGraphics test1 = VectorGraphics(xBase1, yBase1);

}

int main(int argc, char* argv[]) {
    // Create the game
    Game testGame;
    testGame.init("Test Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    testGame.gameLoop();

    return 0;
}