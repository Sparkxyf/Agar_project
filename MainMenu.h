// This is the main menu
#include"cocos2d.h"
class MainMenu :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	void switchSceneToSelectModeA();
	void switchSceneToSelectModeB();
	virtual bool init();
	CREATE_FUNC(MainMenu);
};


