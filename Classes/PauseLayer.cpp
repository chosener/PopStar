#include "PauseLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"


PauseLayer::PauseLayer()
{
    
}
PauseLayer::~PauseLayer()
{

}


bool PauseLayer::init()
{
	if(!Layer::init())
    {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    
#if 1
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan,this);
    
    listener->setSwallowTouches(true);

    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
#endif
    
	/*初始化背景*/
	Sprite* background = Sprite::create("bg/bg_pause.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	
	/*初始化菜单*/
    
    MenuItemImage* btnSkill0 = MenuItemImage::create("images/ico_home.png","images/ico_home.png",CC_CALLBACK_1(PauseLayer::startGame, this));
    MenuItemImage* btnSkill1 = MenuItemImage::create("images/ico_replay.png","images/ico_replay.png",CC_CALLBACK_1(PauseLayer::startGame,this));
    MenuItemImage* btnSkill2 = MenuItemImage::create("images/ico_continue.png","images/ico_continue.png",CC_CALLBACK_1(PauseLayer::startGame,this));
    
    btnSkill0->setTag(10);
    btnSkill1->setTag(11);
    btnSkill2->setTag(12);
    
    Menu* menuSkill= Menu::create(btnSkill0,btnSkill1,btnSkill2,NULL);
    menuSkill->alignItemsHorizontallyWithPadding(40.0f);
    menuSkill->setPosition(visibleSize.width/2,visibleSize.height/2 - 50.0f);
    this->addChild(menuSkill);
    
	return true;
}

void PauseLayer::startGame(Ref* node)
{
	//CCLOG("START!");
	//GAMEDATA::getInstance()->init();
	//Director::getInstance()->replaceScene(GameScene::create());
    
    Node* pender = (Node*)node;
    
    int tag = pender->getTag();
    
    CCLOG("btn tag = %d",tag);
    
    switch (tag)
    {
        case 10:
        {
            Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
            //主菜单
            Director::getInstance()->replaceScene(MenuScene::create());
            
            this->removeFromParent();
        }
            break;
        case 11:
        {
            Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
            //重新开始
            
            //从头来
            
            this->removeFromParent();
        }
            break;
        case 12:
        {
            Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
            //继续游戏
            this->removeFromParent();
        }
            break;
            
        default:
            break;
    }

}

bool PauseLayer::onTouchBegan(Touch* touch,Event* event)
{
    Point p = touch->getLocationInView();
    p = Director::getInstance()->convertToGL(p);
    CCLOG("x=%f y=%f",p.x,p.y);

    return true;
}
