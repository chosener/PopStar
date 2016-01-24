#ifndef _GameOver_H_
#define _GameOver_H_
#include "cocos2d.h"
#include "MenuScene.h"
#include "JniSms.h"
using namespace cocos2d;


class GameOver : public Layer
{
public:
    GameOver();
    ~GameOver();
    
	virtual bool init();
	CREATE_FUNC(GameOver);
    virtual bool onTouchBegan(Touch* touch,Event* event);
	void startGame(Ref* node);
    
private:
    EventListenerTouchOneByOne* listener;
    
    void removeSelfListener();
};
#endif