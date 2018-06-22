//This is the character
//default designed size is  480*480 p          
//default designed radius=339 p                
#include <cocos2d.h>
#include<math.h>
class Balls : public cocos2d::Sprite
{
private:
	float _level;
	int _radius;
	int _subid;
	int _identity;                                                   
public:
	bool isfood;
	//skill to be done
	static Balls* createWithFileName(const std::string & filename);
	static Balls* createWithBallsFrame(cocos2d::SpriteFrame *spriteFrame);
	bool initStatus(int tlevel, int id);
	bool initStatusMin();
	bool initStatusBoom();
	void setID(int identity);
	void setSUBID(int SUBID);
	int getID();
	int getSUBID();
	int getRadius();
	unsigned int getLevel();
	void updateRadius();                                    //update the radius and size when level changes
	void addLevel(const int delLevel);                           //after eating other balls,call this
	void LevelLimit();
	float speed();
	void division(float x, float y, cocos2d::EventKeyboard::KeyCode &_keycode, cocos2d::Layer* _Battelfield);
	void divisionBoom(float x, float y, cocos2d::Layer* _Battelfield);
	void movement(float x, float y, cocos2d::Layer *_Battlefield, int player_id);
	void swallow(float x, float y, cocos2d::Layer *_Battlefield);
};
