#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// 按钮点击事件，点击后push到MyScene
void HelloWorld::menuNextCallback(Ref* pSender)
{
	//新建MyScene实例
	auto scene = MyScene::createScene();
	//用这MyScene实例替换当前scene
	Director::getInstance()->pushScene(scene);
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.test
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	////贴图
	//auto bg = Sprite::create("BackGroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	////贴图的纹理参数
	//Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	//bg->getTexture()->setTexParameters(tp);
	//bg->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//addChild(bg, 0);

	//创建三个方块精灵
	Sprite* boxA = Sprite::create("BoxA2.png");
	boxA->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(-120, 120));
	addChild(boxA, 10, kBoxA_Tag);

	Sprite* boxB = Sprite::create("BoxB2.png");
	boxA->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(boxB, 20, kBoxB_Tag);

	Sprite* boxC = Sprite::create("BoxC2.png");
	boxA->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(120, 160));
	addChild(boxC, 30, kBoxC_Tag);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
	//我的改动
	// 新建一个带图片的按钮菜单
	auto goItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuNextCallback, this));
	goItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - closeItem->getContentSize().width / 2, origin.y / 2 + closeItem->getContentSize().height / 2));

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);
	MenuItemFont* placeMenu = MenuItemFont::create("PLACE", CC_CALLBACK_1(HelloWorld::OnClickMenu, this));
	placeMenu->setTag(PLACE_TAG);
	MenuItemFont* flipXMenu = MenuItemFont::create("FlipX", CC_CALLBACK_1(HelloWorld::OnClickMenu, this));
	flipXMenu->setTag(FLIPX_TAG);
	
	auto mn = Menu::create(placeMenu, flipXMenu, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);


	//结束改动
	

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, goItem, NULL);  //此处原来为(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::OnClickMenu(Ref* pSpender)
{
	MenuItem* nmitem = (MenuItem*)pSpender;

	auto sc = Scene::create();
	auto layer = MyAction::create();
	layer->setTag(nmitem->getTag());

	sc->addChild(layer);

	auto reScene = TransitionSlideInR::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	log("HelloWorld onEnter");
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);

	//注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(kBoxA_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(kBoxB_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(kBoxC_Tag));
}

bool HelloWorld::touchBegan(Touch* touch, Event* event)
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
		return true;
	}
	return false;
}

void HelloWorld::touchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setPosition(target->getPosition() + touch->getDelta());
}

void HelloWorld::touchEnded(Touch* touch, Event* event)
{
	log("onTouchEnded");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	log("sprite onTouchesEnded");

	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	//单击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite x = %f, y = %f", locationInNode.x, locationInNode.y);
		log("sprite.tag = %d", target->getTag());
		target->runAction(ScaleTo::create(0.06f, 1.0f));
	}
}

void HelloWorld::onExit()
{
	Scene::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

}