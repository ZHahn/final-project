#pragma once

#include"cocos2d.h"
#include"MyScene.h"
#include"��ͨС��.h"
#include"���幥��С��.h"
#include"math/CCMath.h"
#include<vector>


#define MAX_COUNT 100
USING_NS_CC;

typedef enum
{
	state_move=0,
	state_build=1
}touchState;

typedef enum
{
	barracksButtonTag=900
}buildingButton;

typedef enum
{
	barracks = 1900
}building;

typedef enum
{
	valid = 1,
	invalid = 0
}buildingPositionVal;


class Setting2 : public cocos2d::Layer
{
	
public:
	static cocos2d::__Array *list;
	static cocos2d::__Array *list2;
	cocos2d::__Array *list3;
	static MySpriteonebyone* target;
	static Vec2 targetLocation;
	static float actionTime(Vec2 currentLocation, Sprite* obj)	//������λ�ú�ѡ�еľ���
	{
		float x = currentLocation.x - obj->getPosition().x;
		float y = currentLocation.y - obj->getPosition().y;
		return 0.01*sqrt(x*x + y * y);
	}
	//���θ�ѡ������
	static float max_x;
	static float max_y;
	static float min_x;
	static float min_y;
	static std::vector<MySpriteonebyone*> targetList;
	static void groupSelectBegin(float x ,float y);
	static bool groupSelectBegin2(float x, float y);
	static void groupSelectMove(Vec2 location);
	static void drawRect(float x, float y);
	static void clearRect();
	static Layer* layer;
	static DrawNode* draw;

	//��ǰ���Ч���ж�
	static int touchState;	//�жϵ��������
	static buildingPositionVal barracksVal;

	//���ý���
	static void build(Vec2 position);

	~Setting2();
	/*static cocos2d::Scene* createScene();*/
	void back(cocos2d::Ref* pSender);
	void onEnter();
	virtual void update(float dt);
	virtual bool init();
	//void back(cocos2d::Ref* pSender);
	void menuCloseCAllback2(cocos2d::Ref* pSender);
	void menuCloseCAllback(cocos2d::Ref* pSender);
	//void onKeypressed(EventKeyboard::KeyCode keyCode, Event *event);
	//void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void getBloodbar(MySprite *guaisprite, float a);
	void getBloodbar(cocos2d::Sprite *guaisprite, float a);


	// implement the "static create()" method manually
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	//���㴥��
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(Setting2);
};
