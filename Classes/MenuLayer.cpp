#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
bool MenuLayer::init()
{
	if(!Layer::init())
    {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*初始化背景*/
	Sprite* background = Sprite::create("bg/bg_mainmenu.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
    
    ///标题
    Sprite* spTitle = Sprite::create("images/title.png");
    spTitle->setPosition(visibleSize.width/2,visibleSize.height/2 + 300.0f);
    this->addChild(spTitle);
    
    Sprite* spFlower0 = Sprite::create("images/loginSceneFollow.png");
    spFlower0->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    spFlower0->setPosition(visibleSize.width/2,0.0f);
    spFlower0->setScaleX(1.5f);
    spFlower0->setScaleY(1.5f);
    this->addChild(spFlower0);
	
	/*初始化菜单*/
	MenuItemImage* startBtn = MenuItemImage::create(
		"images/menu_start.png","images/menu_start_s.png",CC_CALLBACK_0(MenuLayer::startGame,this)
		);
	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2 -150.0f);
	this->addChild(menu);
    
    ScaleTo* scaleTo0 = ScaleTo::create(1.0f, 1.2f);
    ScaleTo* scaleTo1 = ScaleTo::create(1.0f, 1.0f);
    Sequence* seq = Sequence::create(scaleTo0,scaleTo1, NULL);
    
    RepeatForever* repeate = RepeatForever::create(seq);
    
    startBtn->runAction(repeate);
    
	return true;
}

void MenuLayer::startGame()
{
	CCLOG("START!");
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());

}
