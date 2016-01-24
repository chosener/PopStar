#ifndef _PauseLayer_H_
#define _PauseLayer_H_
#include "cocos2d.h"
#include "MenuScene.h"
#include "JniSms.h"
using namespace cocos2d;


class PauseLayer : public Layer
{
public:
    PauseLayer();
    ~PauseLayer();
    
	virtual bool init();
	CREATE_FUNC(PauseLayer);
    virtual bool onTouchBegan(Touch* touch,Event* event);
	void startGame(Ref* node);
    
private:
    EventListenerTouchOneByOne* listener;
    
    void removeSelfListener();
};
#endif