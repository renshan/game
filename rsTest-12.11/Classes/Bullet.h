#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Bullet:public cocos2d::CCSprite
{
public:
	static Bullet* createBullet(CCSpriteFrameCache* cache, char* s);

};

