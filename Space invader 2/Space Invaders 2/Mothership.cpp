#include "Mothership.h"
#include "Game.h"

void Mothership::haveLanded() 
{
	myGame->lose();
}
