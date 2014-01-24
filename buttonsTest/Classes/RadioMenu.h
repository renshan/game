#ifndef _Hello_RadioMenu_
#define _Hello_RadioMenu_

#include "cocos2d.h"

USING_NS_CC;

class RadioMenu : public cocos2d::Menu
{
public:
	
	static RadioMenu* create(cocos2d::MenuItem* item, ...);
	static RadioMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);
	static RadioMenu* createWithItem(MenuItem* item);
	static RadioMenu* createWithItems(MenuItem *firstItem, va_list args);
 

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchCancelled(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

    void setSelectedItem_(cocos2d::MenuItem *item);

	cocos2d::MenuItem *_curHighlighted;

};


#endif
