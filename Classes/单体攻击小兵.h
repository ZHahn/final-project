#pragma once
#include"cocos2d.h"
#include"��ͨС��.h"

enum class SpriteType2   //��������  
{
	PLAYER = 1,
	ENEMY = 2
};
enum class SpriteState2  //����״̬  
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

