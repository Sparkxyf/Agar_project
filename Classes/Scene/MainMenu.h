// This is the main menu
#include"cocos2d.h"
class MainMenu :public cocos2d::Scene
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	void switchSceneToSelectModeA(cocos2d::Ref* pSender);
	void switchSceneToSelectModeB(cocos2d::Ref* pSender);
	void switchSceneToSelectModeC(cocos2d::Ref* pSender);
	CREATE_FUNC(MainMenu);
};
#pragma once
