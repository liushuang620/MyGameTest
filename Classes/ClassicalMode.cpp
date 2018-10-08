#include "ClassicalMode.h"
#include "StartGame.h"
#include "GamePause.h"

USING_NS_CC;

Scene* ClassicalMode::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ClassicalMode::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ClassicalMode::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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
	addChild(timerLabel);

	auto pauseBtn = MenuItemImage::create("CloseNormal.png", "CloseSelect.png",CC_CALLBACK_1(ClassicalMode::menuPauseCallBack, this));
	pauseBtn->setPosition(Point(visibelSize.width - 50, visibelSize.height - 50));

	auto pauseMenu = Menu::create(pauseBtn, NULL);
	pauseMenu->setPosition(Point::ZERO);
	addChild(pauseMenu);

	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {
		log("onTouch");
		auto bs = Block::getBlocks();
		Block *b;

		if (isDone) {
			Director::getInstance()->replaceScene(StartGame::createScene());
			log("%d", bs->size());
			bs->clear();
		}

		for (auto it = bs->begin(); it != bs->end(); it++) {
			b = *it;
			if (b->getLineIndex() == 0 && b->getBoundingBox().containsPoint(t->getLocation())) {
				if (b->getColor() == Color3B::BLACK) {
					b->setColor(Color3B::GRAY);
					moveDown();
					startTimer();
				}
				else if (b->getColor() == Color3B::GREEN) {
					stopTimer();
				}
				else {
					MessageBox("GameOver", "失败");
					Director::getInstance()->replaceScene(StartGame::createScene());
					bs->clear();
				}
				break;
			}
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void ClassicalMode::addStartLine() {
	auto block = Block::createWithArgs(Color3B::YELLOW, Size(visibelSize.width, visibelSize.height / 4), "", 20, Color4B::BLACK);
	gameLayer->addChild(block);
}

void ClassicalMode::addEndLine() {
	auto block = Block::createWithArgs(Color3B::GREEN, Size(visibelSize.width, visibelSize.height), "Game Over", 30, Color4B::BLACK);
	block->setLineIndex(4);
	gameLayer->addChild(block);
	//log("-------%d", block->getLineIndex());
}

void ClassicalMode::addNormalLine(int lineIndex) {
	Block *b;
	int blackIndex = rand() % 4;
	for (int i = 0; i < 4; i++) {
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibelSize.width / 4 - 1, visibelSize.height / 4 - 1), "", 20, Color4B::BLACK);
		b->setPosition(i * visibelSize.width / 4, lineIndex * visibelSize.height / 4);
		b->setLineIndex(lineIndex);
		gameLayer->addChild(b);
	}
	linesCount++;
}

void ClassicalMode::moveDown() {
	if (linesCount <= 10) {
		addNormalLine(4);
	}
	else if (!showEnd) {
		addEndLine();
		showEnd = true;
	}
	auto bs = Block::getBlocks();
	for (auto it = bs->begin(); it != bs->end(); it++) {
		(*it)->moveDown();
	}
}

//setPosition了解一下

void ClassicalMode::startGame() {
	linesCount = 0;
	timerRunning = false;
	showEnd = false;
	isDone = false;
	isPause = false;
	pauseClock = 0;
	
	addNormalLine(0);
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

void ClassicalMode::startTimer() {
	if (!timerRunning) {
		scheduleUpdate();
		startTime = clock();
		timerRunning = true;
	}
}

void ClassicalMode::stopTimer() {
	if (timerRunning) {
		unscheduleUpdate();
		timerRunning = false;
		isDone = true;
	}
}

void ClassicalMode::update(float dt) {
	long offset = clock() - startTime + pauseClock;
	//timerLabel->setString(StringUtils::format("%g", ((double)offset) / 1000));   
	timerLabel->setString(StringUtils::format("%.3f", ((double)offset) / 1000));
}

void ClassicalMode::onEnterTransitionDidFinish() {
	if (isPause) {
		startTime = clock();
		scheduleUpdate();
		isPause = false;
	}
}

void ClassicalMode::menuPauseCallBack(Ref* pSender) {
	unscheduleUpdate();
	isPause = true;
	startTime -= pauseClock;
	pauseClock = clock() - startTime;
	auto sqr = RenderTexture::create(visibelSize.width, visibelSize.height);
	sqr->begin();
	this->getParent()->visit();
	sqr->end();
	Director::getInstance()->pushScene(GamePause::createScene(sqr));
}
