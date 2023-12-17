#include "PlayState.h"
#include <random>

void PlayState::render() const
{
	star->render();
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
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	}
	else {
		for (EventHandler* it : eventHandlerList) {
			it->manageEvent(event);
		}
	}
}

int PlayState::getRandomRange(int min, int max)
{
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return std::uniform_int_distribution<int>(min, max)(randomGenerator); 
}
