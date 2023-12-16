#include "SceneObject.h"
#include <fstream>

SceneObject::SceneObject(Game* game, std::ifstream& in, Texture* texture) : GameObject(game), _texture(texture)
{
	float posX, posY;

	in >> posX;
	in >> posY;
	in >> _life; //Lifes of the SceneObject are stored
	_pos = Point2D<float>(posX, posY); //Position of the SceneObject is stored
	_size.first = texture->getFrameWidth();
	_size.second = texture->getFrameHeight();
};

SceneObject::SceneObject(Game* game, std::ifstream& in, Texture* texture, int life) : GameObject(game), 
	_texture(texture), _life(life)
{
	float posX, posY;

	in >> posX;
	in >> posY;
	_pos = Point2D<float>(posX, posY); //Position of the SceneObject is stored
	_size.first = texture->getFrameWidth();
	_size.second = texture->getFrameHeight();
};

SceneObject::SceneObject(Game* game, std::ifstream& in, std::pair<uint, uint> size, int life) : GameObject(game),
	_size(size), _life(life)
{
	float posX, posY;

	in >> posX;
	in >> posY;
};