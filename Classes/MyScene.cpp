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
	//��ȡ�����ֻ�������Ļ�ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����һ����ʾ"MyScene"���ֵ�Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//���ð�ɫ
	label->setColor(Color3B::WHITE);
	// ����label����Ļ�е���ʾλ��
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// ��label��ӵ������
	this->addChild(label, 1);

	//��Ӿ������
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