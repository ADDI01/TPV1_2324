//#include "checkML.h"

#include "SDL.h"
#include "Game.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

void initGame()
{
	Game game;

	try {
		game.run();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

int main(int argc, char* argv[])
{
	initGame();
	return 0;
}