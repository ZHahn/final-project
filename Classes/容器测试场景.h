#pragma once

#include "cocos2d.h"
#include"MyScene.h"
#include"普通小兵.h"
#include"单体攻击小兵.h"
#include"math/CCMath.h"
#include<vector>


#define MAX_COUNT 100
USING_NS_CC;
extern cocos2d::Layer* map;



class Setting2 : public cocos2d::Layer
{
	
public:
	static cocos2d::__Array *list;
	cocos2d::__Array *list2;
	cocos2d::__Array *list3;
	static MySpriteonebyone* target;
	static Vec2 targetLocation;
	static float actionTime(Vec2 currentLocation, Sprite* obj)	//输入点击位置和选中的精灵
	{
		float x = currentLocation.x - obj->getPosition().x;
		float y = currentLocation.y - obj->getPosition().y;
		return 0.01*sqrt(x*x + y * y);
	}
	//矩形复选框数据
	static float max_x;
	static float max_y;
	static float min_x;
	static float min_y;
	static std::vector<MySpriteonebyone*> targetList;
	static void groupSelectBegin(float x ,float y);
	static bool groupSelectBegin2(float x, float y);
	static void groupSelectMove(Vec2 location);
	static void drawRect(float x, float y);
	static void clearRect();
	static Layer* layer;
	static DrawNode* draw;

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
	void getBloodbar(MySprite *guaisprite, float a);
	void getBloodbar(cocos2d::Sprite *guaisprite, float a);


	// implement the "static create()" method manually
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	//单点触摸
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(Setting2);
};
