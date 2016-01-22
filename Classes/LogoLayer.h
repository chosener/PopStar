
#ifndef __MagicTouch__LogoLayer__
#define __MagicTouch__LogoLayer__

#include "cocos2d.h"
#include "MenuScene.h"

using namespace cocos2d;

//logo层

//Logo界面
class LogoLayer:public Layer
{
public:
	//创建场景
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();

	CREATE_FUNC(LogoLayer);
private:
    void jumpNextScene(float dt);
};
#endif
