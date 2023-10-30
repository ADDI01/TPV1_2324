#include "Bunker.h"

void Bunker:: render() const
{
	SDL_Rect target;
	_texture->render(target);
}

bool Bunker::update() 
{
	bool retorno = true;
	if (_nVidas == 0)
	{
		this->~Bunker();
		retorno = false;
	}
		return retorno;
}

void Bunker::hit() 
{
	_nVidas--;
	//actualizar la imagen
}