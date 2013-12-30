#include "Player.h"


Player* Player::creates( CCSpriteFrameCache* cache, char* s )
{
	Player* player = new Player();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	if(player && player->initWithSpriteFrame(cache->spriteFrameByName(s))){
		player->autorelease();
		player->setPosition(ccp(visibleSize.width/2 , visibleSize.height/6 ));
		return player;
	}
	player->isPressDown = false;
	player->isMove = false;
	CC_SAFE_DELETE(player);

	return NULL;
}

void Player::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this ,0, true);
	CCSprite::onEnter();
}

void Player::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool Player::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint beginPos = pTouch->getLocation ();
	CCPoint playerPos = this->getPosition ();
	
	if(beginPos.x > (playerPos.x-this->getContentSize().width /2) 
		&& beginPos.x < (playerPos.x + this->getContentSize().width/2 )
		&& beginPos.y > ( playerPos.y -this->getContentSize().height/2)  
		&& beginPos.y < (playerPos.y + this->getContentSize().height/2))
	{
		isPressDown = true;
		isMove = true;
		this->setPosition(beginPos);
	}
	return true;
}

void Player::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{ 
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint movePos = pTouch->getLocation();
	if(isMove == true && movePos.x > this->getContentSize().width /2 && movePos.x < size.width - this->getContentSize ().width /2
		&& movePos.y >this->getContentSize ().height /2 &&movePos.y < size.height - this->getContentSize ().height /2){
		this->setPosition(movePos);
	}
	
}

void Player::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if(isPressDown){
		isMove = false;
		isPressDown = false;
	}
}

bool Player::GetPressDownState()
{
	return isPressDown;
}


