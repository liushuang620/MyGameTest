#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	Size visibelSize;
	int linesCount;
	bool showEnd = true;
	bool timerRunning;
	long startTime;

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
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
