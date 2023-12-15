#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
//incluir Game Object

class GameState
{
	/*es la clase raíz de la jerarquía de estados del juego y tiene al menos tres atributos:
la colección de objetos del juego (GameList<GameObject, true>, que se explica en la página 3), los
manejadores de eventos (list<EventHandler*>, véase más adelante) y el puntero al juego. Implementa
los métodos update, render y handleEvent, y también addEventListener y addObject para añadir oyentes
y objetos al estado.
*/
	//GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	
};