//打算在此场景中加入自己写的layer，用于存放可操作的精灵，位于地图上层，触摸时先检测是否点击精灵，
//若否，根据点击位置移动已锁定的精灵，2018年6月5日00点01分
//2018.6.11添加碰撞测试



#include "MyScene.h"
USING_NS_CC;
const PhysicsMaterial PHYSICSBODY_MATERIAL_NOmoca(0.1f, 0.0f, 0.0f);	//摩擦、弹性系数设置为0
Sprite* SpritesStorageLayer::target = NULL;		//静态成员变量初始化
Vec2 SpritesStorageLayer::targetLocation(0, 0);
Scene* MyScene::stoMyScene;


Scene* MyScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	MyScene::stoMyScene = scene;
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//用于测试，最后要去掉
	Vec2 gravity0(0, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity0);//设置重力为0
	auto layer = MyScene::create();
	//auto spriteLayer = SpritesStorageLayer::create();
	//scene->addChild(spriteLayer, 0);
	scene->addChild(layer,1);		//(层的名字，优先级，tag）
	auto map = Setting2::create();
	Setting2::layer = map;
	scene->addChild(map, 2);
	return scene;
}

void MyScene::menuItem1Callback(Ref* pSpender)
{
	MenuItem* item = (MenuItem*)pSpender;
	log("Touch Start Menu Item %p", item);
	Director::getInstance()->popScene();
}

void MyScene::menuItem2Callback(Ref* pSpender)
{
	MenuItem* item = (MenuItem*)pSpender;
	log("Touch Help Menu Item %p", item);
}

bool MyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//层触摸响应
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//获取整个手机可视屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//定义边界的世界(没必要)
	/*auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*10, visibleSize.height*10), PHYSICSBODY_MATERIAL_NOmoca, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width, visibleSize.height));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);*/

	

	

	////添加LayerColor层,ccc4的第一个参数为透明度,占满整个屏幕，setPosition锚点位置为左下角
	//ccColor4B color4B = ccc4(200, 0, 0, 100);
	//CCLayerColor* layerColor = CCLayerColor::create(color4B, visibleSize.width, visibleSize.height);
	//layerColor->setPosition(Vec2(origin.x, origin.y));
	//this->addChild(layerColor,100);		//localZOder越大越往上

	////创建LayerMultiplex多层布景层
	//auto layers = LayerMultiplex::create(layerColor, layer, nullptr);
	//this->addChild(layers, 0, "layers");
	////layers->addLayer();
	//layers->switchTo(0);

	////创建一个显示"MyScene"文字的Label
	//auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	////设置白色
	//label->setColor(Color3B::WHITE);
	//// 设置label在屏幕中的显示位置
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));
	//// 把label添加到画面层
	//this->addChild(label, 1);

	


	

	////添加精灵测试
	//MenuItemFont::setFontName("Times New Roman");
	//MenuItemFont::setFontSize(86);
	//MenuItemFont* item1 = MenuItemFont::create("Start game", CC_CALLBACK_1(MyScene::menuItem1Callback, this));
	//MenuItemAtlasFont* item2 = MenuItemAtlasFont::create("Help", "menu/help.png", 48, 65, ' ',
	//	CC_CALLBACK_1(MyScene::menuItem2Callback, this));
	//Menu* mn = Menu::create(item1, item2, NULL);
	//mn->alignItemsVertically();
	//this->addChild(mn);
	return true;
}

bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Vec2 locationInWorld = touch->getLocation();//选中点的世界坐标
	log("x=%f,y=%f", locationInWorld.x, locationInWorld.y);
	/*if (Setting2::touchState == state_build)
	{
		Setting2::build(locationInWorld);
		return false;
	}*/
	
	//群体选中
	//if(Setting2::targetList.empty())
		Setting2::groupSelectBegin(locationInWorld.x, locationInWorld.y);
	
	return true;
}

void MyScene::onTouchMoved(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Vec2 locationInWorld = touch->getLocation();//选中点的世界坐标
	Setting2::drawRect(locationInWorld.x, locationInWorld.y);
}

void MyScene::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Vec2 locationInWorld = touch->getLocation(); //松开点的世界坐标
	Setting2::draw->clear();	//松开时清除矩形框
	
	//输入松开点的数据
	if(Setting2::groupSelectBegin2(locationInWorld.x, locationInWorld.y))
		//if (Setting2::targetList.empty())
		{
			return;
		}
	//单个移动
	if (Setting2::target != NULL)
	{
		Setting2::targetLocation = Setting2::target->getPosition();
		Setting2::target->stopAllActions();
		//Setting2::target->stopAttack();
		Setting2::target->runAction(MoveTo::create(Setting2::actionTime(locationInWorld, Setting2::target), touch->getLocation()));
	}
	//群体移动
	//Setting2::groupSelectMove(touch->getLocation());
	int number = Setting2::targetList.size();
	if (number > 0)
	{
		Node* Gtarget;
		for (int i = 0; i<number; i++)
		{
			Gtarget = Setting2::targetList[i];
			Gtarget->stopAllActions();
			//(MySprite*)Gtarget->stopAttack();
			Gtarget->runAction(MoveTo::create(Setting2::actionTime(locationInWorld, (Sprite*)Gtarget), locationInWorld));

		}
	}
}


//void MyScene::onEnter()
//{
//	Layer::onEnter();
//
//}

