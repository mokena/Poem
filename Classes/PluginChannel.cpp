#include "PluginChannel.h"
#include <stdlib.h>
#include "cocos2d.h"
#include "../proj.android-studio/app/protocols/include/ProtocolAds.h"
#include "../proj.android-studio/app/protocols/include/AgentManager.h"

// #include "PartViews.h"

using namespace anysdk::framework;

#define  LOG_TAG    "PluginChannel"

PluginChannel* PluginChannel::_pInstance = NULL;

PluginChannel::PluginChannel()
{
    
}

PluginChannel::~PluginChannel()
{
    unloadPlugins();
}

PluginChannel* PluginChannel::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new PluginChannel();
    }
    return _pInstance;
}

//使用anysdk.com的时候注释掉这个宏就可以
//#define isQudaoInfo 1

void PluginChannel::loadPlugins()
{
    printf("Load plugins invoked\n");
    /**
     * appKey、appSecret、privateKey不能使用Sample中的值，需要从打包工具中游戏管理界面获取，替换
     * oauthLoginServer参数是游戏服务提供的用来做登陆验证转发的接口地址。
     */

    std::string appKey = "151BEEEA-C1D6-8FEC-F7EE-01B9D4D806CE";
    std::string appSecret = "02cab009c507e301d2d6c363502cabfb";
    std::string privateKey = "E0601CDE2E245675E8C57F4DC6B2D746";
    std::string oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
    
    AgentManager::getInstance()->init(appKey,appSecret,privateKey,oauthLoginServer);

    //对用户系统设置监听类
    if(AgentManager::getInstance()->getAdsPlugin())
    {
        AgentManager::getInstance()->getAdsPlugin()->setAdsListener(this);
    }

}

void PluginChannel::unloadPlugins()
{
    printf("Unload plugins invoked\n");
    AgentManager::getInstance()->unloadAllPlugins();
}

void PluginChannel::onAdsResult(AdsResultCode code, const char* msg)
{
    switch(code)
    {
        case kAdsReceived://广告接受成功回调

            break;
        case kAdsShown://广告展示回调

            break;
        case kAdsDismissed://广告消失回调

            break;
        case kPointsSpendSucceed://积分设置成功回调

            break;
        case kPointsSpendFailed://积分设置失败回调

            break;
        case kNetworkError://网络错误回调

            break;
        case kUnknownError://未知错误回调

            break;
        case kOfferWallOnPointsChanged://积分改变回调

            break;
        default:
            break;
    }
}

void PluginChannel::preloadAds()
{
    ProtocolAds* ads = AgentManager::getInstance()->getAdsPlugin();

    if( ads && ads->isAdTypeSupported(AD_TYPE_BANNER) )
    {
        ads->preloadAds(AD_TYPE_BANNER);
    }
}

void PluginChannel::showAds()
{
    ProtocolAds* ads = AgentManager::getInstance()->getAdsPlugin();

    if( ads && ads->isAdTypeSupported(AD_TYPE_BANNER) )
    {
        ads->showAds(AD_TYPE_BANNER);
    }
}

void PluginChannel::hideAds()
{
    ProtocolAds* ads = AgentManager::getInstance()->getAdsPlugin();

    if( ads && ads->isAdTypeSupported(AD_TYPE_BANNER) )
    {
        ads->hideAds(AD_TYPE_BANNER);
    }
}



