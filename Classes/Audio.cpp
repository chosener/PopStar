#include "Audio.h"
#include "SimpleAudioEngine.h"

Audio* Audio::m_instance = nullptr;

Audio::Audio()
{
    this->init();
}
Audio::~Audio()
{
    
}
Audio* Audio::getInstance()
{
	if(m_instance == nullptr)
    {
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::init()
{
    this->setbIsOpenMusic(true);
}

void Audio::playBGM()
{
    if(!this->m_bIsOpenMusic)
        return;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg",true);
}

void Audio::pauseBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Audio::resumeBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void Audio::playReadyGo()
{
    if(!this->m_bIsOpenMusic)
        return;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg",false);
}

void Audio::playPop()
{
    if(!this->m_bIsOpenMusic)
        return;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);
}

void Audio::playCombo(int size)
{
    if(!this->m_bIsOpenMusic)
        return;
	if(size < 5)
		return;
	if(size >= 10)
    {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg",false);
	}
    else if(size >= 7)
    {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.ogg",false);
	}
    else
    {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.ogg",false);
	}
}
void Audio::prepare()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");
}