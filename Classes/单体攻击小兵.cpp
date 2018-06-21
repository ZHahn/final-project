#include"cocos2d.h"
#include"单体攻击小兵.h"

USING_NS_CC;

bool MySpriteonebyone::init() {
	if (MySpriteonebyone::SpriteType == 2)
	{
		if (!Sprite::initWithFile("Icon.png")) {
			return false;
		}
	}
	else {
		if (!Sprite::initWithFile("Icon.png")) {
			return false;
		}
	}

	//在这里进行一些精灵类的设置  
	setScale(1.0f, 1.0f);//设置缩放  
	return true;
}
MySpriteonebyone* MySpriteonebyone::create(int x) {
	MySpriteonebyone * sprite = new MySpriteonebyone();
	sprite->SpriteType = x;
	if (x == 2) {
		sprite->setRotation(180);
	}
	if (sprite->init()) {
		sprite->autorelease();//有程序控制sprite的生命周期，  
	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	return sprite;
}
MySpriteonebyone::~MySpriteonebyone() {
	//delete this;
}
void MySpriteonebyone::attack(MySprite* attacked)//攻击普通小兵
{
	attacked->HP -= 35;
	this->stopAllActions();
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	auto moveto = MoveTo::create(0.2, attacked->getPosition());
	auto moveback = MoveTo::create(0.3, Vec2(x, y));
}
void MySpriteonebyone::attack(MySpriteonebyone* attacked)//攻击单击小兵	
{
	attacked->HP -= 35;
	this->stopAllActions();
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	auto moveto = MoveTo::create(0.2, attacked->getPosition());
	auto moveback = MoveTo::create(0.3, Vec2(x, y));
}
void MySpriteonebyone::hurt()//受伤
{
	this->HP -= 20;
	if (this->HP <= 0)
	{
		this->SpriteState = (int)SpriteState2::DEAD;
	}
}
