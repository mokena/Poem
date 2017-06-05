#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

Scene* MainGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand(time(0));
	selectedCount = 0;

	// initial the UI layout
	initUI();
    
    return true;
}

// initial the UI layout
void MainGame::initUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// background
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);

	auto *chnStrings = Dictionary::createWithContentsOfFile("poem.xml");

	//// add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(MainGame::menuCloseCallback, this));

	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
	//	origin.y + closeItem->getContentSize().height / 2));

	//// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	// info area
	const char* tstr = ((String*)chnStrings->objectForKey("poem1"))->getCString();
	auto title = Label::create(tstr, "Arial", 40);
	title->setPosition(Vec2(visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));
	addChild(title);

	const char* astr = ((String*)chnStrings->objectForKey("author1"))->getCString();
	auto author = Label::create(astr, "Arial", 25);
	author->setPosition(Vec2(visibleSize.width / 4, title->getPositionY() - title->getContentSize().height - author->getContentSize().height));
	addChild(author);

	const char* dstr = ((String*)chnStrings->objectForKey("dynasty1"))->getCString();
	auto dynasty = Label::create(dstr, "Arial", 25);
	dynasty->setPosition(Vec2(visibleSize.width * 3 / 4, title->getPositionY() - title->getContentSize().height - dynasty->getContentSize().height));
	addChild(dynasty);

	// note area
	const char* notestr = ((String*)chnStrings->objectForKey("need_note"))->getCString();
	noteLbl = Label::create(notestr, "Arial", 30);
	noteLbl->setPosition(Vec2(visibleSize.width / 2, dynasty->getPositionY() - dynasty->getContentSize().height - noteLbl->getContentSize().height));
	addChild(noteLbl);

	// charactors area
	auto charactorsArea = Sprite::create("charactorArea.png");
	charactorsArea->setAnchorPoint(Vec2(0.5, 0.5));
	charactorsArea->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3));
	addChild(charactorsArea);

	// add poem charactors
	const char* cstr = ((String*)chnStrings->objectForKey("level1"))->getCString();
	originalStr = StringUtils::format(cstr);
	Vector<Charactor*> oriCharactors; //charactors in the right order 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBeganCharactor, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	for (int i = 0; i < strlen(cstr); i+=3) {
		char dest[5] = {0};
		char* di = strncpy(dest, cstr+i, 3);
		auto charactor = Charactor::createWithString(di);//Label::create(di, "Arial", 25);
		addChild(charactor);
		oriCharactors.pushBack(charactor);
	}
	Vec2 chaOrigin  = Vec2(charactorsArea->getPositionX() - charactorsArea->getContentSize().width / 2,
		charactorsArea->getPositionY() - charactorsArea->getContentSize().height / 2);
	disturbCharactors(oriCharactors, chaOrigin, charactorsArea->getContentSize());

	// progress bar
	auto progressBg = Sprite::create("progressBg.png");
	progressBg->setPosition(Vec2(visibleSize.width / 2, 
		charactorsArea->getPositionY() + charactorsArea->getContentSize().height / 2 + charactorsArea->getContentSize().height / 10));
	addChild(progressBg);

	auto progressBar = Sprite::create("progressBar.png");
	progressTimer = ProgressTimer::create(progressBar);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setPosition(Vec2(visibleSize.width / 2, progressBg->getPositionY()));
	progressTimer->setMidpoint(Vec2(0, 0));
	progressTimer->setBarChangeRate(Vec2(1, 0));
	progressTimer->setPercentage(0.0f);
	addChild(progressTimer);
}

/*
	touch listener of charactors
*/
bool MainGame::onTouchBeganCharactor(Touch * touch, Event * event)
{
	auto tpos = touch->getLocation();

	for (int i = 0; i < disCharactors.size(); i++) {
		auto charactor = disCharactors.at(i);
		auto area = charactor->getBoundingBox();
		if (area.containsPoint(tpos)) {
			charactor->setPicked();
			bool picked = charactor->getPicked();
			if (!picked) {
				selectedStr.erase(selectedStr.find_first_of(charactor->getString()), 3);
			} else if (selectedCount < 4) {
				selectedStr.append(charactor->getString());
				log("touched character %s", charactor->getString());
				selectedCount++;
			}
			else {
				selectedStr.append(charactor->getString());
				bool right = isCorrectPoem(selectedStr, originalStr);
				log("you picked %d", right);
				selectedCount = 0;
				selectedStr.clear();
			}
			
			break;
		}
	}

	return false;
}

/*
	disturb the original poem charactors
*/
void MainGame::disturbCharactors(Vector<Charactor*> src, Vec2 chaOrigin, Size size)
{
	int count = src.size();
	int perWidth = size.width / column;
	int perHeight = size.height / row;
	int gap = 5;
	for (int i = 0; i < count; i++) {
		int index = CCRANDOM_0_1()*src.size();
		disCharactors.pushBack(src.at(index));
		auto charactor = src.at(index);
		float x = chaOrigin.x + gap + perWidth * (i % column) + perWidth / 2 -  charactor->getContentSize().width / 2;
		float y = chaOrigin.y + gap + perHeight * (i/ column) + perHeight / 2 - charactor->getContentSize().height / 2;
		charactor->setAnchorPoint(Vec2(0, 0));
		charactor->setPosition(Vec2(x, y));
		src.erase(index);
	}
}


void MainGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/*
check the picked charactors is the right poem sentence
*/
bool MainGame::isCorrectPoem(std::string pick, std::string src)
{
	int index = src.find(pick);
	
	if (index == 0 && correctCount == 0){
		correctCount++;
		progressTimer->setPercentage(25.0f);
		return true;
	}
	else if (index == 15 && correctCount == 1) {
		correctCount++;
		progressTimer->setPercentage(50.0f);
		return true;
	}
	else if (index == 30 && correctCount == 2) {
		correctCount++;
		progressTimer->setPercentage(75.0f);
		return true;
	}
	else if (index == 45 && correctCount == 3) {
		progressTimer->setPercentage(100.0f);
		return true;
	}

	return false;
}
