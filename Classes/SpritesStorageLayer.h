#pragma once
#include"cocos2d.h"
#include<math.h>
USING_NS_CC;

typedef enum
{
	kBox1_Tag = 102
	, kBox2_Tag
	, kBox3_Tag
}SpriteTags;

class SpritesStorageLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	static Sprite* target;
	static Vec2 targetLocation;
	static float actionTime(Vec2 currentLocation)
	{
		float x = currentLocation.x - targetLocation.x;
		float y = currentLocation.y - targetLocation.y;
		return 0.01*sqrt(x*x+y*y);
	}


	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(SpritesStorageLayer);



};
