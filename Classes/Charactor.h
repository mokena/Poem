#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Charactor : public Sprite {
private:
	char* word;
	bool picked;
	Label* label;
public:

	static Charactor* createWithString(char* text);

	virtual bool init();
	void initWithString(char* text);
	bool getPicked();
	void setPicked();
	const std::string& getString();

	CREATE_FUNC(Charactor);
};