#include "Charactor.h"

Charactor * Charactor::createWithString(char * text)
{
	Charactor* c = new Charactor();
	if (c && c->init()) {
		c->initWithString(text);
		c->autorelease();
		return c;
	}
	CC_SAFE_DELETE(c);
	return NULL;
	return nullptr;
}

bool Charactor::init()
{
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void Charactor::initWithString(char * text)
{
	//auto size = this->getContentSize();
	word = text;
	label = Label::create(word, "Arial", 25);
	label->setAnchorPoint(Vec2(0, 0));
	//label->setPosition(size / 2);
	addChild(label);
	setContentSize(label->getContentSize());
}

bool Charactor::getPicked()
{
	return picked;
}

void Charactor::setPicked()
{
	picked = !picked;
	if (picked) {
		label->setTextColor(Color4B::BLUE);
	}
	else {
		label->setTextColor(Color4B::WHITE);
	}
}

const std::string & Charactor::getString()
{
	return label->getString();
}
