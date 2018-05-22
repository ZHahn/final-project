#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "MyScene.h"
#include "cocos2d.h"


class HelloWorld : public cocos2d::Scene
{
public:
	//切换到下一个scene事件

	void menuNextCallback(cocos2d::Ref* pSender);
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
