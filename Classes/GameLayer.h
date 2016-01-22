#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
#include "FloatWord.h"
#include "TopMenu.h"
#include "GameData.h"
#include "StarMatrix.h"
#include "GameScene.h"
using namespace cocos2d;
class StarMatrix;
class GameLayer : public Layer
{
public:
    GameLayer();
    ~GameLayer();
	virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
	CREATE_FUNC(GameLayer);
	void floatLevelWord();
	void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix();
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch* touch,Event* event);
	void refreshMenu();
	void showLinkNum(int size);
    ///飞一个分数数字到分数上去
    void flyNumScore(int num,Vec2 _position);
	void hideLinkNum();
	void floatLeftStarMsg(int leftNum);
	void gotoNextLevel();
	void gotoGameOver();
    
    void reset();
    
    //0-init,1-playing,2-pause,3-gameover
    CC_SYNTHESIZE(int, m_iGameState, iGameState);
    
private:
    /**初始化事件*/
    void initEventCustom();
    void onCustomEventReset(EventCustom* event);
private:
    EventListenerTouchOneByOne* listener;
	FloatWord* _levelMsg;
	FloatWord* _targetScore;
	TopMenu* menu;
	StarMatrix* matrix;
	Label* linkNum;

};
#endif