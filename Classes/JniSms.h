//
//  JniSms.h
//  TowerDefense
//
//  Created by zxtw on 14-4-14.
//
//

#ifndef __TowerDefense__JniSms__
#define __TowerDefense__JniSms__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
extern "C"
{
    //测试
    void testGame(const char *txt);
    /**[JNI]显示退出对话框*/
    void showDialogExit();
    ///[JNI]发送短信
    void sendMessageJNI(int index,const char* markSms);
    // add these menthod phone vibrate
    void vibrateJNI(long long time);
    void vibrateWithPatternJNI(long long pattern[], int repeat);
    void cancelVibrateJNI();
    int getMusicEnable();
    void setEnableAD(int enable);
    void showAD();
}

#endif /* defined(__TowerDefense__JniSms__) */