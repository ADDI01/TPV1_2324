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
		game.init();
		game.run();
	}
	catch (SDLError& sdlErr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL", sdlErr.what(), game.getWindow()); 
	}
	catch (FileFormatError& ffErr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File Format", ffErr.what(), game.getWindow());
	}
	catch (FileNotFoundError& fnfErr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File Not Found",  fnfErr.what(), game.getWindow());
	}
	catch (logic_error& lErr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Logic Error",  lErr.what(), game.getWindow());
	}
	catch (exception& e)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception",  e.what(), game.getWindow());
	}
}

int main(int argc, char* argv[])
{
	initGame();
	return 0;
}