#pragma once
#include "cocos2d.h"  
USING_NS_CC;
class MyScene : public cocos2d::CCLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuItem1Callback(cocos2d::Ref* pSpender);
	void menuItem2Callback(cocos2d::Ref* pSpender);
	CREATE_FUNC(MyScene);
};