//This is the main menu
#include "MainMenu.h"
//#include"BallSelectMenu.h"
#include<ui/CocosGUI.h>
#include<SimpleAudioEngine.h>
#include<ctime>
USING_NS_CC;
using namespace ui;
Scene* MainMenu::createScene()
{
	return MainMenu::create();
}
void MainMenu::switchSceneToSelectModeA()
{
	//auto transition = TransitionPageTurn::create(1.2f, BallSelectMenu::createScene(0), false);
	//Director::getInstance()->replaceScene(transition);
}
void MainMenu::switchSceneToSelectModeB()
{
	//auto transition = TransitionPageTurn::create(1.2f, BallSelectMenu::createScene(1), false);
	//Director::getInstance()->replaceScene(transition);
}
bool MainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("init.png");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);

		auto startGame_button = Button::create("StartMenu_startbutton.png");
		startGame_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
		startGame_button->setScale(0.7);
		startGame_button->addClickEventListener(Widget::ccWidgetClickCallback(CC_CALLBACK_0(MainMenu::switchSceneToSelectModeA, this)));
		this->addChild(startGame_button);



	return true;
}
