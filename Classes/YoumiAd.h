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

    // �������ʹ��
    static void showSpotAd();           //ͨ��JNI����JAVA��̬������ʵ��չʾ�������
    static bool hideSpotAd();          //ͨ��JNI����JAVA��̬������ʵ�����ز������
    static void exitApp();                //ͨ��JNI����JAVA��̬������ʵ���˳�Ӧ��
};
