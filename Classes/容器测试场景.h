#pragma once

#include "cocos2d.h"

#define MAX_COUNT 100
USING_NS_CC;


class Setting2 : public cocos2d::Layer
{
	cocos2d::__Array *list;
	cocos2d::__Array *list2;
	cocos2d::__Array *list3;
public:
	static Sprite* target;
	static Vec2 targetLocation;
	static float actionTime(Vec2 currentLocation)
	{
		float x = currentLocation.x - targetLocation.x;
		float y = currentLocation.y - targetLocation.y;
		return 0.01*sqrt(x*x + y * y);
	}
	~Setting2();
	/*static cocos2d::Scene* createScene();*/
	void back(cocos2d::Ref* pSender);
	void onEnter();
	virtual void update(float dt);
	virtual bool init();
	//void back(cocos2d::Ref* pSender);
	void menuCloseCAllback2(cocos2d::Ref* pSender);
	void menuCloseCAllback(cocos2d::Ref* pSender);
	//void onKeypressed(EventKeyboard::KeyCode keyCode, Event *event);
	//void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	// implement the "static create()" method manually
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	//µ¥µã´¥Ãþ
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(Setting2);
};
