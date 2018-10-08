#ifndef _INFINITYMODE_H_
#define _INFINITYMODE_H_

#include "cocos2d.h"

USING_NS_CC;

class InfinityMode : public Layer {
private:
	Node *gameLayer;
public:
	static Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(InfinityMode);
};


#endif
