#ifndef __CLASSICALMODE_H__
#define __CLASSICALMODE_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

class ClassicalMode : public cocos2d::Layer
{
private:
	Size visibelSize;
	int linesCount;
	bool showEnd = true;
	bool timerRunning;
	long startTime;
	bool isDone;
	bool isPause;
	long pauseClock;

	Label *timerLabel;
	Node *gameLayer;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void addStartLine();

	void addEndLine();

	void addNormalLine(int lineIndex);

	void startGame();

	void moveDown();

	void startTimer();
	void stopTimer();
	virtual void update(float dt);

	// a selector callback
	void menuPauseCallBack(cocos2d::Ref* pSender);
	virtual void onEnterTransitionDidFinish() override;
		
	// implement the "static create()" method manually
	CREATE_FUNC(ClassicalMode);
};

#endif // __HELLOWORLD_SCENE_H__
