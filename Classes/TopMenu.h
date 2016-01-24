#ifndef _TOPMENU_H_
#define _TOPMENU_H_

#include "cocos2d.h"
#include "PauseLayer.h"
#include "Audio.h"

using namespace cocos2d;
class TopMenu : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh();
    
public:
    Vec2 getPosCurScore();
    
private:
    void initView();
    void initScore();
    void pauseGame();
    
    void menuMusicToggleCallback(Ref* pSender);
private:
	LabelAtlas* highestScore;
	LabelAtlas* level;
	LabelAtlas* targetScore;
	LabelAtlas* curScore;
    
    Menu* m_menuBtnPause;
};
#endif