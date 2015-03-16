#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    i = 0;
    j = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    EventListenerPhysicsContact *contact_listener = EventListenerPhysicsContact::create();
    contact_listener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contact_listener, this);
    
    
    touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(false);
    touch_listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
    
    auto body = PhysicsBody::createEdgeBox(visibleSize);
    auto edgeNode = Node::create();
    edgeNode->setPosition(visibleSize.width/2,visibleSize.height/2);
    edgeNode->setPhysicsBody(body);
    
    this->addChild(edgeNode);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    LayerColor* _layer = LayerColor::create(Color4B(255, 255, 255, 255), visibleSize.width,visibleSize.height);
    this->addChild(_layer);
    
    
    _player = Sprite::create("player-hd.png");
    _player->setPosition(visibleSize.width/8,visibleSize.height/2);
    this->addChild(_player);
    
    
    // add a label shows "Hello World"
    // create and initialize a label
    this->schedule(schedule_selector(HelloWorld::addMonster),1);
    //this->schedule(schedule_selector(HelloWorld::GameUpdate));

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::addMonster(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* MonsterExample = Sprite::create("monster-hd.png");
    i = i+1;
    auto OneBody = PhysicsBody::createBox(MonsterExample->getContentSize());
    OneBody->setContactTestBitmask(0x08);
    MonsterExample->setPhysicsBody(OneBody);

    
    MonsterExample->setPosition(
                                visibleSize.width + MonsterExample->getContentSize().width,
                                MonsterExample->getContentSize().height/2+CCRANDOM_0_1()*(visibleSize.height - MonsterExample->getContentSize().height/2));
    Monster.push_back(MonsterExample);
    this->addChild(Monster.back(),i);
    MoveTo* Move = MoveTo::create(3, Vec2(-Monster.back()->getContentSize().width/2,Monster.back()->getPosition().y));
    Monster.back()->runAction(Move);
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    this->removeChild(a->getNode());
    this->removeChild(b->getNode());

    
    
    return true;
}





bool HelloWorld::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Point touchLocation = pTouch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    Sprite* projectileExmaple = Sprite::create("projectile-hd.png");
    j+=1;
    auto OneBody = PhysicsBody::createBox(projectileExmaple->getContentSize());
    OneBody->applyImpulse(Vect(100,500));
    OneBody->setContactTestBitmask(0x04);
    projectileExmaple->setPhysicsBody(OneBody);
    
    projectileExmaple->setPosition(visibleSize.width/8,visibleSize.height/2);
    projectile.push_back(projectileExmaple);
    this->addChild(projectile.back(),j);
    Point offset    = ccpSub(touchLocation, _player->getPosition());
    float   ratio     = offset.y/offset.x;
    int     targetX   = _player->getContentSize().width/2 + visibleSize.width;
    int     targetY   = (targetX*ratio) + _player->getPosition().y;
    Vec2 targetPosition = Vec2(targetX,targetY);

    MoveTo* Move = MoveTo::create(2, targetPosition);
    projectile.back()->runAction(Move);
    return true;
}

void HelloWorld::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

void HelloWorld::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}

void HelloWorld::GameUpdate(float dt)
{
    int i,j;
    for(i = 0;i<projectile.size();i++)
    {
        for(j = 0;j<Monster.size();j++)
        {
            float x = abs(projectile.at(i)->getPosition().x -Monster.at(j)->getPosition().x);
            float y = abs(projectile.at(i)->getPosition().y -Monster.at(j)->getPosition().y);
            float length = sqrt(x*x  + y*y);
            if(length < Monster.at(j)->getContentSize().width/2 + projectile.at(i)->getContentSize().width/2)
            {
                this->removeChild(projectile.at(i));
                this->removeChild(Monster.at(j));
                std::vector<Sprite*>::iterator _Iter1 = projectile.begin() + i;
                projectile.erase(_Iter1);
                
                std::vector<Sprite*>::iterator _Iter2 = Monster.begin() + j;
                Monster.erase(_Iter2);
            }
        }
    }
}
