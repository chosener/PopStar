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

	this->addChild(MenuLayer::create());
    
	return true;
}