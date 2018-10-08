#include "StartGameScene.h"

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

	visibelSize = Director::getInstance()->getVisibleSize();
	//////查一下怎么创建按钮

	auto classicalBtn = MenuItemImage::create("classicalBtn.png", "classicalBtn.png", CC_CALLBACK_1(StartGame::menuClassicalBtnCallBack, this));
	classicalBtn->setPosition(Point(visibelSize.width / 2 - 100, visibelSize.height / 4));


	auto startMenu = Menu::create(classicalBtn, NULL);
	startMenu->setPosition(Point::ZERO);
	this->addChild(startMenu, 1);

}

void StartGame::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void StartGame::menuClassicalBtnCallBack(Ref* pSender) {

}

void StartGame::menuInfinityBtnCallBack(Ref* pSender) {

}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif