#include "Enemy.h"

USING_NS_CC;
Enemy * Enemy::createEnemy( CCSpriteFrameCache* cache, char* s, int type)
{
	Enemy *e = new Enemy();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	if (e && e->initWithSpriteFrame(cache->spriteFrameByName(s)))
	{
		e->autorelease();
		if(type == 0){
			e->speed = 8.0f;
			e->lifeNum = 1;
			e->score = 100;
		}
		else if(type == 1){
			e->speed = 6.0f;
			e->lifeNum = 4;
			e->score =200;
		}
		else if(type ==2){
			e->speed = 4.0f;
			e->lifeNum = 8;
			e->score = 1000;
		}
		e->setType( type );
		e->setPosition(ccp(CCRANDOM_0_1()*visibleSize.width, visibleSize.height + e->getContentSize().height));
		return e;
	}

	CC_SAFE_DELETE(e);
	return NULL;
}

void Enemy::setType(int Type){
	type = Type;
}

int Enemy::getType()
{
	return type;
}
float Enemy::getSpeed(){
	
	return speed;
}

