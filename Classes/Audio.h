#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "cocos2d.h"
using namespace cocos2d;

class Audio
{
public:
    Audio();
    ~Audio();
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playPop();
	void prepare();
	void playCombo(int size);
    
    void pauseBGM();
    void resumeBGM();
private:
    void init();
    
public:
    CC_SYNTHESIZE(bool, m_bIsOpenMusic, bIsOpenMusic);
private:
	static Audio* m_instance;
};
#endif