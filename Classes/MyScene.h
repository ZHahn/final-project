#pragma once
#include "cocos2d.h"  
USING_NS_CC;
class MyScene : public cocos2d::CCLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyScene);
};