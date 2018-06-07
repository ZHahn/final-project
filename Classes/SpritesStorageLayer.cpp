#include"SpritesStorageLayer.h"
USING_NS_CC;

bool SpritesStorageLayer::init()
{
	if (!Layer::init())
	{
		return(false);
	}

	//获取整个手机可视屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	//创建三个方块精灵
	Sprite* boxA = Sprite::create("BoxA.png");
	boxA->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(boxA, 10, kBox1_Tag);

	Sprite* boxB = Sprite::create("BoxB.png");
	boxB->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height/2) + Vec2(40, 50));
	addChild(boxB, 20, kBox2_Tag);

	Sprite* boxC = Sprite::create("BoxC.png");
	boxC->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(60, 20));
	addChild(boxC, 30, kBox3_Tag);

	return true;
}

void SpritesStorageLayer::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");
	auto listener1 = EventListenerTouchOneByOne::create();

	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(SpritesStorageLayer::touchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(SpritesStorageLayer::touchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(SpritesStorageLayer::touchEnded, this);

	//注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, getChildByTag(kBox1_Tag));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), getChildByTag(kBox2_Tag));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), getChildByTag(kBox3_Tag));
}

bool SpritesStorageLayer::touchBegan(Touch* touch, Event* event)
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
		SpritesStorageLayer::target = target;
		return true;
	}
	/*else if (MyScene::target != 0)
	{
	MyScene::target->runAction(MoveTo::create(2, touch->getLocation()));
	return true;
	}*/
	return false;
}

void SpritesStorageLayer::touchMoved(Touch* touch, Event* event)
{
	/*log("onTouchMoved");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setPosition(target->getPosition() + touch->getDelta());*/
}

void SpritesStorageLayer::touchEnded(Touch* touch, Event* event)
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

void SpritesStorageLayer::onExit()
{
	Layer::onExit();
	log("MyScene onExit");
	/*Director::getInstance()->getEventDispatcher()->removeEventListener(listener1);*/

}
