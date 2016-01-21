#include "PauseLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
bool PauseLayer::init()
{
	if(!Layer::init())
    {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan,this);
    
    listener->setSwallowTouches(false);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
	/*初始化背景*/
	Sprite* background = Sprite::create("bg/bg_pause.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	
	/*初始化菜单*/
	MenuItemImage* startBtn = MenuItemImage::create(
		"menu_start.png","menu_star.png",CC_CALLBACK_0(PauseLayer::startGame,this)
		);
	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);
	return true;
}

void PauseLayer::startGame()
{
	//CCLOG("START!");
	//GAMEDATA::getInstance()->init();
	//Director::getInstance()->replaceScene(GameScene::create());

}

bool PauseLayer::onTouchBegan(Touch* touch,Event* event)
{
    Point p = touch->getLocationInView();
    p = Director::getInstance()->convertToGL(p);
    CCLOG("x=%f y=%f",p.x,p.y);

    return true;
}
