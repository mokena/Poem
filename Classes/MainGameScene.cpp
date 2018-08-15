#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

static const char* CUR_LEVEL="cur_level";

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

	// initialize level
	level = UserDefault::getInstance()->getIntegerForKey(CUR_LEVEL);
	level = (level == 0) ? 1 : level;
	log("init level is %d", level);

	// initial the UI layout
	initUI();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	
    
    return true;
}

// initial the UI layout
void MainGame::initUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto designSize = Director::getInstance()->getWinSize();

	scaleFactor = MIN(visibleSize.width / designSize.width, visibleSize.height / designSize.height);

	levelCleared = false;
	
	// background
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);

	// charactors area
	charactorsArea = Sprite::create("charactorArea.png");
	charactorsArea->setAnchorPoint(Vec2(0.5, 0.5));
	charactorsArea->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
	charactorsArea->setScale(scaleFactor);
	addChild(charactorsArea);

	// info area
	// level
	auto levelBg = Sprite::create("levelHint.png");
	levelBg->setPosition(Vec2(origin.x + levelBg->getContentSize().width/2 + 10,
							  origin.y + visibleSize.height - levelBg->getContentSize().height));
	addChild(levelBg);
    levelLbl = Label::create();
    const std::string levelLblStr = "诗";
    levelLbl->setString(levelLblStr);
    levelLbl->setSystemFontSize(25);
    levelLbl->setPosition(levelBg->getPositionX(), levelBg->getPositionY());
    addChild(levelLbl);


	// title
	chnStrings = Dictionary::createWithContentsOfFile("poem.xml");
	const char* dstr = ((String*)chnStrings->objectForKey("app"))->getCString();
	title = Label::create(dstr, "Arial", 40);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            levelBg->getPositionY() - levelBg->getContentSize().height*4/3 - title->getContentSize().height));
	addChild(title);

	// author
	author = Label::create(dstr, "Arial", 25);
	author->setPosition(Vec2(origin.x + visibleSize.width / 4, title->getPositionY() - title->getContentSize().height - author->getContentSize().height));
	addChild(author);

	// dynasty
	dynasty = Label::create(dstr, "Arial", 25);
	dynasty->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, title->getPositionY() - title->getContentSize().height - dynasty->getContentSize().height));
	addChild(dynasty);

	// note area
	const char* notestr = ((String*)chnStrings->objectForKey("need_note"))->getCString();
	noteLbl = Label::create(notestr, "Arial", 30);
	noteLbl->setPosition(Vec2(origin.x + visibleSize.width / 2, dynasty->getPositionY() - dynasty->getContentSize().height - noteLbl->getContentSize().height));
	addChild(noteLbl);

	// add touch listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBeganCharactor, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	// progress bar
	auto progressBg = Sprite::create("progressBg.png");
	progressBg->setScale(scaleFactor);
	progressBg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		charactorsArea->getPositionY() + charactorsArea->getContentSize().height / 2 + charactorsArea->getContentSize().height / 10));
	addChild(progressBg);

	auto progressBar = Sprite::create("progressBar.png");
	progressTimer = ProgressTimer::create(progressBar);
	progressTimer->setScale(scaleFactor);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setPosition(Vec2(origin.x + visibleSize.width / 2, progressBg->getPositionY()));
	progressTimer->setMidpoint(Vec2(0, 0));
	progressTimer->setBarChangeRate(Vec2(1, 0));
	
	addChild(progressTimer);

	initLevel();
}

