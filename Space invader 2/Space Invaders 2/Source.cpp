#include "checkML.h"
#include "SDL.h"
#include "Game.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

void initGame()
{
	Game game;

	try {
		game.run();
	}
	/*catch (SDLError& sdlErr) { cout << sldErr.what(); }
	catch (FileFormatError& ffErr) { cout << ffErr.what(); }
	catch (FileNotFoundError& fnfErr) { cout << fnfErr.what(); }
	catch (logic_error& lErr) { cout << lErr.what(); }*/
	catch (exception& e) { cout << e.what(); }
}

int main(int argc, char* argv[])
{
	initGame();
	return 0;
}