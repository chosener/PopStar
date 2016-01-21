#ifndef _PauseLayer_H_
#define _PauseLayer_H_
#include "cocos2d.h"
using namespace cocos2d;
class PauseLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);
	void startGame();
};
#endif