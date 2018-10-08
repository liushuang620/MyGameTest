#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "cocos2d.h"

USING_NS_CC;

class GamePause : public Layer
{
public:
	static Scene* createScene(RenderTexture *sqr);
	virtual bool init();
	void menuPauseCallback(Ref* pSender);
//	virtual void update(float dt) override;
	CREATE_FUNC(GamePause);
};

#endif

