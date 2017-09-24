#include "YoumiAd.h"

YoumiAd::YoumiAd(){}
YoumiAd::~YoumiAd(){}

/**
 * չʾ������棨C++ ͨ��JNI ����JAVA������
 */
void YoumiAd::showSpotAd()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨

    // ����JNI������Ϣ�ṹ��
    JniMethodInfo showSpotAd;

    /**
     * @param ��һ��������JNI������Ϣ�ṹ��
     * @param �ڶ�������������Android��Ŀ�е���Activity���ڵİ�����Ӧ��Demo��Ϊ��com.youmi.android.cocos2dx.demo.MainActivity����Ҫ��Ϊcom/youmi/android/cocos2dx/denmo/MainActivity
     * @param ������������Android��Ŀ�ж�Ӧ��Activity�����������JAVA��̬��������Demo��Ϊ��showSpotAd
     * @param ���ĸ���������JAVA��������Ҫ�����ֵ����ʽΪ"(JAVA��������Ҫ�����ֵ)c++�б���������ֵ"��Demo�У�showSpotAd��JAVA��������Ҫ����ֵ����YoumiAd::showSpotAd()����ֵΪvoid����������д "()V"
     * @return ����boolֵ��ʾ�Ƿ��ҵ���̬����
     */
    bool isHave = JniHelper::getStaticMethodInfo(showSpotAd, "com/youmi/android/cocos2dx/demo/MainActivity", "showSpotAd", "()V");

    if (!isHave) {
        log("jni:showSpotAd����������");
    } else {
        log("jni:showSpotAd��������");
        showSpotAd.env->CallStaticVoidMethod(showSpotAd.classID, showSpotAd.methodID);
    }
    #endif
}

/**
 * ���ز�����棨C++ ͨ��JNI ����JAVA������
 */
bool YoumiAd::hideSpotAd()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨

    JniMethodInfo hideSpotAd;

    bool isHave = JniHelper::getStaticMethodInfo(hideSpotAd, "com/youmi/android/cocos2dx/demo/MainActivity", "hideSpotAd", "()Z");

    if (!isHave) {
        log("jni:hideSpotAd����������");
        return false;
    } else {
        log("jni:hideSpotAd��������");
        return hideSpotAd.env->CallStaticBooleanMethod(hideSpotAd.classID, hideSpotAd.methodID);
    }
    #endif
}

/**
 * �˳�Ӧ�� ��C++ ͨ��JNI ����JAVA������
 */
void YoumiAd::exitApp()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨

    JniMethodInfo exitApp;

    bool isHave = JniHelper::getStaticMethodInfo(exitApp, "com/youmi/android/cocos2dx/demo/MainActivity", "exitApp", "()V");

    if (!isHave) {
        log("jni:exitApp����������");
    } else {
        log("jni:exitApp��������");
        exitApp.env->CallStaticVoidMethod(exitApp.classID, exitApp.methodID);
    }
    #endif
}
