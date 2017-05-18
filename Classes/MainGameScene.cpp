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

	/////////////////////////////
	// 3. add your codes below...
	// add poem charactors
	auto *chnStrings = Dictionary::createWithContentsOfFile("poem.xml");
	const char* cstr = ((String*)chnStrings->objectForKey("level1"))->getCString();
	originalStr = StringUtils::format(cstr);
	Vector<Sprite*> oriCharactors; //charactors in the right order 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBeganCharactor, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	for (int i = 0; i < strlen(cstr); i+=3) {
		char dest[5] = {0};
		char* di = strncpy(dest, cstr+i, 3);
		auto charactor = Label::create(di, "Arial", 25);
		addChild(charactor);
		oriCharactors.pushBack((Sprite*)charactor);
	}
	disturbCharactors(oriCharactors);
}

/*
	touch listener of charactors
*/
bool MainGame::onTouchBeganCharactor(Touch * touch, Event * event)
{
	auto tpos = touch->getLocation();

	for (int i = 0; i < disCharactors.size(); i++) {
		auto charactor = (Label*)(disCharactors.at(i));
		auto area = charactor->getBoundingBox();
		if (area.containsPoint(tpos)) {
			if (selectedCount < 4) {
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
void MainGame::disturbCharactors(Vector<Sprite*> src)
{
	int count = src.size();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < count; i++) {
		int index = CCRANDOM_0_1()*src.size();
		disCharactors.pushBack(src.at(index));
		auto charactor = src.at(index);
		float x = origin.x + visibleSize.width / column * (i % column);
		float y = origin.y + visibleSize.height / row * (i/ column);
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
	if (index == 0 || index == 15 || index == 30 || index == 45) {
		return true;
	}

	return false;
}
