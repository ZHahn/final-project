//�����ڴ˳����м����Լ�д��layer�����ڴ�ſɲ����ľ��飬λ�ڵ�ͼ�ϲ㣬����ʱ�ȼ���Ƿ������飬
//���񣬸��ݵ��λ���ƶ��������ľ��飬2018��6��5��00��01��
//2018.6.11�����ײ����



#include "MyScene.h"
USING_NS_CC;
const PhysicsMaterial PHYSICSBODY_MATERIAL_NOmoca(0.1f, 0.0f, 0.0f);	//Ħ��������ϵ������Ϊ0
Sprite* SpritesStorageLayer::target = NULL;		//��̬��Ա������ʼ��
Vec2 SpritesStorageLayer::targetLocation(0, 0);
Scene* MyScene::stoMyScene;


Scene* MyScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	MyScene::stoMyScene = scene;
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//���ڲ��ԣ����Ҫȥ��
	Vec2 gravity0(0, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity0);//��������Ϊ0
	auto layer = MyScene::create();
	//auto spriteLayer = SpritesStorageLayer::create();
	//scene->addChild(spriteLayer, 0);
	scene->addChild(layer,1);		//(������֣����ȼ���tag��
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
	
	//�㴥����Ӧ
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//��ȡ�����ֻ�������Ļ�ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//����߽������(û��Ҫ)
	/*auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*10, visibleSize.height*10), PHYSICSBODY_MATERIAL_NOmoca, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width, visibleSize.height));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);*/

	

	

	////���LayerColor��,ccc4�ĵ�һ������Ϊ͸����,ռ��������Ļ��setPositionê��λ��Ϊ���½�
	//ccColor4B color4B = ccc4(200, 0, 0, 100);
	//CCLayerColor* layerColor = CCLayerColor::create(color4B, visibleSize.width, visibleSize.height);
	//layerColor->setPosition(Vec2(origin.x, origin.y));
	//this->addChild(layerColor,100);		//localZOderԽ��Խ����

	////����LayerMultiplex��㲼����
	//auto layers = LayerMultiplex::create(layerColor, layer, nullptr);
	//this->addChild(layers, 0, "layers");
	////layers->addLayer();
	//layers->switchTo(0);

	////����һ����ʾ"MyScene"���ֵ�Label
	//auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	////���ð�ɫ
	//label->setColor(Color3B::WHITE);
	//// ����label����Ļ�е���ʾλ��
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));
	//// ��label��ӵ������
	//this->addChild(label, 1);

	


	

	////��Ӿ������
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
	Vec2 locationInWorld = touch->getLocation();//ѡ�е����������
	log("x=%f,y=%f", locationInWorld.x, locationInWorld.y);
	/*if (Setting2::touchState == state_build)
	{
		Setting2::build(locationInWorld);
		return false;
	}*/
	
	//Ⱥ��ѡ��
	//if(Setting2::targetList.empty())
		Setting2::groupSelectBegin(locationInWorld.x, locationInWorld.y);
	
	return true;
}

void MyScene::onTouchMoved(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Vec2 locationInWorld = touch->getLocation();//ѡ�е����������
	Setting2::drawRect(locationInWorld.x, locationInWorld.y);
}

void MyScene::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Vec2 locationInWorld = touch->getLocation(); //�ɿ������������
	Setting2::draw->clear();	//�ɿ�ʱ������ο�
	
	//�����ɿ��������
	if(Setting2::groupSelectBegin2(locationInWorld.x, locationInWorld.y))
		//if (Setting2::targetList.empty())
		{
			return;
		}
	//�����ƶ�
	if (Setting2::target != NULL)
	{
		Setting2::targetLocation = Setting2::target->getPosition();
		Setting2::target->stopAllActions();
		//Setting2::target->stopAttack();
		Setting2::target->runAction(MoveTo::create(Setting2::actionTime(locationInWorld, Setting2::target), touch->getLocation()));
	}
	//Ⱥ���ƶ�
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

