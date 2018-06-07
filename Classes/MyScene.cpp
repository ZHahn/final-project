//打算在此场景中加入自己写的layer，用于存放可操作的精灵，位于地图上层，触摸时先检测是否点击精灵，
//若否，根据点击位置移动已锁定的精灵，2018年6月5日00点01分



#include "MyScene.h"
USING_NS_CC;

Sprite* SpritesStorageLayer::target = NULL;		//静态成员变量初始化
Vec2 SpritesStorageLayer::targetLocation(0, 0);

Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	auto spriteLayer = SpritesStorageLayer::create();
	scene->addChild(spriteLayer, 100);
	scene->addChild(layer,10);		//(层的名字，优先级，tag）
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

	//创建一个显示"MyScene"文字的Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//设置白色
	label->setColor(Color3B::WHITE);
	// 设置label在屏幕中的显示位置
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// 把label添加到画面层
	this->addChild(label, 1);

	


	

	//添加精灵测试
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);
	MenuItemFont* item1 = MenuItemFont::create("Start game", CC_CALLBACK_1(MyScene::menuItem1Callback, this));
	MenuItemAtlasFont* item2 = MenuItemAtlasFont::create("Help", "menu/help.png", 48, 65, ' ',
		CC_CALLBACK_1(MyScene::menuItem2Callback, this));
	Menu* mn = Menu::create(item1, item2, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
	return true;
}

bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	if (SpritesStorageLayer::target != NULL)
	{
		SpritesStorageLayer::targetLocation = SpritesStorageLayer::target->getPosition();
		SpritesStorageLayer::target->stopAllActions();
		SpritesStorageLayer::target->runAction(MoveTo::create(SpritesStorageLayer::actionTime(locationInNode), touch->getLocation()));
	}

	return true;
}

void MyScene::onTouchMoved(Touch* touch, Event* event)
{

}

void MyScene::onTouchEnded(Touch* touch, Event* event)
{

}

