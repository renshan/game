#ifndef _Enemy_H_
#define _Enemy_H_
#include "cocos2d.h"
using namespace cocos2d;

struct EnemyInfo{
	int type;
	int lifNum;
	int score;
	int speed;
};
class Enemy : public cocos2d::CCSprite
{
public:
   static Enemy *createEnemy( CCSpriteFrameCache* cache, char* s, int type);
   
   float getSpeed();

   void setType(int Type);
   int getType();

   int lifeNum;
   int score;
   EnemyInfo* enemyInfo;

private:
	int type;
	float speed;
  
};

#endif

