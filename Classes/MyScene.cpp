#include "MyScene.h"
USING_NS_CC;
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
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
	//获取整个手机可视屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
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