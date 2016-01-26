//
//  JniSms.cpp
//  TowerDefense
//
//  Created by zxtw on 14-4-14.
//
//


#include "JniSms.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "../../../android-ndk-r8e/platforms/android-14/arch-arm/usr/include/jni.h"
#include <jni.h>
#include "../cocos2d/cocos/platform/android/jni/JniHelper.h"
#endif


#define CLASS_NAME "org/cocos2dx/cpp/JniHelper"
#define CLASS_ACTIVITY_NAME "com/ds/popstar/AppActivity"

extern "C"
{

    //-------------------------------------------------
    //测试
    void testGame(const char *txt)
    {
        //判断当前是否为Android平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "testGame", "(Ljava/lang/String;)V"))
        {
            CCLog("JNI:testGame函数存在");

            jstring jTxt = t.env->NewStringUTF(txt);

            t.env->CallStaticVoidMethod(t.classID, t.methodID,jTxt);
            t.env->DeleteLocalRef(jTxt);
        }
#endif

    }
    //-------------------------------------------------
    /**[JNI]显示退出对话框*/
    void showDialogExit()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialogExit", "()V"))
        {
            CCLog("JNI:showDialogExit函数存在");

            t.env->CallStaticVoidMethod(t.classID, t.methodID);

        }
#endif
    }
    //-------------------------------------------------
    ///[JNI]发送短信
    void setEnableAD(int enable)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_ACTIVITY_NAME, "setEnableAD", "(I)V"))
        {
            CCLog("JNI:setEnableAD函数存在");
            
            t.env->CallStaticVoidMethod(t.classID, t.methodID,enable);
            
        }
#endif
    }
    //-------------------------------------------------
    ///[JNI]显示插屏广告
    void showAD()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_ACTIVITY_NAME, "showMyAD", "()V"))
        {
            CCLog("JNI:showMyAD函数存在");
            
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            
        }
#endif
    }
    //-------------------------------------------------
    ///[JNI]分享游戏
    void shareSelfGame()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_ACTIVITY_NAME, "shareSelfGame", "()V"))
        {
            CCLog("JNI:shareSelfGame函数存在");
            
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            
        }
#endif
    }
    
    //-------------------------------------------------
    ///[JNI]发送短信
    void sendMessageJNI(int index,const char* markSms)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sendMessageJNI", "(ILjava/lang/String;)V"))
        {
            CCLog("JNI:sendMessageJNI函数存在");
            jstring jMarkSms = t.env->NewStringUTF(markSms);
            
            t.env->CallStaticVoidMethod(t.classID, t.methodID,index,jMarkSms);
            
            t.env->DeleteLocalRef(jMarkSms);
            
        }
#endif
    }
    //-------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    void Java_org_cocos2dx_cpp_JniHelper_exitApp(JNIEnv *env, jobject thiz)
    {

        Director::getInstance()->end();
        
        CCLog("[Java_org_cocos2dx_cpp_JniHelper_exitApp()] is called !");

    }
#endif
    //--------------------------------------------------
    //短信支付结果
    
#if 0
    extern "C"
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        
        void Java_org_cocos2dx_cpp_AppActivity_paySuccess(JNIEnv *env, jobject thiz, jint index)
        {
            CCLog("[Java_org_cocos2dx_cpp_AppActivity_payResult()] is called !");

            DSMngSms::getInstance()->paySuccess(index);
        }
        
#endif

    }
#endif

    //--------------------------------------------------
    // add these jni menthod
	void vibrateJNI(long long time)
	{
        //判断当前是否为Android平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		JniMethodInfo methodInfo;
		if (! JniHelper::getStaticMethodInfo(methodInfo,CLASS_ACTIVITY_NAME, "vibrate", "(J)V"))
		{
			return;
		}
        CCLog("JNI:vibrateJNI函数存在");
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, time);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif

	}
    
    //-----------------------------------------------------
	void vibrateWithPatternJNI(long long pattern[], int repeat)
	{
        //判断当前是否为Android平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		JniMethodInfo methodInfo;
		if (! JniHelper::getStaticMethodInfo(methodInfo,CLASS_ACTIVITY_NAME, "vibrateWithPattern", "([JI)V"))
		{
			return;
		}
		int elements = sizeof(pattern);
		jlongArray jLongArray = methodInfo.env->NewLongArray(elements);
		methodInfo.env->SetLongArrayRegion(jLongArray, 0, elements, (jlong*) pattern);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jLongArray, repeat);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif

	}
	void cancelVibrateJNI()
	{
        //判断当前是否为Android平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		JniMethodInfo methodInfo;
		if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_ACTIVITY_NAME,"cancelVibrate", "()V"))
		{
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif

	}
    
    int getMusicEnable()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        JniMethodInfo minfo;

        bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_ACTIVITY_NAME,"getMusicEnable","()I");
        jint _int ;
        if (!isHave)
        {

            return -10000;
        }
        else
        {

            _int = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);

            return _int;
        }
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return 1;
#endif
        
    }

}