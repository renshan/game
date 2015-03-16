#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void addMonster(float dt);
    void GameUpdate(float);
    // implement the "static create()" method manually
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    
    bool onContactBegin(const PhysicsContact& contact);
    
    
    CREATE_FUNC(HelloWorld);
private:
    std::vector<cocos2d::Sprite*> Monster;
    std::vector<cocos2d::Sprite*> projectile;
    EventListenerTouchOneByOne* touch_listener;
    EventListenerPhysicsContact* contact_listener;
    Sprite* _player;
    int i,j;
};

#endif // __HELLOWORLD_SCENE_H__
