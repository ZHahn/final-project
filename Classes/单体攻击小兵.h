#pragma once
#include"cocos2d.h"
#include"普通小兵.h"

enum class SpriteType2   //精灵类型  
{
	PLAYER = 1,
	ENEMY = 2
};
enum class SpriteState2  //精灵状态  
{
	WAITING = 1,

	ATTACK = 2,

	DEAD = 3
};
class MySpriteonebyone : public cocos2d::Sprite {


public:
	int SpriteType, SpriteState = 1;
	float HP = 100;
	virtual bool init();
	static MySpriteonebyone* create(int SpriteType);
	~MySpriteonebyone();
	virtual void attack(MySprite* attacked);
	virtual void attack(MySpriteonebyone* attacked);
	virtual void hurt();
	//CREATE_FUNC(MySprite);  

};

