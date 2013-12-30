#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

bool GameScene:: init(){

	if ( !CCLayer::init() )
	{
		return false;
	}
	initDate();
	preloadMuiscFile();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/game_music.mp3").c_str(), true);

	bgLayer();
	logicLayer();	

	this->setTouchEnabled(true);
	this->scheduleUpdate();

	//pBgLayer->setVisible(false);
	//pLogicLayer->setVisible(false);

	return true;
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(enemyArray);
	CC_SAFE_RELEASE(bulletArray);

	SimpleAudioEngine::sharedEngine()->end();
}

void GameScene::initDate()
{	
	srand(time(0));
	makeEnemyTime1 = 0;
	makeEnemyTime2 = 0;
	makeEnemyTime3 = 0;
	makeBulletTime = 0;
	score = 0;
	isGamePaused = false;
	isGameOver = false;
	
	enemyArray = CCArray::create();
	CC_SAFE_RETAIN(enemyArray);
	bulletArray = CCArray::create();
	CC_SAFE_RETAIN(bulletArray);

	cacheBg = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cacheBg->addSpriteFramesWithFile("bg.plist", "bg.png"); 
	cacheShoot = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cacheShoot->addSpriteFramesWithFile("shoot.plist", "shoot.png"); 
}

void GameScene::preloadMuiscFile()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/game_music.mp3").c_str() );
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/bullet.mp3").c_str() );
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/use_bomb.mp3" ).c_str());
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/enemy0_down.mp3").c_str() );
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/big_spaceship_flying.mp3").c_str() );
}

void GameScene::bgLayer()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//创建背景层
	pBgLayer = CCLayer::create();
	pBgLayer->setContentSize(ccp(CCDirector::sharedDirector()->getVisibleSize().width , CCDirector::sharedDirector()->getVisibleSize().height ));
	pBgLayer->setPosition (ccp(0, 0));
	addChild(pBgLayer);

	//循环背景图片
	pBgSprite1 = CCSprite::createWithSpriteFrame(cacheBg->spriteFrameByName("background.png"));  
	pBgSprite1->setAnchorPoint(ccp(0, 0));
	pBgSprite1->setPosition(ccp(0, 0)); ; 
	pBgLayer->addChild(pBgSprite1, 0);  

	pBgSprite2 = CCSprite::createWithSpriteFrame(cacheBg->spriteFrameByName("background.png"));  
	pBgSprite2->setAnchorPoint(ccp(0, 0));
	pBgSprite2->setPosition(ccp(0, visibleSize.height -1 ));
	pBgLayer->addChild(pBgSprite2, 0); 

	//分数
	pScoreLabel = CCLabelTTF::create("0", "Arial", 40);
	pScoreLabel->setPosition(ccp(60, visibleSize.height - pScoreLabel->getContentSize().height));
	pScoreLabel->setAnchorPoint(ccp(0,0));
	pScoreLabel->setColor(ccc3(0, 0, 0));
	pBgLayer->addChild(pScoreLabel, 1);

	//暂停
	CCSprite *pPauseItem1 = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("game_pause_nor.png"));
	CCSprite *pPauseItem2 = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("game_pause_sel.png"));
	CCMenuItemSprite *pPauseItem = CCMenuItemSprite::create(pPauseItem1, pPauseItem2, this,	menu_selector(GameScene::menuPauseCallback));
	pPauseItem->setPosition(ccp( pPauseItem->getContentSize().width/2 ,	visibleSize.height - pPauseItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create(pPauseItem, NULL);
	pMenu->setPosition(CCPointZero);
	pBgLayer->addChild(pMenu, 1);
}

void GameScene::uILayer()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//创建UI层
	pUiLayer = CCLayerColor::create(ccc4(127, 127, 127, 127));
	pUiLayer->setContentSize(ccp(CCDirector::sharedDirector()->getVisibleSize().width , CCDirector::sharedDirector()->getVisibleSize().height ));
	pUiLayer->setPosition (ccp(0, 0));
	addChild(pUiLayer);

	//菜单各项
	CCSprite* pContinueItem = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("resume_nor.png"));
	CCMenuItemSprite* pContinueBtn = CCMenuItemSprite::create(pContinueItem, pContinueItem, this, menu_selector(GameScene::menuContinueCallback));
	pContinueBtn->setPosition(ccp( visibleSize.width/2, visibleSize.height *2/3));
	pContinueBtn->setScale(2.0f, 2.0f);
	CCSprite* pRestartItem = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("restart_nor.png"));
	CCMenuItemSprite *pRestartBtn = CCMenuItemSprite::create(pRestartItem, pRestartItem, this, menu_selector(GameScene::menuRestartCallback));
	pRestartBtn->setPosition(ccp( visibleSize.width/2, visibleSize.height*5 /9 ));
	pRestartBtn->setScale(2.0f, 2.0f);
	CCSprite* pExitItem = CCSprite::createWithSpriteFrame(cacheShoot->spriteFrameByName("quit_nor.png"));
	CCMenuItemSprite* pExitBtn = CCMenuItemSprite::create(pExitItem, pExitItem, this, menu_selector(GameScene::menuExitCallback));
	pExitBtn->setPosition(ccp(visibleSize.width/2, visibleSize.height *4/9));
	pExitBtn->setScale(2.0f, 2.0f);
	CCMenu *menu = CCMenu::create(pContinueBtn, pRestartBtn, pExitBtn, NULL);
	menu->setPosition(CCPointZero);

	pUiLayer->addChild(menu );
}

void GameScene::logicLayer()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//创建逻辑层
	pLogicLayer = CCLayer::create();
	pLogicLayer->setContentSize(ccp(CCDirector::sharedDirector()->getVisibleSize().width , CCDirector::sharedDirector()->getVisibleSize().height ));
	pLogicLayer->setPosition (ccp(0, 0));
	addChild(pLogicLayer);

	//添加玩家飞机
	playerSprite = this->makePlayer();
	pLogicLayer->addChild(playerSprite ); 
}

void GameScene::update(float t)
{
	this->rollBg();
	this->makeEnemy();
	if (enemyArray->count()>0)
	{
		for (unsigned int i=0;i<enemyArray->count();i++)
		{
			Enemy *enemy=(Enemy*)(enemyArray->objectAtIndex(i));

			if (enemy->getPosition().x>0)
			{
				enemy->setPosition(ccp(enemy->getPosition().x,enemy->getPosition().y-enemy->getSpeed()));
			}else{
				enemyArray->removeObjectAtIndex(i);
				enemy->removeFromParentAndCleanup(true);
			}
			enemyAndPlayerCollision(enemyArray, enemy);
		}
	}

	/*if(((Player*)playerSprite)->GetPressDownState() == true)
	{*/
		this->makeBullet();
		/*bulletSound = SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/bullet.mp3").c_str(), true);
	}
	else{
		SimpleAudioEngine::sharedEngine()->pauseEffect(bulletSound);
	}*/

	if (bulletArray->count()>0)
	{
		for (unsigned int i=0;i<bulletArray->count();i++)
		{
			CCSprite *bullet=(CCSprite*)(bulletArray->objectAtIndex(i));
			if (bullet->getPosition().y < CCDirector::sharedDirector()->getVisibleSize().height )
			{
				bullet->setPosition(ccp(bullet->getPosition().x,bullet->getPosition().y + 10));
			}else{
				bulletArray->removeObjectAtIndex(i);
				bullet->removeFromParentAndCleanup(true);
			}
		}
	}
	this->enemyAndBulletCollision(enemyArray, bulletArray);

	CCString *string=CCString::createWithFormat("%d",score); 
	pScoreLabel->setString(string->getCString());
	if(isGameOver){
		CCUserDefault::sharedUserDefault()->setIntegerForKey("currScore", score);
	}
}

void GameScene::rollBg()
{
	bgheight--;
	pBgSprite1->setPosition(ccp(0, bgheight - CCDirector::sharedDirector()->getVisibleSize().height ));
	pBgSprite2->setPosition(ccp(0, bgheight - 1));
	if(bgheight <= 0)
	{
		bgheight = CCDirector::sharedDirector()->getVisibleSize().height;
	}
}

Player* GameScene::makePlayer(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	Player *playerPlane = Player::creates(cacheShoot, "hero1.png");

	playerPlane->setPosition(ccp(visibleSize.width/2, visibleSize.height/6));  

	return playerPlane;
}

CCSprite* GameScene::createSingleBullet(CCSpriteFrameCache* cache, char* s){
	CCSprite *bulletSprite = new CCSprite();
	if (bulletSprite->initWithSpriteFrame(cache->spriteFrameByName(s)))
	{
		bulletSprite->autorelease();
		return bulletSprite;

	}
	CC_SAFE_DELETE(bulletSprite);
	return NULL;
}

void GameScene::makeBullet()
{
	makeBulletTime++;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	if(makeBulletTime > 15)
	{
		CCSprite *bulletSprite = createSingleBullet(cacheShoot, "bullet1.png");  

		bulletSprite->setPosition(ccp(playerSprite->getPosition().x , playerSprite->getPosition().y + playerSprite->getContentSize().height/2));  
		pLogicLayer->addChild(bulletSprite);
		SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("sound/bullet.MP3").c_str());
		bulletArray->addObject(bulletSprite);
		makeBulletTime = 0;
	}
}

void GameScene::makeEnemy()
{
	makeEnemyTime1++;
	makeEnemyTime2++;
	makeEnemyTime3++;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	Enemy* enemyPlane;
	if(makeEnemyTime1 > 50){
		enemyPlane = Enemy::createEnemy(cacheShoot, "enemy0.png", 0); 
		enemyPlane->setPosition((ccp(CCRANDOM_0_1()*visibleSize.width, visibleSize.height + enemyPlane->getContentSize().height)));
		pLogicLayer->addChild(enemyPlane);
		enemyArray->addObject(enemyPlane);
		makeEnemyTime1 = 0;
	}
	else if(makeEnemyTime2 > 200){
		enemyPlane = Enemy::createEnemy(cacheShoot, "enemy1.png", 1); 
		enemyPlane->setPosition((ccp(CCRANDOM_0_1()*visibleSize.width, visibleSize.height + enemyPlane->getContentSize().height)));
		pLogicLayer->addChild(enemyPlane);
		enemyArray->addObject(enemyPlane);
		makeEnemyTime2 = 0;
	}
	else if(makeEnemyTime3 > 500){
		enemyPlane = Enemy::createEnemy(cacheShoot, "enemy2.png", 2); 
		enemyPlane->setPosition((ccp(CCRANDOM_0_1()*visibleSize.width, visibleSize.height + enemyPlane->getContentSize().height)));
		pLogicLayer->addChild(enemyPlane);
		enemyArray->addObject(enemyPlane);
		makeEnemyTime3 = 0;
		SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename( "sound/big_spaceship_flying.MP3").c_str());
	}
}

bool GameScene::isCollision(CCSprite* sprite1, CCSprite* sprite2){

	if(sprite1 != NULL && sprite2 != NULL){
		CCPoint pos1 = sprite1->getPosition();
		CCPoint pos2 = sprite2->getPosition();
		if (abs(pos1.x-pos2.x)*1.5 <= sprite1->getContentSize().width /2 + sprite2->getContentSize().width/2 && abs(pos1.y-pos2.y)*1.5 <= sprite1->getContentSize().height/2 + sprite2->getContentSize().height /2)
		{
			return true;
		}
	}
	return false;
}

void GameScene::enemyAndPlayerCollision(CCArray* enemyArray, Enemy* enemy)
{
	if(enemy->boundingBox().intersectsRect(playerSprite->boundingBox()))
	{
		playerExplodeAnimation();
		isGameOver = true;
		removeChild(playerSprite);
		enemyArray->removeObject(enemy);
		enemy->removeFromParentAndCleanup(true);
		schedule(schedule_selector(GameScene::gameOver), 1.0f);
	}
}

