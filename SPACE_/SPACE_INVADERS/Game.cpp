#include "Game.h"

Game::Game() {

	texturePath[CANNONTEXTURE] = "../Images/spaceship.png";
	texturePath[ALIENSMAPTEXTURE] = "../Images/aliens.png";
	texturePath[BUNKERTEXTURE] = "../Images/bunker.png";
	texturePath[STARTEXTURE] = "../Images/stars.png";

	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		if (i == ALIENSMAPTEXTURE)
			textures[i] = new Texture(renderer, texturePath[i], 3, 2);
		else textures[i] = new Texture(renderer, texturePath[i], 1, 1);
	}
	// We finally create the game objects
	cannon = new Cannon(objectProps.BALL_WIDTH, objectProps.BALL_HEIGHT, objectProps.BALL_INIT_POS,
		Vector2D(0, 0), this, renderer, textures[BALLTEXTURE]);
	aliensMap = new AliensMap(objectProps.PADDLE_WIDTH, objectProps.PADDLE_HEIGHT,
		objectProps.PADDLE_INIT_POS, Vector2D(0, 0), Vector2D(ZERO, ZERO), renderer, this, textures[PADDLETEXTURE]);
	bunker = new Bunker(objectProps.LATERAL_WALL_WIDTH, objectProps.LATERAL_WALL_HEIGHT,
		objectProps.LATERAL_LEFT_WALL_INIT_POS, renderer, textures[LATERALWALLTEXTURE]);
	star = new Star(objectProps.LATERAL_WALL_WIDTH, objectProps.LATERAL_WALL_HEIGHT,
		objectProps.LATERAL_RIGHT_WALL_INIT_POS, renderer, textures[LATERALWALLTEXTURE]);
}

void Game::init() {
	// We first initialize SDL
	// Inicializar SDL, crear ventana y renderizador
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw exception("Error loading SDL window or renderer");
}
