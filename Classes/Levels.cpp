//
// Created by gjj on 2018/6/2.
//

#include "Levels.h"

Scene* Levels::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Levels::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Levels::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    initUI();


    return true;
}

void Levels::initUI() {
    const int gap = 5;
    auto bg = Sprite::create("bg.png");
    bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto designSize = Director::getInstance()->getWinSize();

    auto level = Sprite::create("level.png");
    auto levelSize = level->getContentSize();
    level->setPosition(visibleSize.width/2, levelSize.height/2 + gap);
    addChild(level);

}