void GameScene::enemyAndBulletCollision(CCArray* enemyArray1, CCArray* bulletArray1)
{
	if(enemyArray1->count() > 0 && bulletArray1->count()  > 0){
		for( unsigned int i = 0; i < enemyArray1->count(); i++)
		{
			Enemy* enemy = (Enemy*)enemyArray1->objectAtIndex(i);
			for(unsigned int j = 0; j< bulletArray1->count(); j++){
				CCSprite* bullet = (CCSprite*)bulletArray1->objectAtIndex(j);
				if(enemy!=NULL && isCollision (enemy, bullet)){
					enemy->lifeNum--;
					score += enemy->score;
					bulletArray->removeObjectAtIndex(j);
					bullet->removeFromParentAndCleanup(true);
					enemyHitAnimation(enemy);					
				}
			}
			if( enemy->lifeNum == 0 ){
				enemyArray->removeObjectAtIndex(i);
				enemyExplodeAnimation(enemy);
			}
		}
	}
}

void GameScene::playerExplodeAnimation(){
	CCArray *array =CCArray::create();
	for(int i=1; i<5; i++)
	{
		CCString *string = CCString::createWithFormat("hero_blowup_n%i.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());
		array->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.2f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCRepeatForever *ac1 = CCRepeatForever::create(animate);
	playerSprite->runAction(ac1);
	array->removeAllObjects();

	//CC_SAFE_RELEASE(array);
	SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename( "sound/use_bomb.mp3").c_str());
}

void GameScene::enemyHitAnimation(Enemy *enemy){
	CCArray *array=CCArray::create();
	if (enemy->getType() == 1 || enemy->getType() == 2)
    {
		CCString* string1 = CCString::createWithFormat("enemy%i.png", enemy->getType());
		CCSpriteFrame *frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string1->getCString());
		array->addObject(frame1);
		CCString* string2 = CCString::createWithFormat("enemy%i_hit.png", enemy->getType());
		CCSpriteFrame *frame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string2->getCString());
		array->addObject (frame2);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.2f);
		CCAnimate *animate = CCAnimate::create(animation);
		CCRepeatForever *ac1 = CCRepeatForever::create(animate);
		enemy->runAction(ac1);
		array->removeAllObjects();
		//CC_SAFE_RELEASE(array);
    }
}

void GameScene::enemyExplodeAnimation(Enemy* enemy)
{ 
    int animationNum = 0;
	if (enemy->getType() == 0)
    {
        animationNum = 4;
	}else if (enemy->getType() == 1)  
    {
        animationNum = 4;
    }else if (enemy->getType() == 2)  
    {  
        animationNum = 6;
    } 
    enemy->stopAllActions();    
    CCArray *array=CCArray::create();      
    for (int i=1; i<=animationNum; i++)  
    {
		CCString *string=CCString::createWithFormat("enemy%i_down%i.png",enemy->getType(),i);
        CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());
        array->addObject(frame);
    }    
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(array,0.2f);  
    CCAnimate *animate=CCAnimate::create(animation);
    CCSequence *seq=CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameScene::cleanUpEnmey)),NULL);    
    enemy->runAction(seq);  
      
    array->removeAllObjects();
	//CC_SAFE_RELEASE(array);
}

void GameScene::gameOver(float t){
	CCScene *scene = CCScene::create();
	EndedScene *layer = EndedScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.0f, scene));
}

void GameScene::cleanUpEnmey(CCNode *object)
{
	Enemy *enemy=(Enemy *)object;
	enemy->removeFromParentAndCleanup(false);
}

void GameScene::menuPauseCallback(CCObject* pSender)
{
	if(!isGamePaused)
	{
        unscheduleUpdate();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		this->setTouchEnabled(false);
		pLogicLayer->setVisible(false);
		uILayer();
		isGamePaused = true;
    }	
}

void GameScene::menuContinueCallback( CCObject* pSender )
{
	scheduleUpdate();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	isGamePaused = false;
	this->setTouchEnabled(true);
	pLogicLayer->setVisible(true);
	this->removeChild(pUiLayer);
}

void GameScene::menuRestartCallback( CCObject* pSender )
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2f, scene));
}

void GameScene::menuExitCallback( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}


