#include "YoumiAd.h"

YoumiAd::YoumiAd(){}
YoumiAd::~YoumiAd(){}

/**
 * 展示插屏广告（C++ 通过JNI 调用JAVA方法）
 */
void YoumiAd::showSpotAd()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

    // 定义JNI函数信息结构体
    JniMethodInfo showSpotAd;

    /**
     * @param 第一个参数：JNI函数信息结构体
     * @param 第二个参数：与你Android项目中的主Activity所在的包名对应，Demo中为：com.youmi.android.cocos2dx.demo.MainActivity，需要改为com/youmi/android/cocos2dx/denmo/MainActivity
     * @param 第三个参数：Android项目中对应的Activity里面所定义的JAVA静态函数名，Demo中为：showSpotAd
     * @param 第四个参数：该JAVA方法所需要传入的值，格式为"(JAVA方法中需要传入的值)c++中本函数返回值"，Demo中，showSpotAd的JAVA方法不需要传入值，而YoumiAd::showSpotAd()返回值为void，所以这里写 "()V"
     * @return 返回bool值表示是否找到静态函数
     */
    bool isHave = JniHelper::getStaticMethodInfo(showSpotAd, "com/youmi/android/cocos2dx/demo/MainActivity", "showSpotAd", "()V");

    if (!isHave) {
        log("jni:showSpotAd函数不存在");
    } else {
        log("jni:showSpotAd函数存在");
        showSpotAd.env->CallStaticVoidMethod(showSpotAd.classID, showSpotAd.methodID);
    }
    #endif
}

/**
 * 隐藏插屏广告（C++ 通过JNI 调用JAVA方法）
 */
bool YoumiAd::hideSpotAd()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

    JniMethodInfo hideSpotAd;

    bool isHave = JniHelper::getStaticMethodInfo(hideSpotAd, "com/youmi/android/cocos2dx/demo/MainActivity", "hideSpotAd", "()Z");

    if (!isHave) {
        log("jni:hideSpotAd函数不存在");
        return false;
    } else {
        log("jni:hideSpotAd函数存在");
        return hideSpotAd.env->CallStaticBooleanMethod(hideSpotAd.classID, hideSpotAd.methodID);
    }
    #endif
}

/**
 * 退出应用 （C++ 通过JNI 调用JAVA方法）
 */
void YoumiAd::exitApp()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

    JniMethodInfo exitApp;

    bool isHave = JniHelper::getStaticMethodInfo(exitApp, "com/youmi/android/cocos2dx/demo/MainActivity", "exitApp", "()V");

    if (!isHave) {
        log("jni:exitApp函数不存在");
    } else {
        log("jni:exitApp函数存在");
        exitApp.env->CallStaticVoidMethod(exitApp.classID, exitApp.methodID);
    }
    #endif
}
