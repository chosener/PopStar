
#ifndef __MagicTouch__AboutLayer__
#define __MagicTouch__AboutLayer__

#include "cocos2d.h"
#include "MenuScene.h"

using namespace cocos2d;

//logo层

//Logo界面
class AboutLayer:public Layer
{
public:
	//创建场景
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	CREATE_FUNC(AboutLayer);
private:

    void returnGame();
};
#endif
