#include "Bullet.h"


Bullet* Bullet::createBullet(CCSpriteFrameCache* cache, char* s){

	Bullet *bullet = new Bullet();
	if (bullet->initWithSpriteFrame(cache->spriteFrameByName(s)))
	{
		bullet->autorelease();
		return bullet;

	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}


