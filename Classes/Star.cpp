#include "Star.h"

Star* Star::create(int color){
	Star* ret = new Star();
	//if(ret && ret->initWithFile(ret->getImage(color)))
    if(ret && ret->initWithSpriteFrameName(ret->getImageFrame(color)))
    {
		ret->color = color;
		ret->selected = false;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

string Star::getImage(int color)
{
	switch(color)
    {
    case Color_BLUE:
		return "blue.png";
	case Color_GREEN:
		return "green.png";
	case Color_YELLOW:
		return "orange.png";
	case Color_RED:
		return "red.png";
	case Color_PURPLE:
		return "purple.png";
	}
}
string  Star::getImageFrame(int color)
{
    switch(color){
        case Color_BLUE:
            return "40.png";
        case Color_GREEN:
            return "20.png";
        case Color_YELLOW:
            return "30.png";
        case Color_RED:
            return "50.png";
        case Color_PURPLE:
            return "10.png";
    }
}

bool Star::isSelected(){
	return selected;
}

int Star::getColor(){
	return color;
}

void Star::setDesPosition(const Point& p)
{
	desPosition = p;
}

void Star::updatePosition()
{
	if(desPosition.y != getPositionY())
    {
		setPositionY(getPositionY() - MOVE_SPEED);
		if(getPositionY() < desPosition.y)
        {
			setPositionY(desPosition.y);
		}
	}
	if(desPosition.x != getPositionX())
    {
		setPositionX(getPositionX() - MOVE_SPEED);
		if(getPositionX() < desPosition.x){
			setPositionX(desPosition.x);
		}
	}
}