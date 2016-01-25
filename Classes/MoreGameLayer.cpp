#include "MoreGameLayer.h"

//创建场景
Scene* MoreGameLayer::createScene()
{

	auto scene = Scene::create();

	auto layer = MoreGameLayer::create();

	scene->addChild(layer);

	return scene;
}

//初始化
bool MoreGameLayer::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if 1
	auto label = LabelTTF::create("更多游戏下载:\n\nwww.isainttech.com", "", 32);

	label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	label->setColor(Color3B(5, 130, 130));

	this->addChild(label, 1);
#endif
    
    Sprite* spLogo = Sprite::create("bg/bg_mainmenu.png");
    spLogo->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(spLogo);
    
    //返回游戏
    MenuItemImage* imageMenuReturn= MenuItemImage::create("images/btn_return.png","images/btn_return_s.png",CC_CALLBACK_0(MoreGameLayer::returnGame,this));
    Menu* menuReturn = Menu::create(imageMenuReturn,NULL);
    menuReturn->setPosition(80.0f,visibleSize.height - 80.0f);
    this->addChild(menuReturn);
    
    return true;
}


void MoreGameLayer::returnGame()
{
    Director::getInstance()->replaceScene(MenuScene::create());
}
