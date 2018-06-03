#pragma once
#ifndef _MYACTIONSCENE_H_
#define _MYACTIONSCENE_H_
#include "cocos2d.h"  
#include "HelloWorldScene.h"
USING_NS_CC;

class MyAction : public cocos2d::Layer
{
	bool hiddenFlag;
	cocos2d::Sprite* sprite;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MyAction);

	void goMenu(cocos2d::Ref* pSpender);
	void backMenu(cocos2d::Ref* pSpender);

};

#endif // _MYACTION_SCENE_H_