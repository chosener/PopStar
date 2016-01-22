#include "LogoLayer.h"

//创建场景
Scene* LogoLayer::createScene()
{

	auto scene = Scene::create();

	auto layer = LogoLayer::create();

	scene->addChild(layer);

	return scene;
}

//初始化
bool LogoLayer::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if 0
	auto label = LabelTTF::create("LogoLayer 测试!", FONT_ARIAL, 24);

	label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	label->setColor(Color3B(255, 0, 0));

	this->addChild(label, 1);
#endif
    
    Sprite* spLogo = Sprite::create("bg/loading_bg.png");
    spLogo->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(spLogo);
    
    this->scheduleOnce(schedule_selector(LogoLayer::jumpNextScene), 2.0f);

	return true;
}
void LogoLayer::jumpNextScene(float dt)
{
    //SceneManager::getInstance()->changeScene(SceneManager::en_GameMainMenu);
    Director::getInstance()->replaceScene(MenuScene::create());
}

