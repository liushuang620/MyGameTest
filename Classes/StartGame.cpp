#include "StartGame.h"
#include "ClassicalMode.h"
#include "InfinityMode.h"

USING_NS_CC;

Scene* StartGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StartGame::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto classicalBtn = MenuItemImage::create(
		"classicalBtn.jpg", 
		"classicalBtn.jpg", 
		CC_CALLBACK_1(StartGame::menuClassicalBtnCallBack, this));
	classicalBtn->setPosition(Vec2(origin.x + visibleSize.width/ 2,
		origin.y + classicalBtn->getContentSize().height+100));

	auto classicalLable = MenuItemFont::create("Classical", CC_CALLBACK_1(StartGame::menuClassicalBtnCallBack, this));
	classicalLable->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + classicalBtn->getContentSize().height + 100));

	auto infinityBtn = MenuItemImage::create(
		"infinityBtn.png",
		"infinityBtn.png",
		CC_CALLBACK_1(StartGame::menuInfinityBtnCallBack, this));

	infinityBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + classicalBtn->getContentSize().height / 2 + 50));
	
	auto infinityLable = MenuItemFont::create("Infinity", CC_CALLBACK_1(StartGame::menuInfinityBtnCallBack, this));
	infinityLable->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + classicalBtn->getContentSize().height / 2 + 50));

	auto startMenu = Menu::create(classicalBtn, classicalLable, infinityBtn, infinityLable, NULL);
	startMenu->setPosition(Point::ZERO);
	this->addChild(startMenu);
	
}

void StartGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void StartGame::menuClassicalBtnCallBack(Ref* pSender) {
	Director::getInstance()->replaceScene(ClassicalMode::createScene());
}

void StartGame::menuInfinityBtnCallBack(Ref* pSender) {
	Director::getInstance()->replaceScene(InfinityMode::createScene());
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif




