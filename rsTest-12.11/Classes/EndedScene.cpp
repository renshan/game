#include "EndedScene.h"
#include "GameScene.h"
using namespace cocos2d;

bool EndedScene::init()
{
	if( !CCLayer::init()){

		return false;
	}
	highestScore = 0;
	initScene();
	addScoreLabel();
	
	return true;
}

void EndedScene::initScene()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache->addSpriteFramesWithFile("bg.plist", "bg.png");
	CCSpriteFrameCache* cacheShoot = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cacheShoot->addSpriteFramesWithFile("shoot.plist", "shoot.png");  

	//背景
	CCSprite* pBgSprite = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("gameover.png"));  
	pBgSprite->setAnchorPoint(ccp(0, 0));
	pBgSprite->setPosition(ccp(0, 0)); 
	this->addChild(pBgSprite, 0);	

	//重新开始菜单项
	CCSprite *pRestartItem = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("restart_nor.png"));
	CCMenuItemSprite *pRestartBtn = CCMenuItemSprite::create(
		pRestartItem,
		pRestartItem,
		this,
		menu_selector(EndedScene::menuRestartCallback));

	pRestartBtn->setPosition(ccp( visibleSize.width -100, 760 ));
	CCMenu *menu = CCMenu::create(pRestartBtn, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu ,1);
}

void EndedScene::addScoreLabel()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	//当前分数
	CCLabelTTF* currScoreLabel = CCLabelTTF::create("0", "Arial", 50);
	currScoreLabel->setPosition(ccp(visibleSize.width/2, visibleSize.height/4));

	int currScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("currScore");
	CCString *currScoreString=CCString::createWithFormat("%d",currScore); 

	currScoreLabel->setString(currScoreString->getCString());
	this->addChild(currScoreLabel);
	
	//历史最高分数
	CCLabelTTF* highestScoreLabel = CCLabelTTF::create("0", "Arial", 50);
	highestScoreLabel->setPosition(ccp(visibleSize.width /2, visibleSize.height*2/3));
	//CCUserDefault::sharedUserDefault()->setIntegerForKey("highestScore", highestScore);
	highestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highestScore");
	if(currScore >= highestScore )
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("highestScore", currScore);
		highestScoreLabel->setString(currScoreString->getCString());		
	}
	else if(currScore < highestScore)
	{
		CCString *highestScoreString=CCString::createWithFormat("%d", highestScore); 
		highestScoreLabel->setString(highestScoreString->getCString());
	}
	CCUserDefault::sharedUserDefault()->flush();
	this->addChild (highestScoreLabel);
	
}

void EndedScene::menuRestartCallback(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}