#include "TopMenu.h"

#include "GameData.h"
#include "GameLayer.h"

bool TopMenu::init()
{
	if(!Node::init())
    {
		return false;
	}
    
    this->initView();

	return true;
}
void TopMenu::initView()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    ///暂停按钮
    MenuItemImage* btnPause = MenuItemImage::create("images/pause.png","images/pause_s.png",CC_CALLBACK_0(TopMenu::pauseGame,this));
    Menu* menuPause = Menu::create(btnPause,NULL);
    menuPause->alignItemsVertically();
    menuPause->setPosition(60.0f,visibleSize.height - 50.0f);
    this->addChild(menuPause,1,100);
    
    this->m_menuBtnPause = menuPause;
    
    ///声音
    
    //音乐
    auto musicOnMenuItem  =MenuItemImage::create("images/ico_audio_on.png","images/ico_audio_on.png");
    auto musicOffMenuItem  =MenuItemImage::create("images/ico_audio_off.png","images/ico_audio_off.png");
    
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TopMenu::menuMusicToggleCallback,this),musicOnMenuItem,musicOffMenuItem,NULL );
    
    auto menuMusic = Menu::create(musicToggleMenuItem, nullptr );
    menuMusic->setPosition(visibleSize.width - 80.0f,visibleSize.height - 50.0f);
    this->addChild(menuMusic);
    
    musicToggleMenuItem->setSelectedIndex((Audio::getInstance()->getbIsOpenMusic() ? 0 : 1));
    
    ///技能0,刷子
    
    ///技能1,重新排列
    
    ///技能2,炸弹
    
#if 0
    MenuItemImage* btnSkill0 = MenuItemImage::create("images/Props_Paint.png","images/Props_Paint_s.png",CC_CALLBACK_0(TopMenu::pauseGame,this));
    MenuItemImage* btnSkill1 = MenuItemImage::create("images/Props_Rainbow.png","images/Props_Rainbow_s.png",CC_CALLBACK_0(TopMenu::pauseGame,this));
    MenuItemImage* btnSkill2 = MenuItemImage::create("images/Props_Bomb.png","images/Props_Bomb_s.png",CC_CALLBACK_0(TopMenu::pauseGame,this));
    
    Menu* menuSkill= Menu::create(btnSkill0,btnSkill1,btnSkill2,NULL);
    menuSkill->alignItemsHorizontallyWithPadding(40.0f);
    menuSkill->setPosition(visibleSize.width - 220.0f,visibleSize.height - 200.0f);
    this->addChild(menuSkill);
#endif
    
    this->initScore();
}
void TopMenu::menuMusicToggleCallback(Ref* pSender)
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

void TopMenu::initScore()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //--------------------------------------
    ///最高分
    Sprite* spHighestScore = Sprite::create("images/ico_heigh_score_str.png");
    spHighestScore->setPosition(visibleSize.width/2 - 100.0f,visibleSize.height - 50.0f);
    this->addChild(spHighestScore);
    
    string strHighestScore = StringUtils::format("%d",GAMEDATA::getInstance()->getHistoryScore());
    highestScore = LabelAtlas::create(strHighestScore, "images/numbers/number_highest_score.png",28,42,'0');
    highestScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    highestScore->setPosition(spHighestScore->getPosition() + Vec2(90.0f,0.0f));
    this->addChild(highestScore);
    
    //--------------------------------------
    ///等级
    Sprite* spLevel = Sprite::create("images/ico_level_str.png");
    spLevel->setPosition(60.0f,visibleSize.height - 120.0f);
    this->addChild(spLevel);
    
    string strLevel= StringUtils::format("%d",GAMEDATA::getInstance()->getNextLevel());
    level = LabelAtlas::create(strLevel, "images/numbers/number_target_score.png",28,41,'0');
    level->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    level->setPosition(spLevel->getPosition() + Vec2(50.0f,0.0f));
    this->addChild(level);
    
    //ChineseWord("guanqia") + StringUtils::format("%d",GAMEDATA::getInstance()->getNextLevel()
    
    //--------------------------------------
    ///目标分数
    Sprite* spTarget = Sprite::create("images/ico_target_score_str.png");
    spTarget->setPosition(visibleSize.width - 230.0f,visibleSize.height - 120.0f);
    this->addChild(spTarget);
    
    string strTarget= StringUtils::format("%d",GAMEDATA::getInstance()->getNextScore());
    targetScore = LabelAtlas::create(strTarget, "images/numbers/number_target_score.png",28,41,'0');
    targetScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    targetScore->setPosition(spTarget->getPosition() + Vec2(65.0f,0.0f));
    this->addChild(targetScore);
    
    
    //--------------------------------------
    ///当前分数
    Sprite* spCurrent = Sprite::create("images/ico_current_score_str.png");
    spCurrent->setPosition(visibleSize.width/2 - 150.0f,visibleSize.height - 120.0f);
    this->addChild(spCurrent);
    
    string strCurrent= StringUtils::format("%d",GAMEDATA::getInstance()->getCurScore());
    curScore = LabelAtlas::create(strCurrent, "images/numbers/number_curent_score.png",28,41,'0');
    curScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    curScore->setPosition(spCurrent->getPosition() + Vec2(65.0f,0.0f));
    this->addChild(curScore);

}

void TopMenu::refresh()
{
	//char buf[64];
	//sprintf(buf,"%d",GAMEDATA::getInstance()->getCurScore());
    
    string current = StringUtils::format("%d",GAMEDATA::getInstance()->getCurScore());
    
	curScore->setString(current);

	string history = StringUtils::format("%d",GAMEDATA::getInstance()->getHistoryScore());
    
    highestScore->setString(history);

	string guanqia = StringUtils::format("%d",GAMEDATA::getInstance()->getNextLevel());
    
	level->setString(guanqia);

	string target = StringUtils::format("%d",GAMEDATA::getInstance()->getNextScore());
    
	targetScore->setString(target);
}
Vec2 TopMenu::getPosCurScore()
{
    return this->curScore->getPosition();
}
void TopMenu::pauseGame()
{
    CCLOG("PAUSE!");
    this->m_menuBtnPause->setEnabled(false);
    //Director::getInstance()->replaceScene(GameScene::create());
    GameLayer* gameLayer = (GameLayer*)this->getParent();
    //gameLayer->setiGameState(2);
    
    Scene* scene = (Scene*)gameLayer->getParent();
    scene->addChild(PauseLayer::create(),2);
}
