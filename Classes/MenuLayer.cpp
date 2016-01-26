#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "AboutLayer.h"
#include "MoreGameLayer.h"
#include "JniSms.h"

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
	MenuItemImage* startBtn = MenuItemImage::create("images/menu_start.png","images/menu_start_s.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2 -100.0f);
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
    
    //关于游戏
    MenuItemImage* imageMenuAbout= MenuItemImage::create("images/about_n.png","images/about_s.png",CC_CALLBACK_0(MenuLayer::aboutGame,this));
    imageMenuAbout->setScale(0.7f);
    Menu* menuAbout = Menu::create(imageMenuAbout,NULL);
    menuAbout->setPosition(visibleSize.width/2 - 200.0f,visibleSize.height/2 - 450.0f);
    this->addChild(menuAbout);
    
    //更多游戏
    MenuItemImage* imageMenuMoreGame = MenuItemImage::create("images/moregame_n.png","images/moregame_s.png",CC_CALLBACK_0(MenuLayer::moreGame,this));
    imageMenuMoreGame->setScale(0.7f);
    Menu* menuMoreGame = Menu::create(imageMenuMoreGame,NULL);
    menuMoreGame->setPosition(visibleSize.width/2,visibleSize.height/2 - 450.0f);
    this->addChild(menuMoreGame);
    
    //分享游戏
    MenuItemImage* imageMenuShare = MenuItemImage::create("images/share_n.png","images/share_s.png",CC_CALLBACK_0(MenuLayer::shareGame,this));
    imageMenuShare->setScale(0.7f);
    Menu* menuShare = Menu::create(imageMenuShare,NULL);
    menuShare->setPosition(visibleSize.width/2 + 200.0f,visibleSize.height/2 - 450.0f);
    this->addChild(menuShare);
    
#if 0
    ScaleTo* scaleTo00 = ScaleTo::create(1.0f, 1.05f);
    ScaleTo* scaleTo11 = ScaleTo::create(1.0f, 1.0f);
    Sequence* seqq = Sequence::create(scaleTo00,scaleTo11, NULL);
    RepeatForever* repeatee = RepeatForever::create(seqq);
    
    imageMenuAbout->runAction(repeatee);
    imageMenuMoreGame->runAction(repeatee->clone());
    imageMenuShare->runAction(repeatee->clone());
#endif
    
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
void MenuLayer::aboutGame()
{

    Director::getInstance()->replaceScene(AboutLayer::createScene());
    
}
void MenuLayer::moreGame()
{

    Director::getInstance()->replaceScene(MoreGameLayer::createScene());
    
}
void MenuLayer::shareGame()
{
    shareSelfGame();
}
