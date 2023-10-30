#include "Bunker.h"

void Bunker:: render() const
{
	SDL_Rect target;
	_texture->render(target);
}

bool Bunker::update() 
{
	bool retorno = true;
	if (_nLifes == 0)
	{
		this->~Bunker();
		retorno = false;
	}
		return retorno;
}

void Bunker::hit() 
{
	_nLifes--;
	//actualizar la imagen
}