#pragma once
#include"cocos2d.h"
#include<cmath>
#include<cstring>

USING_NS_CC;

typedef enum
{
	kBox1_Tag = 102
	, kBox2_Tag
	, kBox3_Tag
}SpriteTags;

typedef enum
{
	red
	,blue
}teamName;

typedef enum
{
	soldier
	,tank
	,dog
}spriteType;

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

//class mySprite : public cocos2d::Sprite
//{
//public:
//	mySprite(spriteType _type, teamName _tName);	//构造函数(名字，队伍名，生命值，攻击力，移动速度)
//	static mySprite* createWithSpriteTypeAndTeam(spriteType _type, teamName _tName);
//	void setTeam(teamName t);
//	void setHp(float h);
//	void setAttackPoint(float a);
//	void setSpeed(float s);
//	void die();
//	void attack(mySprite &obj);
//	void update(float dt);
//
//
//private:
//	spriteType type;
//	teamName team;
//	float hp;
//	float attackPoint;
//	float speed;
//};
//mySprite* mySprite::createWithSpriteTypeAndTeam(spriteType _type, teamName _tName)
//{
//	mySprite* _sprite = new mySprite(_type, _tName);
//	return _sprite;
//}
//mySprite::mySprite(spriteType _type, teamName _tName)
//{
//	type = _type;
//	team = _tName;
//	/*switch (spriteType) {
//		case soldier;
//
//	}*/
//	scheduleUpdate();
//	
//}
//
//void mySprite::setTeam(teamName t)
//{
//	team = t;
//}
//void mySprite::setHp(float h)
//{
//	hp = h;
//}
//void mySprite::setAttackPoint(float a)
//{
//	attackPoint = a;
//}
//void mySprite::setSpeed(float s)
//{
//	speed = s;
//}
//void mySprite::update(float dt)
//{
//	if (hp <= 0)
//	{
//		die();
//	}
//}
//void mySprite::die()
//{
//	this->unscheduleUpdate();
//	this->removeFromParent();
//}