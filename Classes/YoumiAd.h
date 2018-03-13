#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#include "cocos2d.h"
#endif
using namespace cocos2d;
class YoumiAd
{
public:

    YoumiAd();
    virtual ~YoumiAd();

    // 插屏广告使用
    static void showSpotAd();           //通过JNI调用JAVA静态函数，实现展示插屏广告
    static bool hideSpotAd();          //通过JNI调用JAVA静态函数，实现隐藏插屏广告
    static void exitApp();                //通过JNI调用JAVA静态函数，实现退出应用
};