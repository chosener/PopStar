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
    
    //音乐
    auto musicOnMenuItem  =MenuItemImage::create("images/sound-on1.png","images/sound-on1.png");
    auto musicOffMenuItem  =MenuItemImage::create("images/sound-off1.png","images/sound-off1.png");
    
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::menuMusicToggleCallback,this),musicOnMenuItem,musicOffMenuItem,NULL );

    auto menuMusic = Menu::create(musicToggleMenuItem, nullptr );
    menuMusic->setPosition(visibleSize.width - 80.0f,visibleSize.height - 80.0f);
    this->addChild(menuMusic);
    
    musicToggleMenuItem->setSelectedIndex((Audio::getInstance()->getbIsOpenMusic() ? 0 : 1));
    
    Audio::getInstance()->playBGM();
    
    
	return true;
}

void MenuLayer::menuMusicToggleCallback(Ref* pSender)
{
    MenuItemToggle* menuMusic = (MenuItemToggle*)pSender;
    
    CCLOG("selected index:%d",menuMusic->getSelectedIndex());
    
    int select = menuMusic->getSelectedIndex();
    
    switch (select) {
        case 0:
        {
            Audio::getInstance()->setbIsOpenMusic(true);
            Audio::getInstance()->playBGM();
        }
            break;
        case 1:
        {
            Audio::getInstance()->setbIsOpenMusic(false);
            Audio::getInstance()->pauseBGM();
        }
            break;
            
        default:
            break;
    }
}

void MenuLayer::startGame()
{
	CCLOG("START!");
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());

}
