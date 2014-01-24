#include "HelloWorldScene.h"
#include "RadioMenu.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	label = LabelTTF::create("Last button: None", "Marker Felt", 32);
	label->setPosition(Point(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - 80));
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label);

	auto starMenuItem = MenuItemImage::create(
		"ButtonStar.png",
		"ButtonStarSel.png", CC_CALLBACK_1(HelloWorld::starMenuCallback, this));


	starMenuItem->setPosition(Point(160, 220));
	auto starMenu = Menu::create(starMenuItem, NULL);
	starMenu->setPosition(Point::ZERO);
	this->addChild(starMenu, 1);

	_plusItem = MenuItemImage::create(
		"ButtonPlus.png",
		"ButtonPlusSel.png");
	_minusItem = MenuItemImage::create(
		"ButtonMinus.png",
		"ButtonMinusSel.png");

	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::plusMinusButtonCallback, this), _plusItem, _minusItem, NULL);

	auto toggleMenu = Menu::create(toggleItem, NULL);
	toggleMenu->setPosition(Point(160, 290));
	this->addChild(toggleMenu, 1);

	auto *menuItem1 = MenuItemImage::create("Button1.png", "Button1Sel.png", this, menu_selector(HelloWorld::but1Callback));
	auto *menuItem2 = MenuItemImage::create("Button2.png", "Button2Sel.png", this, menu_selector(HelloWorld::but2Callback));
	auto *menuItem3 = MenuItemImage::create("Button3.png", "Button3Sel.png", this, menu_selector(HelloWorld::but3Callback));

	auto *radioMenu = RadioMenu::create(menuItem1, menuItem2, menuItem3, NULL);
	radioMenu->setPosition(Point(225, 360));
	radioMenu->alignItemsHorizontally();
	radioMenu->setSelectedItem_(menuItem1);
	menuItem1->selected();	
	this->addChild(radioMenu, 10);

    return true;
}
void HelloWorld::starMenuCallback(Object* pSender)
{
	label->setString("Last button: * ");
}

void HelloWorld::but1Callback(Object* pSender)
{
	label->setString("Last button: button1 ");
}

void HelloWorld::but2Callback(Object* pSender)
{
	label->setString("Last button: button2 ");
}

void HelloWorld::but3Callback(Object* pSender)
{
	label->setString("Last button: button3 ");
}

void HelloWorld::plusMinusButtonCallback(Object* pSender)
{
	MenuItemToggle *toggleItem = (CCMenuItemToggle *)pSender;
	if (toggleItem->selectedItem() == _plusItem){
		label->setString("Visible button: +");
	}
	else if (toggleItem->selectedItem() == _minusItem){
		label->setString("Visible button: -");
	}
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
