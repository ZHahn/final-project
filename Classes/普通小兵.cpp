#include"cocos2d.h"
#include"普通小兵.h"

USING_NS_CC;

bool MySprite::init() {
	if (MySprite::SpriteType == 2)
	{
		if (!Sprite::initWithFile("SpinningPeas.png")) {
			return false;
		}
	}
	else {
		if (!Sprite::initWithFile("Pea.png")) {
			return false;
		}
	}

	//在这里进行一些精灵类的设置  
	setScale(1.0f, 1.0f);//设置缩放  
	return true;
}


MySprite* MySprite::create(int x) {
	MySprite * sprite = new MySprite();
	sprite->SpriteType = x;
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
MySprite::~MySprite() {
	//delete this;
}
void MySprite::attack()//攻击
{
	if (this->SpriteState != (int)SpriteState::ATTACK)
	{
		//this->SpriteState = (int)SpriteState::ATTACK;
		this->stopAllActions();
		auto scaleTo1 = ScaleTo::create(0.2f, 1.5f);
		auto scaleTo2 = ScaleTo::create(0.3f, 1.0f);
		auto seq = Sequence::create(scaleTo1, scaleTo2, nullptr);
		this->runAction(seq);
		/*auto rotateTo = RotateTo::create(2.0f, 40.0f);
		this->runAction(rotateTo);
		/*auto *atta = Sequence::create(attackAction,
		CallFunc::create(CC_CALLBACK_0(GameSprite::idle, this)), NULL);
		this->runAction(atta);*/
	}
}
void MySprite::hurt()//受伤
{
	this->HP -= 35;
	if (this->HP <= 0)
	{
		this->SpriteState = (int)SpriteState::DEAD;
	}
}
