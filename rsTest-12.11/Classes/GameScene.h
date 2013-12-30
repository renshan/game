#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Player.h"
#include "EndedScene.h"

class GameScene: public cocos2d::CCLayer
{
public:
	virtual bool init();
	~GameScene();

	//各回调函数
	void menuPauseCallback(CCObject* pSender);
	void menuContinueCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);
	void menuExitCallback(CCObject* pSender);
	void gameOver(float t);
	void cleanUpEnmey(CCNode *object);

	CREATE_FUNC(GameScene);

private:
	CCLayerColor *pUiLayer;	//UI层
	CCLayer* pBgLayer;		//背景层
	CCLayer* pLogicLayer;	//游戏逻辑层（子弹、飞机、敌机都在这层）

	cocos2d::CCSprite* playerSprite;	 
	cocos2d::CCSprite* pBgSprite1;
	cocos2d::CCSprite* pBgSprite2;

	CCSpriteFrameCache* cacheBg;
	CCSpriteFrameCache* cacheShoot;
	int makeBulletTime;		//子弹生成间隔时间
	int makeEnemyTime1, makeEnemyTime2, makeEnemyTime3;//三种敌机生成间隔时间
	int bgheight;			//背景贴图的高
	int score;
	CCLabelTTF* pScoreLabel;
	cocos2d::CCArray* enemyArray;
	cocos2d::CCArray* bulletArray;
	
	bool isGamePaused;
	bool isGameOver;

	unsigned int bulletSound;


	void initDate();
	void preloadMuiscFile();

	//各层
	void uILayer();
	void bgLayer();
	void logicLayer();

	//创建各对象
	CCSprite* createSingleBullet(CCSpriteFrameCache* cache, char* s);
	Player* makePlayer();
	void makeBullet();
	void makeEnemy();

	//碰撞检测
	bool isCollision(CCSprite* sprite1, CCSprite* sprite2);
	void enemyAndPlayerCollision(CCArray* enemyArray, Enemy* enemy);
	void enemyAndBulletCollision(CCArray* enemyArray1, CCArray* bulletArray1);

	//各动画
	void playerExplodeAnimation();
	void enemyHitAnimation(Enemy *enemy);
	void enemyExplodeAnimation(Enemy* enemy);
	
	//背景循环
	void rollBg();

	//更新
	void update(float t);
};

#endif