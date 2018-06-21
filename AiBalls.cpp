#include"AiBalls.h"

USING_NS_CC;

AiBalls* AiBalls::createWithFileName(Layer*lSender, const std::string& filename, int ID,int subid, int level)
{
	AiBalls* zz = new(std::nothrow) AiBalls;
	if (zz&&zz->initWithFile(filename) && zz->initStatus(level, ID))
	{
		zz->autorelease();
		lSender->addChild(zz, 1);
		zz->setSUBID(subid);
		return zz;
	}
	CC_SAFE_DELETE(zz);
	return nullptr;
}

Vec2&AiBalls::getDirection( float nodeX, float nodeY, int BGlevel)
{
	int _x_ai = 0, _y_ai = 0;
	float distance, x0, y0;
	x0 = this->getPositionX() - nodeX;
	y0 = this->getPositionY() - nodeY;
	distance = (0.0001*(x0*x0) + 0.0001*(y0*y0));
	
	if (distance > 40)
	{
		_x_ai = nodeX;
		_y_ai = nodeY;
	}

	if (distance < 40)
	{
		if (this->getLevel() <= BGlevel)
		{
			_x_ai = 2 * this->getPositionX() - nodeX;
			_y_ai = 2 * this->getPositionY() - nodeY;
		}
		else if (this->getLevel() > BGlevel)
		{
			_x_ai = nodeX;
			_y_ai = nodeY;
		}
	}
	return Vec2(_x_ai, _y_ai);
}
Vec2& AiBalls::getOriginalPosition(int num)
{

	if (num == 0) return Vec2(1640, 1640);
	if (num == 1) return Vec2(2640, 2640);
	if (num == 2) return Vec2(3640, 3640);
	if (num == 3) return Vec2(4640, 4640);
	if (num == 4) return Vec2(1640, -1640);
	if (num == 5) return Vec2(2640, -2640);
	if (num == 6) return Vec2(3640, -3640);
	if (num == 7) return Vec2(4640, -4640);
	if (num == 8) return Vec2(-1640, 1640);
	if (num == 9) return Vec2(-2640, 2640);
	if (num == 10) return Vec2(-3640, 3640);
	if (num == 11) return Vec2(-2640, 4640);
	if (num == 12) return Vec2(-1640, -1640);
	if (num == 13) return Vec2(-2640, -2640);
	if (num == 14) return Vec2(-3640, -3640);
	if (num == 15) return Vec2(-4640, -4640);
	return Vec2(0, 0);
}
Vec2& AiBalls::getNewPosition(int SUBID)
{
	if (SUBID == 1) return Vec2(0, 0);
	if (SUBID == 2) return Vec2(5120, 5120);
	if (SUBID == 3) return Vec2(5120, -5120);
	if (SUBID == 4)return Vec2(-5120, 5120);
	if (SUBID == 5)return Vec2(-5120, -5120);
	return Vec2(0, 0);
}