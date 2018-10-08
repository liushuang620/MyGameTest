#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(NULL));
	visibelSize = Director::getInstance()->getVisibleSize();

	gameLayer = Node::create();
	addChild(gameLayer);

	timerLabel = Label::create();
	timerLabel->setTextColor(Color4B::BLUE);
	timerLabel->setSystemFontSize(48);
	timerLabel->setPosition(visibelSize.width / 2, visibelSize.height - 100);
	//timerLabel->setString("0.00000");
	addChild(timerLabel);


	//addStartLine();
	//addEndLine();
	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {
		log("onTouch");
		auto bs = Block::getBlocks();
		Block *b;

		for (auto it = bs->begin(); it != bs->end(); it++) {
			b = *it;
			if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())) {
				if (b->getColor() == Color3B::BLACK) {
					b->setColor(Color3B::GRAY);
					this->moveDown();
					this->startTimer();
				}
				else if (b->getColor() == Color3B::GREEN) {
					this->moveDown();
					this->stopTimer();
				}
				else {
					MessageBox("GameOver", "失败");
				}
				break;
			}
		}
		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
    return true;
}

void HelloWorld::addStartLine() {
	auto block = Block::createWithArgs(Color3B::YELLOW, Size(visibelSize.width, visibelSize.height / 4), "", 20, Color4B::BLACK);
	gameLayer->addChild(block);
}

void HelloWorld::addEndLine() {
	auto block = Block::createWithArgs(Color3B::GREEN, Size(visibelSize.width, visibelSize.height), "Game Over", 30, Color4B::BLACK);
	block->setLineIndex(4);
	gameLayer->addChild(block);
	//log("-------%d", block->getLineIndex());
}

void HelloWorld::addNormalLine(int lineIndex) {
	Block *b;
	int blackIndex = rand() % 4;
	for (int i = 0; i < 4; i++) {
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibelSize.width/4-1, visibelSize.height/4-1), "", 20, Color4B::BLACK);
		b->setPosition(i * visibelSize.width/4, lineIndex * visibelSize.height/4);
		b->setLineIndex(lineIndex);
		gameLayer->addChild(b);
	}
	linesCount++;
}

void HelloWorld::moveDown() {
	if (linesCount <= 10) {
		addNormalLine(4);
	}
	else if(!showEnd){
		addEndLine();
		showEnd = true;
	}
	auto bs = Block::getBlocks();
	for (auto it = bs->begin(); it != bs->end(); it++) {
		(*it)->moveDown();
	}
}

//setPosition了解一下

void HelloWorld::startGame() {
	linesCount = 0;
	timerRunning = false;
	showEnd = false;
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

void HelloWorld::startTimer() {
	if (!timerRunning) {
		scheduleUpdate();
		startTime = clock();
		timerRunning = true;
	}
}

void HelloWorld::stopTimer() {
	if (timerRunning) {
		unscheduleUpdate();
		timerRunning = false;
	}
}

void HelloWorld::update(float dt) {
	long offset = clock() - startTime;
	timerLabel->setString(StringUtils::format("%g", ((double)offset) / 1000));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
