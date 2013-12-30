#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class Player:public CCSprite, public CCTouchDelegate
{
public:
	static Player* creates( CCSpriteFrameCache* cache, char* s );
	bool GetPressDownState();

private:
	bool isPressDown;
	bool isMove;
private:
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);	
};

