#pragma once

#include"cocos2d.h"
#include"���幥��С��.h"

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

	//���������һЩ�����������  
	setScale(1.0f, 1.0f);//��������  
	return true;
}
MySpriteonebyone* MySpriteonebyone::create(int x) {
	MySpriteonebyone * sprite = new MySpriteonebyone();
	sprite->SpriteType = x;
	if (x == 2) {
		sprite->setRotation(180);
	}
	if (sprite->init()) {
		sprite->autorelease();//�г������sprite���������ڣ�  
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
void MySpriteonebyone::attack(MySprite* attacked)//������ͨС��
{
	attacked->HP -= 35;
	this->stopAllActions();
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	Sprite *sprite = Sprite::create("pump_flare_02.png");
	this->addChild(sprite, 10); sprite->setPosition(0, 0);
	sprite->setScale(0.5, 0.5f);

	auto moveto = MoveTo::create(0.5, Vec2(attacked->getPosition().x - x, attacked->getPosition().y - y));
	auto fadeout = FadeOut::create(0.1);
	auto seq = Sequence::create(moveto, fadeout, nullptr);
	sprite->runAction(seq);
	/*auto moveto = MoveTo::create(0.2, Vec2(attacked->getPosition()));
	auto moveback= MoveTo::create(0.3,Vec2(x,y));
	auto seq = Sequence::create(moveto, moveback, nullptr);
	this->runAction(seq);*/
}
void MySpriteonebyone::attack(MySpriteonebyone* attacked)//��������С��	
{
	attacked->HP -= 35;
	this->stopAllActions();
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	Sprite *sprite = Sprite::create("pump_flare_02.png");
	this->addChild(sprite, 10); sprite->setPosition(0, 0);
	sprite->setScale(0.5, 0.5f);

	auto moveto = MoveTo::create(0.5, Vec2(attacked->getPosition().x - x, attacked->getPosition().y - y));
	auto fadeout = FadeOut::create(0.1);
	auto seq = Sequence::create(moveto, fadeout, nullptr);
	sprite->runAction(seq);
	/*auto moveto = MoveTo::create(0.2, Vec2(attacked->getPosition()));
	auto moveback = MoveTo::create(0.3, Vec2(x, y));
	auto seq = Sequence::create(moveto, moveback, nullptr);
	this->runAction(seq);*/
}


void MySpriteonebyone::hurt()//����
{
	this->HP -= 20;
	if (this->HP <= 0)
	{
		this->SpriteState = (int)SpriteState2::DEAD;
	}
}
