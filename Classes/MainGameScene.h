﻿#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainGame : public cocos2d::Layer
{
private:
	int row = 4;
	int column = 5;
	Vector<Sprite*> oriCharactors; //charactors in the right order 
	Vector<Sprite*> disCharactors; //charactors in the disturbed order

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void initUI();

	void disturbCharactors();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
};

#endif // __MAINGAME_SCENE_H__