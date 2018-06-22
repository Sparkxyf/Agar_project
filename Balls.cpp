//This is the character
//default designed size is  480*480 p          
//default designed radius=339 p                
#include <cocos2d.h>
#include<math.h>
#include"BattleField.h"
#include"AiBalls.h"
const char * randomName(float randomNum)
{
	if (randomNum<0.33f)
	{
		return "Ai_1.png";
	}
	else if (randomNum < 0.66f)
	{
		return "Ai_2.png";
	}
	else
	{
		return "Ai_3.png";
	}
}

Balls* Balls::createWithFileName(const std::string & filename)
{
	Balls *ball = new(std::nothrow) Balls;
	if (ball&&ball->initWithFile(filename) && ball->initStatus(1, 0))
	{
		ball->autorelease();
		return ball;
	}		
	CC_SAFE_DELETE(ball);
	return nullptr;
}
Balls* Balls::createWithBallsFrame(cocos2d::SpriteFrame *spriteFrame)
{
	Balls *sprite = new (std::nothrow) Balls();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
bool Balls::initStatus(int tlevel, int id)
{
	this->_level = tlevel;
	this->_identity = id;
	if (this != nullptr)
		this->updateRadius();
	return true;
}
bool Balls::initStatusMin()
{
	this->_level = 1;
	this->_identity = 0;
	this->_radius = 20;
	this->setScale(0.08f);
	return true;
}
bool Balls::initStatusBoom()
{
	this->_level = 80;
	this->_identity = -1;
	this->_radius = 40;
	this->updateRadius();
	return true;
}

void Balls::setID(int identity)
{
	_identity = identity;
}
void Balls::setSUBID(int subid)
{
	_subid = subid;
}
int Balls::getID()
{
	return _identity;
}
int Balls::getSUBID()
{
	return _subid;
}
int Balls:: getRadius()
{
	return _radius;
}
unsigned int Balls::getLevel()
{
	return _level;
}
void Balls::updateRadius()                                          //update the radius and size when level changes
{
	double sizeLevel = _level / 10;
	this->setScale(sqrt(sizeLevel) / 10);
	_radius = sqrt(sizeLevel) * 234 / 10;
}
void Balls::LevelLimit()
{
	if (this->_level > 1000)this->_level = 1000;
}
void Balls:: addLevel(const int delLevel)                              //after eating other balls,call this
{
	_level += delLevel;
	if (_level > 1000) _level = 1000;								//the level limit should be adjusted later
}
float Balls::speed()
{
	if (this->_level > 1000)this->_level = 1000;
	float ballSpeed = 7.25 - 0.00625*this->_level;
	if (this->getID() == 2)ballSpeed = ballSpeed*0.9;
	
	return ballSpeed;
}

void Balls::division(float x, float y, cocos2d::EventKeyboard::KeyCode &_keycode, cocos2d::Layer* _Battelfield)
{
	
	if (_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE&&this->_level > 40 && this != nullptr)
	{
		this->_level = this->_level / 2;
		//if (this != nullptr)
		this->updateRadius();
		Balls* substitute = this->createWithBallsFrame(this->getSpriteFrame());
		substitute->initStatus(this->_level, this->_identity);
		float distance = cocos2d::ccpDistance(this->getPosition(), cocos2d::Vec2(x, y));
		if (distance < 0.01f)distance = 0.01f;
		float x1 = this->getPositionX() + (x - this->getPositionX())  / distance;
		float y1 = this->getPositionY() + (y - this->getPositionY())  / distance;
		float x2 = (x - this->getPositionX()) * 100 / distance;
		float y2 = (y - this->getPositionY()) * 100 / distance;
		substitute->setPosition(x1,y1);
		auto move = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(2*x2,2*y2));
		substitute->runAction(move);
		_Battelfield->addChild(substitute, 1);
	}
}
void Balls::divisionBoom(float x, float y, cocos2d::Layer* _Battelfield)
{
	
	cocos2d::Sprite* substitute;
	if (dynamic_cast<Combat *>(this->getParent())->_meBall == 1)
	{
		substitute = cocos2d::Sprite::create("Ball_1.png");
	}
	else if (dynamic_cast<Combat *>(this->getParent())->_meBall == 2)
	{
		substitute= cocos2d::Sprite::create("Ball_2.png");
	}
	else
	{
		substitute= cocos2d::Sprite::create("Ball_3.png");
	}
	substitute->setPosition(this->getPosition());
	if (this->_level <= 40)
	{
		substitute->setScale(this->getScale()/2);
		this->getParent()->removeChild(this);
	}
	else
	{
		this->_level = _level / 2;
		this->updateRadius();
		substitute->setScale(this->getScale());
	}
	_Battelfield->addChild(substitute);

}

void Balls::movement(float x, float y, cocos2d::Layer *_Battlefield, int player_id)
{
	cocos2d::Vector<Node*> _allballs;
	_allballs = _Battlefield->getChildren();
	for (auto _target : _allballs)
	{
		Balls* the_target = dynamic_cast<Balls*>(_target);
		if (the_target != nullptr&&the_target->_identity == player_id &&the_target != this)
		{
			float distance = cocos2d::ccpDistance(this->getPosition(), the_target->getPosition());
			if (distance < 0.01f)distance = 0.01f;
			if (distance < the_target->_radius + this->_radius)
			{
				float x2 = this->getPositionX() - (the_target->getPositionX() - this->getPositionX()) *(the_target->_radius + this->_radius - distance) / distance;
				float y2 = this->getPositionY() - (the_target->getPositionY() - this->getPositionY()) *(the_target->_radius + this->_radius - distance) / distance;
				this->setPosition(cocos2d::Vec2(x2, y2));
			}
		}
	}
	if (this->_identity == player_id)
	{
		float distance = cocos2d::ccpDistance(this->getPosition(), cocos2d::Vec2(x, y));
		if (distance < 0.01f)distance = 0.01f;
		float x1 = this->getPositionX() + (x - this->getPositionX()) * this->speed() / distance;
		float y1 = this->getPositionY() + (y - this->getPositionY()) * this->speed() / distance;
		this->setPosition(x1, y1);
	}
}
void Balls::swallow(float x, float y, cocos2d::Layer *_Battlefield)
{
	cocos2d::Vector<Node*> _allballs;
	_allballs = _Battlefield->getChildren();
	for (auto _target : _allballs)
	{
		Balls* target_b = dynamic_cast<Balls*>(_target);
		if (target_b != nullptr&&target_b->_identity != this->_identity)
		{
			float _distance = cocos2d::ccpDistance(target_b->getPosition(), this->getPosition());
			if (target_b->_identity != -1)
			{
				if (_distance <= this->_radius + target_b->_radius)
				{
					if (this->_level > target_b->_level)
					{
						_Battlefield->removeChild(target_b);
						this->addLevel(target_b->_level);
						if (target_b->getID() == 0)dynamic_cast<Food *>(_Battlefield)->foodCount--;
						if (target_b->getID() == 2)
						{
							float randomNum = CCRANDOM_0_1();
							auto newAI = AiBalls::createWithFileName(_Battlefield, randomName(randomNum), 2, target_b->getSUBID(), this->getLevel() + (target_b->getSUBID() * 30));
							newAI->setPosition(newAI->getNewPosition(target_b->getSUBID()));
						}
					}
					else if (this->_level < target_b->_level)
					{
						_Battlefield->removeChild(this);
					}
				}
			}
			else if (_distance <= this->_radius + target_b->_radius)
			{
				_Battlefield->removeChild(target_b);
				this->divisionBoom(x,y,_Battlefield);
			}
		}
	}
}
