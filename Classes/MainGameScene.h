#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include "Charactor.h"
USING_NS_CC;

class MainGame : public cocos2d::Layer
{
private:
	float scaleFactor = 1.0f; // ui scale factor
	int row = 4; // charactor rows 
	int column = 5; // charactor columns
	int level = 1; // poem level
	int correctCount = 0; // correct sentences user has selected
	int selectedCount; // the count of user selected charactor
	bool levelCleared = false;
	
	Dictionary* chnStrings; // string from xml
	Vector<Charactor*> disCharactors; // charactors in the disturbed order
	Vector<Charactor*> selectedCharactors; // selected charactors 
	std::string originalStr; // the right ordered poem
	std::string selectedStr; // the user selected sentence
	
	ProgressTimer* progressTimer; // progress of the whole poem been selected
	Label* noteLbl; // hint to user
    Label* levelLbl; // level string
	Label* title; // title of the poem
	Label* author; // author of the poem
	Label* dynasty; // dynasty of the poem
	Sprite* charactorsArea; // charactor area background
	

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void initUI();

	void initLevel();

	bool onTouchBeganCharactor(Touch* touch, Event* event);

	// disturb charactors randomly
	void disturbCharactors(Vector<Charactor*> src, Vec2 origin, Size size);
    
	// all level clear
	void allLevelClear();

	// one level cleaned
	void levelClear();

	// on key back pressed
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	bool isCorrectPoem(std::string pick, std::string src);

    // convert level no. to ancient chinese
    std::string convertNoToChn(int no);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
};

#endif // __MAINGAME_SCENE_H__
