//
// Created by gjj on 2018/6/2.
//

#ifndef PROJ_ANDROID_STUDIO_LEVELS_H
#define PROJ_ANDROID_STUDIO_LEVELS_H


#include <2d/CCLayer.h>

class Levels : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    virtual bool init();


    // implement the "static create()" method manually
    CREATE_FUNC(Levels);

};


#endif //PROJ_ANDROID_STUDIO_LEVELS_H
