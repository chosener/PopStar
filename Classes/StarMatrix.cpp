#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include "ComboEffect.h"
#include "Audio.h"
#include <ctime>
float StarMatrix::ONE_CLEAR_TIME = 0.05f;
StarMatrix* StarMatrix::create(GameLayer* layer){
	StarMatrix* ret = new StarMatrix();
	if(ret && ret->init(layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer){
	if(!Node::init()){
		return false;
	}
	m_layer = layer;
	needClear = false;
	clearSumTime = 0;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	initMatrix();
	return true;
}

void StarMatrix::updateStar(float delta){
	
	for(int i = 0;i < ROW_NUM;i++){
		for(int j = 0;j< COL_NUM;j++){
			if(stars[i][j]!=nullptr){
				stars[i][j]->updatePosition();
			}
		}
	}
	if(needClear){
		clearSumTime += delta;
		if(clearSumTime > ONE_CLEAR_TIME){
			clearMatrixOneByOne();
			clearSumTime = 0;
		}
	}
	
}

void StarMatrix::onTouch(const Point& p)
{
    Vec2 pos = p - Vec2(0.0f, 80.0f);
	Star* s = getStarByTouch(pos);
	if(s)
    {
        genSelectedList(s);
        CCLOG("SIZE = %d",(int)selectedList.size());
        deleteSelectedList();
	}
}

void StarMatrix::setNeedClear(bool b){
	needClear = b;
}
void StarMatrix::initMatrix(){
	srand(time(0));
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			int color = abs(rand()%Star::COLOR_MAX_NUM);
			if(color < 0)
				CCLOG("color i=%d,j=%d");
			Star* star = Star::create(color);
			stars[i][j] = star;
			star->setPosition(getPositionByIndex(i,j) + Point(0,100));
			star->setDesPosition(getPositionByIndex(i,j));
			star->setIndex_ij(i,j);
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i,int j){
	float x = j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y = (StarMatrix::COL_NUM - i)*Star::STAR_HEIGHT - Star::STAR_HEIGHT/2;
	return Point(x,y) + Vec2(0.0f, 80.0f);
}

Star* StarMatrix::getStarByTouch(const Point& p){
	int k = p.y/Star::STAR_HEIGHT;//这里要用K转一下int 不然得不到正确结果
	int i = ROW_NUM - 1 - k;
	int j = p.x/Star::STAR_WIDTH;
	if(i >= 0 && i < ROW_NUM && 
	   j >= 0 && j < COL_NUM &&
	   stars[i][j] != nullptr){
		CCLOG("i=%d,j=%d",i,j);
		return stars[i][j];
	}else{
		return nullptr;
	}
}

void StarMatrix::genSelectedList(Star* s){
	selectedList.clear();
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for(it= travelList.begin();it != travelList.end();){
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//上
		if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i-1][index_j]);
		}
		//下
		if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i+1][index_j]);
		}
		//左
		if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j-1]);
		}
		//右
		if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j+1]);
		}
		if(!star->isSelected()){
			star->setSelected(true);
			selectedList.push_back(star);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
}

void StarMatrix::deleteSelectedList()
{
	if(selectedList.size() <= 1)
    {
		m_layer->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return;
	}

	for(auto it = selectedList.begin();it != selectedList.end();it++)
    {
		Star* star = *it;
        Vec2 pos = star->getPosition();
        //pos = Vec2(0, 0);
		//粒子效果
		showStarParticleEffect(star->getColor(),pos,this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
		//播放音效
		Audio::getInstance()->playPop();
	}
    int sizeSelected = (int)selectedList.size();
	//COMBO效果
	showComboEffect(sizeSelected,this);
    
	Audio::getInstance()->playCombo(sizeSelected);

	refreshScore();
    
	m_layer->showLinkNum(sizeSelected);
    
	adjustMatrix();
    
	if(isEnded())
    {
		m_layer->floatLeftStarMsg(getLeftStarNum());//通知layer弹出剩余星星的信息
		CCLOG("ENDED");
	}

}

void StarMatrix::adjustMatrix(){
	//垂直方向调整
	for(int i = ROW_NUM-1;i>=0;i--){
		for(int j = COL_NUM-1;j>=0;j--){
			if(stars[i][j] == nullptr){
				int up = i;
				int dis = 0;
				while(stars[up][j] == nullptr){
					dis++;
					up--;
					if(up<0){
						break;
					}
				}
				
				for(int begin_i = i - dis;begin_i >= 0;begin_i--){
					if(stars[begin_i][j] == nullptr)
						continue;
					Star* s = stars[begin_i + dis][j] = stars[begin_i][j];
					s->setIndex_ij(begin_i + dis,j);
					s->setDesPosition(getPositionByIndex(begin_i + dis,j));
					stars[begin_i][j] = nullptr;
				}
			}else{
				continue;
			}
		}
	}
	//水平方向调整
	for(int j = 0;j < COL_NUM;j++){
		if(stars[ROW_NUM-1][j] == nullptr){
			int des = 0;
			int right = j;
			while(stars[ROW_NUM-1][right] == nullptr){
				des++;
				right++;
			}
			for(int begin_i = 0;begin_i<ROW_NUM;begin_i++){
				for(int begin_j = j + des;begin_j < COL_NUM;begin_j++){
					if(stars[begin_i][begin_j] == nullptr)
						continue;
					Star* s = stars[begin_i][begin_j - des] = stars[begin_i][begin_j];
					s->setIndex_ij(begin_i,begin_j - des);
					s->setDesPosition(getPositionByIndex(begin_i,begin_j - des));
					stars[begin_i][begin_j] = nullptr;
				}
			}
		}
	}

}


void StarMatrix::refreshScore()
{
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + selectedList.size()*selectedList.size()*5);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	m_layer->refreshMenu();
}


bool StarMatrix::isEnded(){
	bool bRet = true;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			int curColor = stars[i][j]->getColor();
			//上
			if(i-1>=0 && stars[i-1][j]!=nullptr && stars[i-1][j]->getColor() ==  curColor)
				return false;
			//下
			if(i+1<ROW_NUM && stars[i+1][j]!=nullptr && stars[i+1][j]->getColor() == curColor)
				return false;
			//左
			if(j-1>=0 && stars[i][j-1]!=nullptr && stars[i][j-1]->getColor() == curColor)
				return false;
			//右
			if(j+1<COL_NUM && stars[i][j+1]!=nullptr && stars[i][j+1]->getColor() == curColor)
				return false;
		}
	}
	return bRet;
}

void StarMatrix::clearMatrixOneByOne(){
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			showStarParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}
	//能够执行到这一句说明Matrix全为空，不在需要清空
	needClear = false;
	//转到下一关或者弹出结束游戏的窗口
	if(GAMEDATA::getInstance()->getCurScore() >= GAMEDATA::getInstance()->getNextScore())
    {
		GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
		m_layer->gotoNextLevel();
	}else{
		m_layer->gotoGameOver();
		CCLOG("GAME OVER");
	}
}

int StarMatrix::getLeftStarNum(){
	int ret = 0;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			ret++;
		}
	}
	return ret;
}