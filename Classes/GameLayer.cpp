#include "GameLayer.h"
#include "FloatWord.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "MenuScene.h"
#include "Audio.h"
bool GameLayer::init()
{
	if(!Layer::init())
    {
		return false;
	}

	matrix = nullptr;
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	menu = TopMenu::create();
	this->addChild(menu);
    
	linkNum = Label::create("","Arial",40);
	linkNum->setPosition(visibleSize.width/2,visibleSize.height-320);
	linkNum->setVisible(false);
	this->addChild(linkNum,1);
    
    // 帧缓存
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    // 纹理缓存
    //auto textureCache = Director::getInstance()->getTextureCache();
    //textureCache->addImage(s_backgound);
    
    spriteFrameCache->addSpriteFramesWithFile("mainStar.plist");

	this->floatLevelWord();
    
    //底下的一条线
    Sprite* spLine = Sprite::create("images/img_bars.png");
    spLine->setPosition(Vec2(visibleSize.width/2, 95.0f));
    this->addChild(spLine);
    
	return true;
}

///开始新的一局
void GameLayer::floatLevelWord()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    
    string strGuanqia = ChineseWord("guanqia") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextLevel())->_string;
    
	_levelMsg = FloatWord::create(strGuanqia,50,Point(visibleSize.width,visibleSize.height/3*2));
    
	this->addChild(_levelMsg,1);
    
    ///开始新局
	_levelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::floatTargetScoreWord,this));
    
	Audio::getInstance()->playReadyGo();
}

void GameLayer::floatTargetScoreWord()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_targetScore = FloatWord::create(
		ChineseWord("mubiao") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen"),
		50, Point(visibleSize.width,visibleSize.height/3)
		);
	this->addChild(_targetScore,1);
	_targetScore->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removeFloatWord,this));
}

void GameLayer::removeFloatWord()
{
	_levelMsg->floatOut(0.5f,nullptr);
	_targetScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

void GameLayer::showStarMatrix()
{
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
}

void GameLayer::update(float delta){
	if(matrix){
		matrix->updateStar(delta);
	}
}

bool GameLayer::onTouchBegan(Touch* touch,Event* event){
	Point p = touch->getLocationInView();
	p = Director::getInstance()->convertToGL(p);
	CCLOG("x=%f y=%f",p.x,p.y);
	if(matrix){
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshMenu()
{
	menu->refresh();
}

void GameLayer::showLinkNum(int size)
{
	
	string s = String::createWithFormat("%d",size)->_string + ChineseWord("lianji") + 
		String::createWithFormat("%d",size*size*5)->_string + ChineseWord("fen");
	linkNum->setString(s);
	linkNum->setVisible(true);
}


///飞一个分数数字到分数上去
void GameLayer::flyNumScore(int num,Vec2 _position)
{
    LabelAtlas* curScore = LabelAtlas::create(StringUtils::format("%d",num), "images/numbers/number_curent_score.png",28,41,'0');
    curScore->setPosition(_position - Vec2(0.0f, 10.0f));
    this->addChild(curScore);
    
    //MoveTo* moveTo = MoveTo::create(0.8f, this->menu->getPosCurScore());
    JumpTo* jumpTo = JumpTo::create(0.8, this->menu->getPosCurScore(), 50.0f, 1);
    CallFunc* callBack = CallFunc::create([=]
                                          {
                                              curScore->removeFromParent();
                                          });

    Sequence* seq = Sequence::create(jumpTo,callBack, NULL);
    curScore->runAction(seq);
}

void GameLayer::hideLinkNum(){
	linkNum->setVisible(false);
}

void GameLayer::floatLeftStarMsg(int leftNum){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("shengyu") + String::createWithFormat("%d",leftNum)->_string +ChineseWord("ge"), 
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
    int jiangLiScore = GAMEDATA::getInstance()->getJiangli(leftNum);
	FloatWord* leftStarMsg2 = FloatWord::create(ChineseWord("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/2 - 50));
	this->addChild(leftStarMsg2);

	leftStarMsg1->floatInOut(0.5f,1.0f,
				[=](){
					hideLinkNum();
					matrix->setNeedClear(true);
					GAMEDATA* data = GAMEDATA::getInstance();
					data->setCurScore(data->getCurScore() + jiangLiScore);
					if(data->getCurScore() > data->getHistoryScore()){
						data->setHistoryScore(data->getCurScore());
					}
					refreshMenu();
				});
	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
}

void GameLayer::gotoNextLevel()
{
	refreshMenu();
	floatLevelWord();
}

void GameLayer::gotoGameOver(){
	//ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩﬂ∑Ôø?
	GAMEDATA::getInstance()->saveHighestScore();
	//∆ÆÔøΩ÷£ÔøΩÔøΩ–ªÔøΩscene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameOver = FloatWord::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOver);
	gameOver->floatIn(1.0f,[]{Director::getInstance()->replaceScene(MenuScene::create());});
}
