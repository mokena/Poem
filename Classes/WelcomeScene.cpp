#include "WelcomeScene.h"
#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Welcome::createScene()
{
    return Welcome::create();
}

// on "init" you need to initialize your instance
bool Welcome::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "welcome" splash screen"
    auto sprite = Sprite::create("welcome.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    scheduleOnce(schedule_selector(Welcome::runMainGame), 2.0f);
    
    return true;
}

void Welcome::runMainGame(float dt) {
    auto mainScene = MainGame::createScene();
    _director->runWithScene(mainScene);
}