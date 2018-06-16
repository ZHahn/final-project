#pragma once
#include "cocos2d.h"  
#include"SpritesStorageLayer.h"
#include"容器测试场景.h"
USING_NS_CC;





class MyScene : public cocos2d::CCLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuItem1Callback(cocos2d::Ref* pSpender);
	void menuItem2Callback(cocos2d::Ref* pSpender);

	//单点事件

	

	virtual bool onTouchBegan(cocos2d::Touch* touch, Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, Event* event);

	/*virtual void onEnter();*/
	//virtual void onExit();

	

	CREATE_FUNC(MyScene);
};