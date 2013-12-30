#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	//背景图片
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache->addSpriteFramesWithFile("bg.plist");  
	CCSprite* pBgSprite = CCSprite::createWithSpriteFrameName("background.png");  
	pBgSprite->setAnchorPoint(ccp(0, 0));
	pBgSprite->setPosition(ccp(origin.x, origin.y)); 
	this->addChild(pBgSprite, 0);
	
	//游戏名
	CCSprite* pTitleSprite = CCSprite::createWithSpriteFrameName("name.png");  
	pTitleSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height*2/3 + origin.y)); 
	this->addChild(pTitleSprite); 

	//开始游戏按钮
	CCMenuItemFont *startBtn = CCMenuItemFont::create("START GAME", this, menu_selector(HelloWorld::startClicked));
	startBtn->setPosition(ccp( visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
	startBtn->setFontSizeObj(60);
	startBtn->setFontNameObj("Arial");
	CCMenu *menu = CCMenu::create(startBtn, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu ,1);

	

	schedule(schedule_selector(HelloWorld::startGame), 6.0f);

    return true;
}

void HelloWorld::startGame(float t)
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.2f, scene));
}

void HelloWorld::startClicked(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.2f, scene));
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
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
