#include"容器测试场景.h"
#include "SimpleAudioEngine.h"
#include "base/CCEventKeyboard.h"
#include<string>
#include<sstream>
using namespace std;

USING_NS_CC;bool have=0;
long money = 0;
int spritenumber = 0;
string s="0";
int times = 0;
int orgin_tag = 100;	//精灵tag的初始值，每生成一个新精灵就+1
Sprite* Setting2::target = NULL;
Vec2 Setting2::targetLocation(0, 0);



bool Setting2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg, 0);

	auto closeItem1 = MenuItemImage::create("b1.png", "b2.png",
		CC_CALLBACK_1(Setting2::back, this));
	auto menu1 = Menu::create(closeItem1, NULL);
	menu1->setPosition(Vec2(50, 50));
	this->addChild(menu1, 20);

	auto label1 = Label::createWithTTF("Money:"+s, "fonts/Marker Felt.ttf", 36);
	label1->setPosition(Vec2(150,700));
	label1->enableOutline(Color4B::BLACK, 10);
	label1->enableGlow(Color4B::YELLOW);
	addChild(label1,20,123);

	auto goItem = MenuItemImage::create("r1.png", "r2.png", CC_CALLBACK_1(Setting2::menuCloseCAllback, this));
	auto menu = Menu::create(goItem, NULL);
	menu->setPosition(Vec2(1000, 380));
	this->addChild(menu, 20);

	auto goItem1 = MenuItemImage::create("r1.png", "r2.png", CC_CALLBACK_1(Setting2::menuCloseCAllback2, this));
	auto menu2 = Menu::create(goItem1, NULL);
	menu2->setPosition(Vec2(935, 380));
	this->addChild(menu2, 20);

	auto goItem2 = MenuItemImage::create("r1.png", "r2.png", CC_CALLBACK_1(Setting2::menuCloseCAllback2, this));
	auto menu3 = Menu::create(goItem2, NULL);
	menu3->setPosition(Vec2(935, 320));
	this->addChild(menu3, 20);

	auto lan = Sprite::create("lan.jpg");
	lan->setAnchorPoint(Vec2::ZERO);
	lan->setPosition(Vec2(900, 0));
	lan->runAction(ScaleTo::create(0.02f, 2.0f));
	this->addChild(lan, 19);

	this->list = __Array::createWithCapacity(MAX_COUNT);
	this->list->retain();

	this->list2 = __Array::createWithCapacity(MAX_COUNT);
	this->list2->retain();

	this->list3 = __Array::createWithCapacity(MAX_COUNT);
	this->list3->retain();	
	
	auto enemyhouse= Sprite::create("powered.png");
	this->list2->addObject(enemyhouse);
	enemyhouse->setPosition(Vec2(3600, 1600));
	this->addChild(enemyhouse, 11,666);

	auto background = Sprite::create("1.jpg");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2(0, 0));
	background->runAction(ScaleTo::create(0.02f, 3.0f));
	this->addChild(background, 2,1);

	//for (int i = 0; i < MAX_COUNT; ++i) {
		//Sprite* sprite = Sprite::create("pu_green_ball.png");                                   
		//	this->list->addObject(sprite);                                         
	//}
	this->scheduleUpdate();
	return true;
}
//Scene* Setting2::createScene()
//{
//	auto scene = Scene::create();
//	auto layer = Setting2::create();
//	scene->addChild(layer);
//
//	return scene;
//}
void Setting2::back(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Setting2::menuCloseCAllback(Ref* pSender)
{
	if (have == 1&&money-50>=0)
	{
		money -= 50;
		auto house = getChildByTag(5);
		Sprite* sprite = Sprite::create("Icon.png");	//创建可控制精灵
		this->list->addObject(sprite);
		log("list->count() = %d", this->list->count());
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Ref* obj = nullptr;
		spritenumber++;
		int i = 0;

		CCARRAY_FOREACH(this->list, obj) {	//将精灵添加至随机位置
			i++;
			if (i >= spritenumber)
			{
				Sprite* sprite = (Sprite*)obj;
				sprite->setPosition(house->getPosition());
				int x = CCRANDOM_0_1() * visibleSize.width*0.6- visibleSize.width*0.3;
				int y = CCRANDOM_0_1() * visibleSize.height*0.6- visibleSize.height*0.3;
				auto moveto = MoveBy::create(0.2, Vec2(x, y));
				sprite->runAction(moveto);
				//this->removeChild(sprite);
				this->addChild(sprite, 10, orgin_tag);	//tag从100开始生成
				//单点触摸监听器,此处代码在生成精灵的同时创建并注册监听器，我觉得可能浪费了资源(重复创建监听器),
				//但是如果在onEnter函数中创建监听器，则在此函数中无法识别，暂且如此
				auto listener2 = EventListenerTouchOneByOne::create();

				listener2->setSwallowTouches(true);
				listener2->onTouchBegan = CC_CALLBACK_2(Setting2::touchBegan, this);
				listener2->onTouchMoved = CC_CALLBACK_2(Setting2::touchMoved, this);
				listener2->onTouchEnded = CC_CALLBACK_2(Setting2::touchEnded, this);

				//注册监听器
				EventDispatcher* mouse_eventDispatcher = Director::getInstance()->getEventDispatcher();
				mouse_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2->clone(), getChildByTag(orgin_tag));
				orgin_tag++;
			}
		}
	}
}
void Setting2::menuCloseCAllback2(Ref* pSender)
{
	if (have == 0) {
		Sprite* sprite = Sprite::create("powered.png");
		this->list2->addObject(sprite);
		//log("list->count() = %d", this->list->count());
		Size visibleSize = Director::getInstance()->getVisibleSize();
		
		int x =0.5 * visibleSize.width;
		int y = 0.5 * visibleSize.height;
		sprite->setPosition(Vec2(x, y));
		//this->removeChild(sprite);
		this->addChild(sprite,11,5); have++;
	}
}
Setting2::~Setting2()
{
	this->list->removeAllObjects();                                           
		CC_SAFE_RELEASE_NULL(this->list);                                        
}
void Setting2::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");
	Ref* obj = nullptr;

	auto listenerk = EventListenerKeyboard::create();
	listenerk->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event) {
		auto icon1 = this->getChildByTag(1);
		if (keyCode == EventKeyboard::KeyCode::KEY_S&&icon1->getPosition().y+50<=0)
		{
			auto moveto = MoveTo::create(0.2, icon1->getPosition() + Vec2(+0, +50));
			icon1->runAction(moveto);

			CCARRAY_FOREACH(this->list, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, +50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, +50));
			}
			CCARRAY_FOREACH(this->list2, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, +50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, +50));
			}
			CCARRAY_FOREACH(this->list3, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, +50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, +50));
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W&&icon1->getPosition().y + 50 >=-1200)
		{
			auto moveto = MoveTo::create(0.2, icon1->getPosition() + Vec2(+0, -50));
			icon1->runAction(moveto);

			CCARRAY_FOREACH(this->list, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, -50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, -50));
			}
			CCARRAY_FOREACH(this->list2, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, -50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, -50));
			}
			CCARRAY_FOREACH(this->list3, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+0, -50));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(0, -50));
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A&&icon1->getPosition().x+50<=0)
		{
			auto moveto = MoveTo::create(0.2, icon1->getPosition() + Vec2(+50, 0));
			icon1->runAction(moveto);

			CCARRAY_FOREACH(this->list, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+50,0 ));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(+50, 0));
			}
			CCARRAY_FOREACH(this->list2, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+50, 0));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(+50, 0));
			}
			CCARRAY_FOREACH(this->list3, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(+50, 0));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(+50, 0));
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_D&&icon1->getPosition().x + 50 >= -3150)
		{
			auto moveto = MoveTo::create(0.2, icon1->getPosition() + Vec2(-50, 0));
			icon1->runAction(moveto);

			CCARRAY_FOREACH(this->list, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(-50, 0));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(-50, 0));
			}
			CCARRAY_FOREACH(this->list2, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(-50, 0));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(-50, 0));
			}
			CCARRAY_FOREACH(this->list3, obj) {
				Sprite* sprite = (Sprite*)obj;
				auto moveto = MoveTo::create(0.2, sprite->getPosition() + Vec2(-50, 0));
				sprite->runAction(moveto);
				//sprite->setPosition(sprite->getPosition() + Vec2(-50, 0));
			}
		}
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenerk, this);

	////单点触摸监听器
	//auto listener1 = EventListenerTouchOneByOne::create();

	//listener1->setSwallowTouches(true);
	//listener1->onTouchBegan = CC_CALLBACK_2(Setting2::touchBegan, this);
	//listener1->onTouchMoved = CC_CALLBACK_2(Setting2::touchMoved, this);
	//listener1->onTouchEnded = CC_CALLBACK_2(Setting2::touchEnded, this);

	////注册监听器
	//EventDispatcher* mouse_eventDispatcher = Director::getInstance()->getEventDispatcher();
	/*_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, getChildByTag(kBox1_Tag));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), getChildByTag(kBox2_Tag));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), getChildByTag(kBox3_Tag));*/
}
void Setting2::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto enemyhouse = getChildByTag(666);
	if (money <= 999999)
		money++;
	stringstream ss;
	ss << money/10;
	ss >> s;
	if (money % 10 == 0)
	{
		auto label = this->getChildByTag(123);
		removeChildByTag(123);
		label = Label::createWithTTF("Money:" + s, "fonts/Marker Felt.ttf", 36);
		label->setPosition(Vec2(150, 700));
		//label->enableOutline(Color4B::BLACK, 10);
		//label->enableGlow(Color4B::YELLOW);
		addChild(label, 6,123);
	}	times++;
	if (times % 50 == 0)
	{
		times -= 50;
		Sprite* sprite = Sprite::create("Icon.png");
		this->list3->addObject(sprite);
		sprite->setPosition(enemyhouse->getPosition());
		int x = CCRANDOM_0_1() * visibleSize.width*0.6 - visibleSize.width*0.3;
		int y = CCRANDOM_0_1() * visibleSize.height*0.6 - visibleSize.height*0.3;
		auto moveto = MoveBy::create(0.2, Vec2(x, y));
		sprite->runAction(moveto);
		//this->removeChild(sprite);
		this->addChild(sprite, 10);
	}
}

