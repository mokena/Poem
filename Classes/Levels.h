//
// Created by gjj on 2018/6/2.
//

#ifndef PROJ_ANDROID_STUDIO_LEVELS_H
#define PROJ_ANDROID_STUDIO_LEVELS_H

#include "cocos2d.h"
#include <2d/CCLayer.h>
USING_NS_CC;

class Levels : public cocos2d::Layer {
private:
    Sprite* levels[10];

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void initUI();


    // implement the "static create()" method manually
    CREATE_FUNC(Levels);

};


#endif //PROJ_ANDROID_STUDIO_LEVELS_H
