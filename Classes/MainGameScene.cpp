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
	auto cstr = ((String*)chnStrings->objectForKey("level1"))->getCString();
	std::string poem(cstr);
	for (int i = 0; i < poem.size(); i+=2) {
		std::string c(poem.substr(i, 2));
		TTFConfig config("fonts/Marker Felt", 25);
		auto charactor = Label::createWithTTF(config, c);
		addChild(charactor);
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
