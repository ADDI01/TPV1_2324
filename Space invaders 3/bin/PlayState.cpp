#include "PlayState.h"
#include "PauseState.h"
#include <random>

PlayState::~PlayState()
{
	gameList.clear();
	delete infoBar;
	delete _mother;
	delete star;
}

void PlayState::render() const
{
	star->render();
	infoBar->render();
	for (auto it = gameList.begin(); it != gameList.end(); ++it)
	{
		(*it).render();
	}
}

void PlayState::update()
{
	_mother->update();
	for (auto it = gameList.begin(); it != gameList.end(); ++it) {
		(*it).update();
	}
}


void PlayState::handleEvent(const SDL_Event& event) {
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		PauseState* pause = new PauseState(myGame, myGame->getTexture()[11], myGame->getTexture()[13], myGame->getTexture()[9], myGame->getTexture()[16]);
		myGame->pushState(pause);
		pause->setPlayState(this);
	}

	for (EventHandler* it : eventHandlerList) {
		it->manageEvent(event);
	}
}

int PlayState::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return std::uniform_int_distribution<int>(min, max)(randomGenerator); 
}
