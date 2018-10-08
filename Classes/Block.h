#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class Block : public Sprite {
private:
	static Vector<Block*> *blocks;
	int lineIndex;
public:
	static Vector<Block*>* getBlocks();
	static Block* createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);
	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);
	void removeBlock();
	void setLineIndex(int lineIndex);
	int getLineIndex();
	void moveDown();
};

