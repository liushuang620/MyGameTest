#include "InfinityMode.h"
#include "Block.h"

USING_NS_CC;

Scene* InfinityMode::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = InfinityMode::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool InfinityMode::init() {
	if (!Layer::init())
	{
		return false;
	}
	gameLayer = Node::create();
	addChild(gameLayer);
}
