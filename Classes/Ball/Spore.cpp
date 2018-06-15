#include "Spore.h"
#include<ui/CocosGUI.h>
#include"Ball.h"
#include<SimpleAudioEngine.h>
#include<ctime>
USING_NS_CC;
using namespace ui;

Spore::Spore()
{

}

Spore::~Spore()
{

}

Spore * Spore::create(const std::string& filename)
{
	Spore * spore = new Spore();
	if (spore && spore->init(filename))
	{
		spore->autorelease();
		return spore;
	}
	CC_SAFE_DELETE(spore);
	return nullptr;
}

bool Spore::init(const std::string& filename)
{
	_skinID = 1;
	if (!Ball::initWithFile(filename))
	{
		return false;
	}

	f_rad = 25;
	i_score = 15;

	Size size = this->getContentSize();
	float scale = (f_rad * 2) / size.width;
	this->setScale(scale);

	return true;
}

Spore * Spore::create(int id)
{
	Spore * spore = new Spore();
	if (spore && spore->init(id))
	{
		spore->autorelease();
		return spore;
	}
	CC_SAFE_DELETE(spore);
	return nullptr;
}

bool Spore::init(int id)
{
	_skinID = id;
	std::string filename = StringUtils::format("public/keyword_%d.png", id);
	if (!Ball::initWithFile(filename))
	{
		return false;
	}

	f_rad = 20;
	i_score = 100;

	Size size = this->getContentSize();
	float scale = (f_rad * 2) / size.width;
	this->setScale(scale);

	return true;
}

int Spore::getID()
{
	return _skinID;
}