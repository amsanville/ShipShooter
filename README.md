# Ship Shooter
This project is an SDL-based game modeled after some of my favorite arcade games: spaceship shooters (i.e. Gradius, Asteroids, Raiden, etc., alright some of these are jets, the point still stands).. This project will be an amalgamation of all the different game making tutorials I've done. The backend structure is based entirely on polymorphism. The game itself uses a state machine, which sets the program into a specific state and then based on user behavior changes state. These states all inherit from a parent state class with each state having a separate implementation for UI and what not.

Since this is my first major project, I'm not too worried about trimming down code size or a whole lot of code reuse type stuff. I am going to attempt to minimize the number of states though. The game objects are also based on polymorphism. Each individual object inherits from a parent game object class which has some basic pure virtual features. The polymorphism may ultimately be unnecessary for the game objects. Finally, read the documentation (generated using Doxygen) for more details on how exactly everything works.

## Compiling
WIP - no make file yet.

This project uses the following external libraries:
* SDL2
Planned, but not needed yet:
* SDL2 Image
* SDL2 TTF
Linux Instructions:
1. Install GNU compiler
2. Install SDL libraries
3. Download all the `.h` and `.cpp` and the makefile.
4. Use command `make all` to build the project.
5. Run the game with `./ShipShooter`
