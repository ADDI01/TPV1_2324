#include "Mothership.h"
#include "Game.h"

void Mothership::haveLanded() 
{
	_game->lose();
}
