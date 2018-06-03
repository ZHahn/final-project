#include"MyActionScene.h"
#include"cocos2d.h"
USING_NS_CC;

bool MyAction::init()
{
	if (!Layer::init())
	{
		return(false);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	sprite = Sprite::create("Plane.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	auto backMenuItem = MenuItemImage::create("Back-up.png", "Back-down.png",
		CC_CALLBACK_1(MyAction::backMenu, this));
	backMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(120, 100)));

	auto goMenuItem = MenuItemImage::create("Go-up.png", "Go-down.png",
		CC_CALLBACK_1(MyAction::goMenu, this));
	goMenuItem->setPosition(visibleSize.width / 2, 100);

	Menu* mn = Menu::create(backMenuItem, goMenuItem, NULL);

	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	this->hiddenFlag = true;
	return true;
}

void MyAction::backMenu(Ref* pSpender)
{
	auto sc = HelloWorld::createScene();
	auto reScene = TransitionSlideInL::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);

}

void MyAction::goMenu(Ref* pSpender)
{
	log("Tag = %i", this->getTag());
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(CCRANDOM_0_1()* size.width, CCRANDOM_0_1()* size.height);

	//获得Tag，用于判断执行何种动作
	switch (this->getTag()){
	case PLACE_TAG:
		sprite->runAction(Place::create(p));
		break;
	case FLIPX_TAG:
		sprite->runAction(FlipX::create(true));
		break;

	

	}

}






