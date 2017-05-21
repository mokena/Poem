#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainGame : public cocos2d::Layer
{
private:
	int row = 4;
	int column = 5;
	
	Vector<Sprite*> disCharactors; //charactors in the disturbed order
	std::string originalStr;
	std::string selectedStr;
	int selectedCount;
	ProgressTimer* progressTimer;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void initUI();

	bool onTouchBeganCharactor(Touch* touch, Event* event);

	void disturbCharactors(Vector<Sprite*> src, Vec2 origin, Size size);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	bool isCorrectPoem(std::string pick, std::string src);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
};

#endif // __MAINGAME_SCENE_H__
