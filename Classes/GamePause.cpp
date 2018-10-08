#include "GamePause.h"

USING_NS_CC;

Scene* GamePause::createScene(RenderTexture* sqr)

{

	Size visibelSize = Director::getInstance()->getVisibleSize();

	auto scene = Scene::create();
	auto layer = GamePause::create();
	scene->addChild(layer, 1);
	log("####### (%d, %d)", visibelSize.width, visibelSize.height);
	Sprite *bg = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	bg->setPosition(Point(visibelSize.width / 2, visibelSize.height / 2));
	bg->setFlippedY(true);
	bg->setColor(Color3B::GRAY);
	scene->addChild(bg);
	
	return scene;
}

bool GamePause::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size visibelSize = Director::getInstance()->getVisibleSize();

	auto continueBtn = MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(GamePause::menuPauseCallback, this));
	continueBtn->setPosition(Point(visibelSize.width / 2, visibelSize.height /2 ));
	
	auto pauseMenu = Menu::create(continueBtn, NULL);
	pauseMenu->setPosition(Point::ZERO);
	addChild(pauseMenu);

	auto continueLabel = Label::create("Tap to continue", "Arial", 18);
	continueLabel->setPosition(Point(visibelSize.width / 2, visibelSize.height / 2 - 100));
	addChild(continueLabel);
}

void GamePause::menuPauseCallback(Ref* pSender) {
	Director::getInstance()->popScene();
}
