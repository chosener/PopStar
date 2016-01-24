#ifndef _STAR_H_
#define _STAR_H_

#include <iostream>
#include "GlobalEnum.h"

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Star : public Sprite
{
public:

	static Star* create(int color);
	bool isSelected();
	inline void setSelected(bool b){selected = b;}
	int getColor();
	void setDesPosition(const Point& p);
	inline Point getDesPosition(){return desPosition;}
	void updatePosition();
	inline int getIndexI(){return index_i;}
	inline int getIndexJ(){return index_j;}
	inline void setIndex_ij(int i,int j){index_i = i;index_j = j;}
private:
	string getImage(int color);
    string  getImageFrame(int color);
public:
	const static int MOVE_SPEED = 12;
	static const int COLOR_MAX_NUM = 5;
	static const int STAR_WIDTH = 72;
	static const int STAR_HEIGHT = 72;
private:
	int color;
	Point desPosition;
	bool selected;
	int index_i;
	int index_j;
};
#endif