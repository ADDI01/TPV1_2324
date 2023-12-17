#include "PlayState.h"

void PlayState::render() const
{
	for (SceneObject* o : _sceneObjectList)
		o->render();
}
