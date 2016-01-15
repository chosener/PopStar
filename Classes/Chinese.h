#ifndef _CHINESEWORD_H_
#define _CHINESEWORD_H_
#include <string>
#include <cocos2d.h>
using namespace std;
using namespace cocos2d;

static ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("ChineseWords.xml");

string ChineseWord(const char* wordId);

#endif