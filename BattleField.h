//This is the battlefield where the main game runs
#include<cocos2d.h>
#include<SimpleAudioEngine.h>
#include<ui\CocosGUI.h>
#include<math.h>

class FailMenu :public cocos2d::Layer
{
public:
	virtual bool init();
	void failToSelectMenu();
	void setCallBackOn();
	cocos2d::EventListenerKeyboard *keyboardListener;
	CREATE_FUNC(FailMenu);
};
class Combat :public cocos2d::Layer                   //class Combat is where to put all the balls and food
{
public:
	int _meBall;
	virtual bool init();
	Combat(int meBall) :_meBall(meBall) {}
	static Combat * create(int meBall) 
	{ 
		Combat *pRet = new(std::nothrow) Combat(meBall); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}
};
class Food :public cocos2d::Layer
{
public:
	int foodCount;
	virtual bool init();
	void foodRefresh(float del);
	void foodCreator();
	CREATE_FUNC(Food);
};
class BattleField : public cocos2d::Layer             //class BattleField is used as the parent node
{
public:
	//BackGround * _BG;
	int x;
	int y;
	//where is ai going
	cocos2d::Vec2& _direction_1 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2& _direction_2 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2& _direction_3 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2& _direction_4 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2& _direction_5 = cocos2d::Vec2(0, 0);
	int BGlevel = 0;

	float nodeX;
	float nodeY;
	int nodeCount;
	cocos2d::EventKeyboard::KeyCode _keycode;
	cocos2d::EventListenerKeyboard *k_listener;
	void update(float del);
	cocos2d::TMXTiledMap * _BG;
	Combat * _BC;
	FailMenu * _fail;
	Food * _food;
	static cocos2d::Scene  *createScene(int ballID);
	virtual bool init();
	void getDirection(float);
	void setCameraFollow();
	CREATE_FUNC(BattleField);
};
class ScoreCounter : public cocos2d::Layer
{
public:
	virtual bool init();
	void scoreUpdate(float del);
	int score;
	CREATE_FUNC(ScoreCounter);
};

/*class BackGround :public cocos2d::Layer
{

	virtual bool init();
	CREATE_FUNC(BackGround);
};*/



