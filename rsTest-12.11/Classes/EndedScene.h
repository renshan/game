#ifndef __ENDED_SCENE_H__
#define __ENDED_SCENE_H__
#include "cocos2d.h"

class EndedScene : public cocos2d::CCLayer
{
public:
	virtual bool init();

	CREATE_FUNC(EndedScene);
	void menuRestartCallback(CCObject* pSender);
	void initScene();
	void addScoreLabel();

	int highestScore ;
};

#endif