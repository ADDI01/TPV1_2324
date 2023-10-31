#include "BunkersMap.h"

void BunkersMap:: Load()
{
	_bunkers = new Bunker * [_nBunkers];
	for (int i = 0; i<_nBunkers;i++) 
	{
		_bunkers[i] = new Bunker(Point2D<float>(_cellW, _cellW), _nLifes, _bunkerTexture);
	}
}