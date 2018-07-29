#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void runMainGame(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Welcome);
};

#endif // __HELLOWORLD_SCENE_H__
