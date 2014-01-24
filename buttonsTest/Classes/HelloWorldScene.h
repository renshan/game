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
    void menuCloseCallback(Object* pSender);
	void starMenuCallback(Object* pSender);
	void plusMinusButtonCallback(Object* pSender);

	void but1Callback(Object* pSender);
	void but2Callback(Object* pSender);
	void but3Callback(Object* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::LabelTTF* label;
	cocos2d::MenuItem *_plusItem;
	cocos2d::MenuItem *_minusItem;
};

#endif // __HELLOWORLD_SCENE_H__