void MainGame::initLevel()
{
	correctCount = 0;
	progressTimer->setPercentage(0.0f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	chnStrings = Dictionary::createWithContentsOfFile("poem.xml");

    log("level is %d", level);

	// info area
    // level
    std::string levelNo = convertNoToChn(level);
    const std::string levelNoStr = "诗 " + levelNo;
    levelLbl->setString(levelNoStr);

	// title
	std::string ts = StringUtils::format("poem%d", level);
	const char* titstr = ts.c_str();
	String* tChnStr = (String*)chnStrings->objectForKey(titstr);
	if (tChnStr == NULL) {
		allLevelClear();
		return;
	}
	const char* tstr = tChnStr->getCString();
	
	title->setString(tstr);

	// author
	std::string as = StringUtils::format("author%d", level);
	const char* austr = as.c_str();
	const char* astr = ((String*)chnStrings->objectForKey(austr))->getCString();
	author->setString(astr);

	// dynasty
	std::string ds = StringUtils::format("dynasty%d", level);
	const char* dystr = ds.c_str();
	const char* dstr = ((String*)chnStrings->objectForKey(dystr))->getCString();
	dynasty->setString(dstr);

	// note area

	// charactors
	std::string levels = StringUtils::format("level%d", level);
	const char* levelStr = levels.c_str();
	const char* cstr = ((String*)chnStrings->objectForKey(levelStr))->getCString();
	if (cstr == NULL || cstr == "") {
		// all level clear
		
	}
	originalStr = StringUtils::toString(cstr);
	Vector<Charactor*> oriCharactors; //charactors in the right order 

	for (int i = 0; i < strlen(cstr); i += 3) {
		char dest[5] = { 0 };
		char* di = strncpy(dest, cstr + i, 3);
		auto charactor = Charactor::createWithString(di);//Label::create(di, "Arial", 25);
		addChild(charactor);
		oriCharactors.pushBack(charactor);
	}
	Vec2 chaOrigin = Vec2(charactorsArea->getPositionX() - charactorsArea->getContentSize().width / 2 * scaleFactor,
		charactorsArea->getPositionY() - charactorsArea->getContentSize().height / 2*scaleFactor);
	disturbCharactors(oriCharactors, chaOrigin, charactorsArea->getContentSize()*scaleFactor);
}

/*
	touch listener of charactors
*/
bool MainGame::onTouchBeganCharactor(Touch * touch, Event * event)
{
	if (levelCleared) {
		return false;
	}

	auto tpos = touch->getLocation();

	for (int i = 0; i < disCharactors.size(); i++) {
		auto charactor = disCharactors.at(i);
		auto area = charactor->getBoundingBox();
		if (area.containsPoint(tpos)) {
			charactor->setPicked();
			bool picked = charactor->getPicked();
			if (!picked) { // cancel picked charactor
				selectedStr.erase(selectedStr.find(charactor->getString()), 3);
				selectedCharactors.eraseObject(charactor); // delete from the selected charactors
				selectedCount--;
				
				// for test
				//noteLbl->setString(selectedStr.c_str());

				log("selectedCount -- %d", selectedCount);
			} else if (selectedCount < 4) { 
				// picked one charactor but the number of picked charactors 
				// is smaller than a sentence
				selectedStr.append(charactor->getString());
				selectedCharactors.pushBack(charactor);
				//log("touched character %s", charactor->getString());
				selectedCount++;

				// for test
				//noteLbl->setString(selectedStr.c_str());

				log("selectedCount ++ %d", selectedCount);
			}
			else {
				// picked a whole sentence
				selectedStr.append(charactor->getString());
				selectedCharactors.pushBack(charactor);
				bool right = isCorrectPoem(selectedStr, originalStr);
				selectedCount++;

				// for test
				//noteLbl->setString(selectedStr.c_str());
				
				log("you picked %d", right);
				if (right) {
					auto iterator = selectedCharactors.begin();
					while (iterator != selectedCharactors.end()) {
						((Charactor*)(*iterator))->removeFromParent();
						ParticleExplosion* particleSystem = ParticleExplosion::createWithTotalParticles(50);
						particleSystem->setAnchorPoint(Vec2(0, 0));
						particleSystem->setLife(0.2f);
						auto startColor = Color4F(((Charactor*)(*iterator))->getColor());
						particleSystem->setStartColor(Color4F::GREEN);
						particleSystem->setEndColor(Color4F::GREEN);
						particleSystem->setStartColorVar(Color4F(0, 0, 0, 1.0f));
						particleSystem->setEndColorVar(Color4F(0, 0, 0, 0.1f));
						auto chaPos = ((Charactor*)(*iterator))->getPosition();
						auto chaContentSize = ((Charactor*)(*iterator))->getContentSize();
						particleSystem->setPosition(Vec2(chaPos.x + chaContentSize.width/2, chaPos.y + chaContentSize.height/2));
						particleSystem->setAutoRemoveOnFinish(true);
						particleSystem->setSpeed(40);
						particleSystem->setSpeedVar(20);
						addChild(particleSystem);
						iterator++;
					}
					
					selectedCharactors.clear();
					selectedCount = 0;
					selectedStr.clear();
				}
				
				// if this stage is cleaned
				if (progressTimer->getPercentage() == 100) {
					levelClear();

				}
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
	int gap = 5 * scaleFactor;
	if (disCharactors.size() > 0) {
		disCharactors.clear();
	}
	
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

/*	all level clear */
void MainGame::allLevelClear()
{
	levelCleared = true;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto clearBg = Sprite::create("levelClear.png");
	clearBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(clearBg);
}

/* one level clear */
void MainGame::levelClear()
{
	level++;
	initLevel();

	// write current level to storage
	log("++ level is %d", level);
	UserDefault::getInstance()->setIntegerForKey(CUR_LEVEL, level);
}

void MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
	#endif
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

std::string MainGame::convertNoToChn(int no) {
    std::string chn = "";
    do{
        switch(no%10) {
            case 0:
                chn = "零" + chn;
                break;
            case 1:
                chn = "壹" + chn;
                break;
            case 2:
                chn = "貳" + chn;
                break;
            case 3:
                chn = "叁" + chn;
                break;
            case 4:
                chn = "肆" + chn;
                break;
            case 5:
                chn = "伍" + chn;
                break;
            case 6:
                chn = "陸" + chn;
                break;
            case 7:
                chn = "柒" + chn;
                break;
            case 8:
                chn = "捌" + chn;
                break;
            case 9:
                chn = "玖" + chn;
                break;
            default:
                break;
        }

        no = no / 10;
    }
    while(no>0);
    return chn;
}