#include"容器测试场景.h"
#include "SimpleAudioEngine.h"
#include "base/CCEventKeyboard.h"
#include<string>
#include<sstream>
using namespace std;

USING_NS_CC;
bool have=0;
long money = 0;
int spritenumber = 0;
string s="0";
int times = 0;
int orgin_tag = 100;	//精灵tag的初始值，每生成一个新精灵就+1
MySpriteonebyone* Setting2::target = NULL;
Vec2 Setting2::targetLocation(0, 0);
vector<MySpriteonebyone*> Setting2::targetList;
__Array* Setting2::list;
float Setting2::max_x;
float Setting2::max_y;
float Setting2::min_x;
float Setting2::min_y;
Layer* Setting2::layer = NULL;
DrawNode* Setting2::draw = NULL;



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
	this->getBloodbar(enemyhouse, 100.0f);

	auto background = Sprite::create("1.jpg");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2(0, 0));
	background->runAction(ScaleTo::create(0.02f, 3.0f));
	this->addChild(background, 2,1);

	//for (int i = 0; i < MAX_COUNT; ++i) {
		//Sprite* sprite = Sprite::create("pu_green_ball.png");                                   
		//	this->list->addObject(sprite);                                         
	//}
	draw = DrawNode::create(); //绘制矩形选框
	this->addChild(draw, 10);
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
		MySpriteonebyone* sprite = MySpriteonebyone::create(1);	//创建可控制精灵
		//添加物理体积
		auto bodyS = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
		bodyS->setContactTestBitmask(0xFFFFFFFF);
		sprite->setPhysicsBody(bodyS);
		//物理体积设定结束
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
				MySprite* sprite = (MySprite*)obj;
				sprite->setPosition(house->getPosition());
				this->getBloodbar(sprite, 100.0f);
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
				mouse_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2->clone(), sprite);
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
		this->getBloodbar(sprite, 100.0f);
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
bool mt(MySprite *s1, MySprite *s2)
{
	int x2 = (s1->getPosition().x - s2->getPosition().x)*(s1->getPosition().x - s2->getPosition().x);
	int y2 = (s1->getPosition().y - s2->getPosition().y)*(s1->getPosition().y - s2->getPosition().y);
	if (sqrt(x2 + y2) <= 100 && s1->SpriteState != (int)SpriteState::DEAD&&s1->SpriteState != (int)SpriteState::DEAD)
		return 1;
	else return 0;
}
void Setting2::update(float dt)
{
	auto fadeOut = FadeOut::create(1.0f);
	auto house = getChildByTag(5);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto enemyhouse = getChildByTag(666);
	if (money <= 999999)
		money++;
	stringstream ss;
	ss << money / 10;
	ss >> s;
	if (money % 10 == 0)
	{
		auto label = this->getChildByTag(123);
		removeChildByTag(123);
		label = Label::createWithTTF("Money:" + s, "fonts/Marker Felt.ttf", 36);
		label->setPosition(Vec2(150, 700));
		//label->enableOutline(Color4B::BLACK, 10);
		//label->enableGlow(Color4B::YELLOW);
		addChild(label, 6, 123);
	}	times++;
	if (times % 150 == 0 && have == 1)
	{
		times -= 150;
		MySpriteonebyone* sprite = MySpriteonebyone::create(2);
		this->list3->addObject(sprite);
		sprite->setPosition(enemyhouse->getPosition());
		int x1 = enemyhouse->getPosition().x;
		int y1 = enemyhouse->getPosition().y;
		int x2 = house->getPosition().x;
		int y2 = house->getPosition().y;
		auto moveto = MoveBy::create(20, Vec2(x2 - x1, y2 - y1));
		sprite->runAction(moveto);
		this->getBloodbar(sprite, 100.0f);
		//this->removeChild(sprite);
		this->addChild(sprite, 10);
		//单点触摸监听器	
		auto listener3 = EventListenerTouchOneByOne::create();

		listener3->setSwallowTouches(true);
		listener3->onTouchBegan = CC_CALLBACK_2(Setting2::touchBegan, this);
		listener3->onTouchMoved = CC_CALLBACK_2(Setting2::touchMoved, this);
		listener3->onTouchEnded = CC_CALLBACK_2(Setting2::touchEnded, this);

		//注册监听器
		EventDispatcher* mouse_eventDispatcher3 = Director::getInstance()->getEventDispatcher();
		mouse_eventDispatcher3->addEventListenerWithSceneGraphPriority(listener3->clone(), sprite);
		orgin_tag++;
	}
	if (times % 30 == 0) {
		Ref* obj1 = nullptr;
		Ref* obj3 = nullptr;

		CCARRAY_FOREACH(this->list, obj1) {
			MySprite* sprite1 = (MySprite*)obj1;
			if (sprite1->SpriteState != (int)SpriteState::DEAD)
			{
				CCARRAY_FOREACH(this->list3, obj3) {
					MySprite* sprite3 = (MySprite*)obj3;
					if (mt(sprite1, sprite3) && sprite3->SpriteState != (int)SpriteState::DEAD)
					{
						sprite1->attack();
						sprite3->attack();
						sprite1->hurt();
						sprite3->hurt();
						sprite3->removeChildByTag(2);
						this->getBloodbar(sprite3, sprite3->HP);
						sprite1->removeChildByTag(2);
						this->getBloodbar(sprite1, sprite1->HP);
					}
					//else sprite1->setRotation(0);
				}
			}
		}

	}
	if (times % 60 == 0)
	{
		Ref* obj3 = nullptr;
		CCARRAY_FOREACH(this->list3, obj3) {
			MySprite* sprite3 = (MySprite*)obj3;
			if (sprite3->HP <= 0)
			{
				sprite3->removeAllChildren();
				sprite3->runAction(fadeOut);
				//this->list3->removeObject(sprite3);
				//this->removeChild(sprite3);
			}
		}

		Ref* obj1 = nullptr;
		CCARRAY_FOREACH(this->list, obj1) {
			MySprite* sprite1 = (MySprite*)obj1;
			if (sprite1->HP <= 0)
			{
				sprite1->removeAllChildren();
				sprite1->runAction(fadeOut);
				//this->list->removeObject(sprite1);
				//this->removeChild(sprite1);
			}
		}
	}
	if (times % 60 == 59)
	{
		Ref* obj3 = nullptr;
		CCARRAY_FOREACH(this->list3, obj3) {
			MySprite* sprite3 = (MySprite*)obj3;
			if (sprite3->SpriteState == (int)SpriteState::DEAD)
			{
				//this->list3->removeObject(sprite3);
				this->removeChild(sprite3);
			}
		}

		Ref* obj1 = nullptr;
		CCARRAY_FOREACH(this->list, obj1) {
			MySprite* sprite1 = (MySprite*)obj1;
			if (sprite1->SpriteState == (int)SpriteState::DEAD)
			{
				//this->list->removeObject(sprite1);
				this->removeChild(sprite1);
			}
		}
	}

}


