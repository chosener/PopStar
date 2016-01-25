
#ifndef __MagicTouch__MoreGameLayer__
#define __MagicTouch__MoreGameLayer__

#include "cocos2d.h"
#include "MenuScene.h"

using namespace cocos2d;

//logo层

//Logo界面
class MoreGameLayer:public Layer
{
public:
	//创建场景
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	CREATE_FUNC(MoreGameLayer);
private:

    void returnGame();
};
#endif
