#include "MenuScene.h"
#include "MenuLayer.h"
#include "Audio.h"

//using namespace CocosDenshion;

bool MenuScene::init()
{
	if(!Scene::init())
    {
		return false;
	}
    
	Audio::getInstance()->playBGM();
    
	this->addChild(MenuLayer::create());
    
	return true;
}