bool Setting2::touchBegan(Touch* touch, Event* event)
{
	//获取事件所绑定的target
	auto target = static_cast<MySpriteonebyone*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());	//将getLocation返回的世界坐标转换为模型坐标
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//单击范围判断检测
	if (rect.containsPoint(locationInNode)&&target->SpriteType == (int)SpriteType::PLAYER)	//点击我方精灵&&target.team == 1
	{
		log("sprite x = %f, y = %f", locationInNode.x, locationInNode.y);
		log("sprite tag = %d", target->getTag());
		//target->runAction(ScaleBy::create(0.06f, 1.06f));
		Setting2::target = target;
		Setting2::targetList.clear();	//点击单个目标时清空群体选中列表
		return true;
	}
	else if (rect.containsPoint(locationInNode) && target->SpriteType ==(int) SpriteType::ENEMY)	//点击敌方精灵
	{
		if (Setting2::target != NULL)
		{
			Setting2::target->attack(target);
			return true;
		}
		else if (!Setting2::targetList.empty())
		{
			for (int i = 0; i < Setting2::targetList.size(); i++)
			{
				Setting2::targetList[i]->attack(target);
			}
			return true;
		}
	}
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
	//target->runAction(ScaleTo::create(0.06f, 1.0f));
	//
	//}


}
void Setting2::groupSelectBegin(float x, float y)
{
	//群体选中按下
	Setting2::max_x = x;	//存入初始点的数据
	Setting2::max_y = y;
}
bool Setting2::groupSelectBegin2(float x, float y)
{
	if (x > Setting2::max_x)
	{
		Setting2::min_x = Setting2::max_x;
		Setting2::max_x = x;
	}
	else
		Setting2::min_x = x;
	if (y > Setting2::max_y)
	{
		Setting2::min_y = Setting2::max_y;
		Setting2::max_y = y;
	}
	else
		Setting2::min_y = y;
	float width = Setting2::max_x - Setting2::min_x;
	float height = Setting2::max_y - Setting2::min_y;
	//创造矩形
	if (width > 30 && height > 30)	//矩形的最小尺寸
	{
		Setting2::targetList.clear();	//清空群体选中列表
		Setting2::target = NULL;	//清空单体选中，即如果矩形不选中任何目标，效果等于清除当前选中状态
		Rect rect = Rect(Setting2::min_x, Setting2::min_y, width, height);
		//遍历容器中的数据
		Ref* obj = nullptr;
		CCARRAY_FOREACH(Setting2::list, obj) {
			//spr = (Sprite*)Setting2::list->getObjectAtIndex(i);
			//Vec2 nodeLocation = spr->getPosition();	//获取list容器中精灵坐标
			//if (rect.containsPoint(nodeLocation))
			//{
			//	targetList.push_back(spr->getTag());	//如果精灵在矩形范围内，获取tag并压入targetList
			//}
			//i++;
			MySpriteonebyone* spr = (MySpriteonebyone*)obj;
			Vec2 nodeLocation = spr->getPosition();
			if (rect.containsPoint(nodeLocation))
			{
				Setting2::targetList.push_back(spr);	//如果精灵在矩形范围内，获取tag并压入targetList
				
			}
		}
		//选中完成后清空数据
		Setting2::clearRect();
		return true;
	}
	return false;
	//for (int i = 0; i < list->count(); i++)
	//{
	//	Sprite* spr = (Sprite*)list->objectAtIndex(i);
	//	Vec2 nodeLocation = spr->getPosition();
	//	if (rect.containsPoint(nodeLocation))
	//	{
	//		Setting2::targetList.push_back(spr->getTag());	//如果精灵在矩形范围内，获取tag并压入targetList
	//	}
	//}
}
void Setting2::drawRect(float x, float y)
{
	float width = Setting2::max_x - x;
	float height = Setting2::max_y - y;
	Setting2::draw->clear();
	Vec2 points[] = { Vec2(Setting2::max_x, Setting2::max_y),Vec2(Setting2::max_x,y), Vec2(x, y) ,Vec2(x,Setting2::max_y)};
	Setting2::draw->drawPolygon(points, 4, Color4F(0, 0, 0, 0), 2, Color4F(0, 0, 1, 1));
	//Setting2::layer->addChild(draw, 20);
}
void Setting2::clearRect()
{
	Setting2::max_x = 0;
	Setting2::min_x = 0;
	Setting2::max_y = 0;
	Setting2::min_y = 0;
}
void Setting2::getBloodbar(MySprite *guaisprite, float a) { //guaispirte为怪物精灵的参数
	CCSprite *pBloodKongSp = CCSprite::create("silver-button-normal@2x.png");//空血条
	pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 0.85));
	guaisprite->addChild(pBloodKongSp);
	CCSprite *pBloodManSp = CCSprite::create("Inkedblankboodl_LI.jpg");//满血条
	CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodManSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 0.85));
	pBloodProGress->setPercentage(a);
	guaisprite->addChild(pBloodProGress, 1, 2);
}
void Setting2::getBloodbar(Sprite *guaisprite, float a) { //guaispirte为怪物精灵的参数
	CCSprite *pBloodKongSp = CCSprite::create("silver-button-normal@2x.png");//空血条
	pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 0.85));
	guaisprite->addChild(pBloodKongSp);
	CCSprite *pBloodManSp = CCSprite::create("Inkedblankboodl_LI.jpg");//满血条
	CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodManSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 0.85));
	pBloodProGress->setPercentage(a);
	guaisprite->addChild(pBloodProGress, 1, 2);
}

//void Setting2::onExit()
//{
//	Layer::onExit();
//	log("MyScene onExit");
//	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
//
//}
