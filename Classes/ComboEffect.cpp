#include "ComboEffect.h"
void showComboEffect(int size,Node* node)
{
	if(size<3)
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* comboSprite;
    if(size>=19)
    {
        comboSprite = Sprite::create("images/combo/combo_9.png");
    }
    else if(size>=15)
    {
        comboSprite = Sprite::create("images/combo/combo_8.png");
    }
    else if(size>=12)
    {
        comboSprite = Sprite::create("images/combo/combo_7.png");
    }
    else if(size>=10)
    {
        comboSprite = Sprite::create("images/combo/combo_6.png");
    }
    else if(size>=7)
    {
        comboSprite = Sprite::create("images/combo/combo_5.png");
    }
    else if(size>=6)
    {
        comboSprite = Sprite::create("images/combo/combo_4.png");
    }
    else if(size>=5)
    {
		comboSprite = Sprite::create("images/combo/combo_3.png");
	}
    else if(size>=4)
    {
		comboSprite = Sprite::create("images/combo/combo_2.png");
	}
    else
    {
		comboSprite = Sprite::create("images/combo/combo_1.png");
	}

	comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	node->addChild(comboSprite);

	Blink* blink = Blink::create(1.0f,5);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(blink,remove,nullptr);
	comboSprite->runAction(action);
}