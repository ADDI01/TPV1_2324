#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
//incluir Game Object

class GameState
{
	/*es la clase ra�z de la jerarqu�a de estados del juego y tiene al menos tres atributos:
la colecci�n de objetos del juego (GameList<GameObject, true>, que se explica en la p�gina 3), los
manejadores de eventos (list<EventHandler*>, v�ase m�s adelante) y el puntero al juego. Implementa
los m�todos update, render y handleEvent, y tambi�n addEventListener y addObject para a�adir oyentes
y objetos al estado.
*/
	//GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	
};