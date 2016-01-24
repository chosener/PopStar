#include "GameOver.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "GameLayer.h"
#include "TopMenu.h"

GameOver::GameOver()
{
    
}
GameOver::~GameOver()
{

}


bool GameOver::init()
{
	if(!Layer::init())
    {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
    
#if 1
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan,this);
    
    listener->setSwallowTouches(true);

    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
#endif
    
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg/bg_pause.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
    
    //��ͣ��
    
    Sprite* spTxtPause = Sprite::create("images/GameOver.png");
    spTxtPause->setPosition(visibleSize.width/2 + 200.0f,visibleSize.height/2 + 130.0f);
    this->addChild(spTxtPause);
    
	
	/*��ʼ���˵�*/
    
    MenuItemImage* btnSkill0 = MenuItemImage::create("images/ico_home.png","images/ico_home.png",CC_CALLBACK_1(GameOver::startGame, this));
    MenuItemImage* btnSkill1 = MenuItemImage::create("images/ico_replay.png","images/ico_replay.png",CC_CALLBACK_1(GameOver::startGame,this));
    //MenuItemImage* btnSkill2 = MenuItemImage::create("images/ico_continue.png","images/ico_continue.png",CC_CALLBACK_1(GameOver::startGame,this));
    
    btnSkill0->setTag(10);
    btnSkill1->setTag(11);
    //btnSkill2->setTag(12);
    
    Menu* menuSkill= Menu::create(btnSkill0,btnSkill1,NULL);
    menuSkill->alignItemsHorizontallyWithPadding(40.0f);
    menuSkill->setPosition(visibleSize.width/2,visibleSize.height/2 - 50.0f);
    this->addChild(menuSkill);
    
    showAD();
    
	return true;
}

void GameOver::startGame(Ref* node)
{
	//CCLOG("START!");
	//GAMEDATA::getInstance()->init();
	//Director::getInstance()->replaceScene(GameScene::create());
    
    Node* pender = (Node*)node;
    
    int tag = pender->getTag();
    
    CCLOG("btn tag = %d",tag);
    
    Scene* scene = (Scene*)this->getParent();
    
    GameLayer* gameLayer = (GameLayer*)scene->getChildByTag(999);
    
    TopMenu* topMenu = (TopMenu*)gameLayer->getChildByTag(9999);
    
    Menu* menuPause = (Menu*)topMenu->getChildByTag(100);
    
    menuPause->setEnabled(true);
    
    switch (tag)
    {
        case 10:
        {
            this->removeSelfListener();

            //���˵�
            Director::getInstance()->replaceScene(MenuScene::create());
            
            this->removeFromParent();
        }
            break;
        case 11:
        {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            //���¿�ʼ
            EventCustom eventReset = EventCustom("Game_Reset");
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventReset);
            //��ͷ��
            
            this->removeFromParent();
        }
            break;
        case 12:
        {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            //������Ϸ
            this->removeFromParent();
        }
            break;
            
        default:
            break;
    }

}

bool GameOver::onTouchBegan(Touch* touch,Event* event)
{
    Point p = touch->getLocationInView();
    p = Director::getInstance()->convertToGL(p);
    CCLOG("x=%f y=%f",p.x,p.y);

    return true;
}
void GameOver::removeSelfListener()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
}
