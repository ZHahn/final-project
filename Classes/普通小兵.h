#pragma once
#include"cocos2d.h"
enum class SpriteType   //��������  
{
	PLAYER = 1,
	ENEMY = 2
};
enum class SpriteState  //����״̬  
{
	WAITING = 1,

	ATTACK = 2,

	DEAD = 3
};
class MySprite : public cocos2d::Sprite {


public:
	int SpriteType, SpriteState = 1;
	float HP = 100;
	virtual bool init();
	static MySprite* create(int SpriteType);
	~MySprite();
	virtual void attack();
	virtual void hurt();
	//CREATE_FUNC(MySprite);  

};
