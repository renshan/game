#include "RadioMenu.h"

RadioMenu * RadioMenu::create(MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	RadioMenu *ret = RadioMenu::createWithItems(item, args);

	va_end(args);

	return ret;
}

RadioMenu* RadioMenu::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
	auto ret = new RadioMenu();
	if (ret && ret->initWithArray(arrayOfItems))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

RadioMenu* RadioMenu::createWithItems(MenuItem* item, va_list args)
{
	Vector<MenuItem*> items;
	if (item)
	{
		items.pushBack(item);
		MenuItem *i = va_arg(args, MenuItem*);
		while (i)
		{
			items.pushBack(i);
			i = va_arg(args, MenuItem*);
		}
	}

	return RadioMenu::createWithArray(items);
}

RadioMenu* RadioMenu::createWithItem(MenuItem* item)
{
	return RadioMenu::create(item, nullptr);
}

void RadioMenu::setSelectedItem_(MenuItem *item)
{
	_selectedItem = NULL;
	_selectedItem = item;
}

bool RadioMenu::onTouchBegan(Touch* touch, Event* event)
{
	if (_state != kCCMenuStateWaiting)
		return false;
	CCLOG("onTouchBegan 1111111111111");
	MenuItem *curSelection = this->getItemForTouch(touch);
    if (curSelection) {
        curSelection->selected();
        _curHighlighted = curSelection;
        
        if (_curHighlighted) 
		{
            if (_selectedItem != curSelection) {
                _selectedItem->unselected();
            }
            _state = kCCMenuStateTrackingTouch;
            return true;
        }
    }
    return false;
}

void RadioMenu::onTouchEnded(Touch* touch, Event* event)
{    
	CCMenuItem *curSelection = this->getItemForTouch(touch);
    if (curSelection != _curHighlighted && curSelection != NULL) {
        this->_selectedItem->selected();
        _curHighlighted->unselected();
        _curHighlighted = NULL;
        _state = kCCMenuStateWaiting;
        return;
    }
    
	_selectedItem = _curHighlighted;
    _curHighlighted->activate();
    _curHighlighted = NULL;
    
	_state = kCCMenuStateWaiting;
}

void RadioMenu::onTouchCancelled(Touch* touch, Event* event)
{
	_selectedItem->selected();
    _curHighlighted->unselected();
    _curHighlighted = NULL;
    
	_state = kCCMenuStateWaiting;
}

void RadioMenu::onTouchMoved(Touch* touch, Event* event)
{
	CCMenuItem *curSelection = this->getItemForTouch(touch);
    if (curSelection != _curHighlighted && curSelection != NULL) {
        _curHighlighted->unselected();
        curSelection->selected();
        _curHighlighted = curSelection;
        return;
    }
}

