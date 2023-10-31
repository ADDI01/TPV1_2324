#include "AliensMap.h"


void AliensMap::render() const {
	for (Alien* a : _aliens) {
		a->render();
	}
}