bool Setting2::touchBegan(Touch* touch, Event* event)
{
	//获取事件所绑定的target
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//单击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite x = %f, y = %f", locationInNode.x, locationInNode.y);
		log("sprite tag = %d", target->getTag());
		target->runAction(ScaleBy::create(0.06f, 1.06f));
		Setting2::target = target;
		return true;
	}
	/*else if (MyScene::target != 0)
	{
	MyScene::target->runAction(MoveTo::create(2, touch->getLocation()));
	return true;
	}*/
	return false;
}

void Setting2::touchMoved(Touch* touch, Event* event)
{
	/*log("onTouchMoved");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setPosition(target->getPosition() + touch->getDelta());*/
}

void Setting2::touchEnded(Touch* touch, Event* event)
{
	//log("onTouchEnded");
	//auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//log("sprite onTouchesEnded");

	//Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	//Size s = target->getContentSize();
	//Rect rect = Rect(0, 0, s.width, s.height);
	////单击范围判断检测
	//if (rect.containsPoint(locationInNode))
	//{
	//log("sprite x = %f, y = %f", locationInNode.x, locationInNode.y);
	//log("sprite.tag = %d", target->getTag());
	target->runAction(ScaleTo::create(0.06f, 1.0f));
	//
	//}


}

//void Setting2::onExit()
//{
//	Layer::onExit();
//	log("MyScene onExit");
//	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
//
//}
