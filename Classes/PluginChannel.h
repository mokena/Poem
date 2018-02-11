//
//  PluginChannel.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#ifndef __PLUGIN_CHANNEL_H__
#define __PLUGIN_CHANNEL_H__

#include "AgentManager.h"
#include "string.h"

using namespace anysdk::framework;
using namespace std;

class PluginChannel:public AdsListener
{
public:
    static PluginChannel* _pInstance;

    static PluginChannel* getInstance();

    PluginChannel();
    ~PluginChannel();

    void loadPlugins();

    void unloadPlugins();

    virtual void onAdsResult(AdsResultCode code, const char* msg);

    void preloadAds();

    void showAds();

    void hideAds();
};

#endif
