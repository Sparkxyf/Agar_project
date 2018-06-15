#include "Prick.h"
#include<ui/CocosGUI.h>
#include"Ball.h"
#include<SimpleAudioEngine.h>
#include<ctime>
USING_NS_CC;
using namespace ui;


Prick::Prick()
{

}

Prick::~Prick()
{

}

Prick * Prick::create(const std::string& filename)
{
	Prick * prick = new Prick();
	if (prick && prick->init(filename))
	{
		prick->autorelease();
		return prick;
	}
	CC_SAFE_DELETE(prick);
	return nullptr;
}

bool Prick::init(const std::string& filename)
{
	if (!Ball::initWithFile(filename))
	{
		return false;
	}

	f_rad = 60;
	i_score = 128;

	Size size = this->getContentSize();
	float scale = (f_rad * 2) / size.width;
	this->setScale(scale);

	return true;
}