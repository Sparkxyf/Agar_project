//This is the battlefield where the main game runs
//BattleField coordinate system:
// x: -5120 to 5120
// y: -5120 to 5120
#include "BattleField.h"
#include "MainMenu.h"
#include "AiBalls.h"
#include<ctime>

USING_NS_CC;
Scene * BattleField::createScene(int ballID)
{
	auto scene = Scene::create();
	auto layerBattleField = BattleField::create();
	auto layerBC = Combat::create(ballID);
	scene->addChild(layerBattleField,1);
	layerBattleField->_BC = layerBC;
	layerBattleField->addChild(layerBC, 2);
	auto layerFail = FailMenu::create();
	layerBattleField->_fail = layerFail;
	scene->addChild(layerFail, 3);
	auto layerScoreCounter = ScoreCounter::create();
	scene->addChild(layerScoreCounter,4,4);    //tag 4 for ScoreCounter
	auto layerFood = Food::create();
	layerBattleField->addChild(layerFood,1,"food");
	layerBattleField->_food = layerFood;
	return scene;
}
void BattleField::setCameraFollow()
{
	Vec2 delVec = Vec2(640, 360) - this->getPosition() - Vec2(nodeX, nodeY);   //CAUTION!:coordinate system change
	this->setPosition(this->getPosition() + delVec);
}
void BattleField::getDirection(float dt)
{
	cocos2d::Vector<Node*> allballs;

	allballs = this->_BC->getChildren();

	for (auto target : allballs)
	{
		AiBalls* target_p = dynamic_cast<AiBalls*>(target);
		if (target_p != nullptr)
		{
			if (target_p->getID() == 2 && target_p->getSUBID() == 1) _direction_1 = target_p->getDirection( nodeX, nodeY, BGlevel);
			if (target_p->getID() == 2 && target_p->getSUBID() == 2) _direction_2 = target_p->getDirection(nodeX, nodeY, BGlevel);
			if (target_p->getID() == 2 && target_p->getSUBID() == 3) _direction_3 = target_p->getDirection( nodeX, nodeY, BGlevel);
			if (target_p->getID() == 2 && target_p->getSUBID() == 4) _direction_4 = target_p->getDirection( nodeX, nodeY, BGlevel);
			if (target_p->getID() == 2 && target_p->getSUBID() == 5) _direction_5 = target_p->getDirection( nodeX, nodeY, BGlevel);
		}
	}
}
void BattleField::update(float del)
{
	cocos2d::Vector<Node*> allballs;
	allballs = this->_BC->getChildren();
	float nowX = x - this->getPositionX();
	float nowY = y - this->getPositionY();
	float nodeSumX=0;
	float nodeSumY=0;
	int nowNodeCount=0;
	int _BGlevel = 0;
	
	for (auto target : allballs)
	{
		Balls* target_b = dynamic_cast<Balls*>(target);
		if (target_b != nullptr&&target_b->getID() == 1)
		{
			target_b->movement(nowX, nowY, this->_BC, 1);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
			if (target_b->getLevel() > _BGlevel) _BGlevel = target_b->getLevel();
			target_b->swallow(nowX, nowY,this->_food);
			target_b->swallow(nowX, nowY, this->_BC);
			if (target_b != nullptr&&_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE&&nodeCount < 8)
			{
				target_b->division(nowX, nowY, _keycode, this->_BC);
				this->unscheduleUpdate();
				//	for debug using
			}
			nodeSumX += target_b->getPositionX();
			nodeSumY += target_b->getPositionY();
			nowNodeCount++;
			target_b->updateRadius();
		}
		//±ß½ç
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 1)
		{
			target_b->movement(_direction_1.x, _direction_1.y, this->_BC, 2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 2)
		{
			target_b->movement(_direction_2.x, _direction_2.y, this->_BC,2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 3)
		{
			target_b->movement(_direction_3.x, _direction_3.y, this->_BC, 2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 4)
		{
			target_b->movement(_direction_4.x, _direction_4.y, this->_BC, 2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 5)
		{
			target_b->movement(_direction_5.x, _direction_5.y, this->_BC, 2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
		if (target_b != nullptr&&target_b->getID() == 2 && target_b->getSUBID() == 6)
		{
			target_b->movement(nodeX, nodeY, this->_BC, 2);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120 + target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120 - target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120 + target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120 - target_b->getRadius());
		}
	}
	
	BGlevel = _BGlevel;
	nodeCount = nowNodeCount;
	if (nodeCount!=0)
	{
		nodeX = nodeSumX / nodeCount;
		nodeY = nodeSumY / nodeCount;
		setCameraFollow();
		this->unscheduleUpdate();
		//for debug using¡ü
	}
	else
	{
		k_listener->setEnabled(false);
		(this->getParent()->getChildByTag(4))->unschedule(schedule_selector(ScoreCounter::scoreUpdate));
		dynamic_cast<LabelTTF *>(_fail->getChildByName("result"))->setString(dynamic_cast<LabelTTF *>(this->getParent()->getChildByTag(4)->getChildByName("display"))->getString());
		_fail->setVisible(true);
		_fail->keyboardListener->setEnabled(true);
	}
	_keycode = cocos2d::EventKeyboard::KeyCode::KEY_NONE;

}
bool Combat::init()
{
	std::srand(std::time(0));
	if (!Layer::init())
	{
		return false;
	}
	Balls * myBall;
	float randomNum = CCRANDOM_0_1();
	if (randomNum<0.33f)
	{
		myBall = Balls::createWithFileName("Ball_1.png");
	}
	else if (randomNum < 0.66f)
	{
		myBall = Balls::createWithFileName("Ball_2.png");
	}
	else
	{
		myBall = Balls::createWithFileName("Ball_3.png");
	}
	myBall->initStatus(10, 1);
	myBall->setPosition(Vec2(640,360));
	this->addChild(myBall, 1);
	//create Ai
	int num = CCRANDOM_0_1() * 15;
	auto aiBalls1 = AiBalls::createWithFileName(this, "Ai_1.png", 2, 1, 30);
	aiBalls1->setPosition(aiBalls1->getOriginalPosition(num));
	num = CCRANDOM_0_1() * 15;


	auto aiBalls2 = AiBalls::createWithFileName(this, "Ai_2.png", 2, 2, 60);
	aiBalls2->setPosition(aiBalls1->getOriginalPosition(num));
	aiBalls2->runAction(CCRepeatForever::create(RotateBy::create(2, 360)));
	num = CCRANDOM_0_1() * 15;
	auto aiBalls3 = AiBalls::createWithFileName(this, "Ai_1.png", 2, 3, 90);
	aiBalls3->setPosition(aiBalls1->getOriginalPosition(num));
	num = CCRANDOM_0_1() * 15;
	auto aiBalls4 = AiBalls::createWithFileName(this, "Ai_2.png", 2, 4, 120);
	aiBalls4->setPosition(aiBalls1->getOriginalPosition(num));
	aiBalls4->runAction(CCRepeatForever::create(RotateBy::create(2, -360)));
	num = CCRANDOM_0_1() * 15;
	auto aiBalls5 = AiBalls::createWithFileName(this, "Ai_1.png", 2, 5, 150);
	aiBalls5->setPosition(aiBalls1->getOriginalPosition(num));
	num = CCRANDOM_0_1() * 15;
	auto aiBalls6 = AiBalls::createWithFileName(this, "Ai_3.png", 2, 6, 999);
	aiBalls6->setPosition(aiBalls1->getOriginalPosition(num));
	return true;
}

void FailMenu::failToSelectMenu()
{
	auto transition = TransitionPageTurn::create(0.8f, MainMenu::createScene(), true);
	Director::getInstance()->replaceScene(transition);
}
bool FailMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto failImg = Sprite::create("fail.png");
	failImg->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(failImg);
	auto result = LabelTTF::create("0", "Chiller", 60);
	result->setPosition(Vec2(640, 100));
	this->addChild(result,2,"result");
	keyboardListener= EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		failToSelectMenu();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
	keyboardListener->setEnabled(false);
	this->setVisible(false);
	return true;
}
bool BattleField::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	x = visibleSize.width / 2 + originPos.x;
	y = visibleSize.height / 2 + originPos.y;
	_BG = TMXTiledMap::create("BG1.tmx");
	this->addChild(_BG,-1);
	_BG->setAnchorPoint(Vec2(0.5,0.5));
	_BG->setPosition(Vec2(0,0));
	this->schedule(schedule_selector(BattleField::update), 0.02f);
	//for debug using¡ü
	this->scheduleUpdate();
	this->schedule(schedule_selector(BattleField::getDirection),0.4f);
	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseMove = [=](Event * event)
	{
		EventMouse* _event = (EventMouse *)event;
		x = _event->getCursorX();
		y = _event->getCursorY();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	k_listener = EventListenerKeyboard::create();
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);
	return true;
}
bool Food::init()
{
	if (!Layer::init())
	{
		return false;
	}
	foodCount = 0;
	foodCreator();
	this->schedule(schedule_selector(Food::foodRefresh), 1.5f);
}
void Food::foodRefresh(float del)
{
	auto cache = SpriteFrameCache::getInstance();
	while (foodCount < 1200)
	{
		int xPos = CCRANDOM_MINUS1_1() * 4800;
		int yPos = CCRANDOM_MINUS1_1() * 4800;
		float timeFix = (dynamic_cast<ScoreCounter *>(this->getParent()->getParent()->getChildByTag(4))->score) / 780+1;
		if (timeFix > 1.8f)timeFix = 1.8f;
		float food_colour;
		food_colour = CCRANDOM_0_1()*timeFix;
		if (food_colour < 0.16)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("red"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.33)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("yellow"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.48)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("blue"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.66)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("green"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.82)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("purple"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if(food_colour<0.93)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("scolor"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("Boom"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusBoom();
			this->addChild(food);
			foodCount += 1;
		}
	}
}
void Food::foodCreator()
{
	SpriteFrameCache::getInstance()->destroyInstance();
	while (foodCount < 7)
	{
		int xPos = CCRANDOM_MINUS1_1() * 4800;
		int yPos = CCRANDOM_MINUS1_1() * 4800;
		if (foodCount == 0)
		{
			auto food = Balls::createWithFileName("food_red.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "red");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount == 1)
		{
			auto food = Balls::createWithFileName("food_ye.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "yellow");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount == 2)
		{
			auto food = Balls::createWithFileName("food_blue.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "blue");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount == 3)
		{
			auto food = Balls::createWithFileName("food_green.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "green");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount == 4)
		{
			auto food = Balls::createWithFileName("food_pu.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "purple");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount==5)
		{
			auto food = Balls::createWithFileName("food_sc.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "scolor");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else
		{
			auto food = Balls::createWithFileName("cs.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "Boom");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusBoom();
			this->addChild(food);
			foodCount += 1;
		}
	}
}
bool ScoreCounter::init()
{
	if (!Layer::init())
	{
		return false;
	}
	score = 0;
	this->schedule(schedule_selector(ScoreCounter::scoreUpdate), 1.0f);
	auto scoreDisplay = LabelTTF::create("0", "Chiller", 40);
	auto timeBG = Sprite::create("time.png");
	timeBG->setPosition(Vec2(154, 680));
	timeBG->setScale(0.8);
	this->addChild(timeBG, 0);
	scoreDisplay->setColor(Color3B::WHITE);
	scoreDisplay->setPosition(Vec2(148, 681));
	this->addChild(scoreDisplay, 1, "display");
	return true;
}
void ScoreCounter::scoreUpdate(float del)
{
	score++;
	dynamic_cast<LabelTTF *>(this->getChildByName("display"))->setString(__String::createWithFormat("%d\' %d\"", (score / 60), (score % 60))->getCString());
}
