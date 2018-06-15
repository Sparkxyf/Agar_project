//This is the main menu
#include "MainMenu.h"
#include<ui/CocosGUI.h>

#include<SimpleAudioEngine.h>
#include<ctime>
USING_NS_CC;
using namespace ui;
Scene* MainMenu::createScene()
{
	return MainMenu::create();
}
void MainMenu::switchSceneToSelectModeA(Ref* pSender)
{
//	auto Scene = SuvivalMode::createScene();
//	Director::getInstance()->replaceScene(Scene);

	 Director::getInstance()->end();
}
void MainMenu::switchSceneToSelectModeB(Ref* pSender)
{
	//	auto Scene = MistSuvivalMode::createScene();
	//	Director::getInstance()->replaceScene(Scene);

	Director::getInstance()->end();
}
void MainMenu::switchSceneToSelectModeC(Ref* pSender)
{
	//	auto Scene = MultiplayerMode::createScene();
	//	Director::getInstance()->replaceScene(Scene);

	Director::getInstance()->end();
}
bool MainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("HelloWorld.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
/*
	auto startGame_button = Button::create("StartMenu_startbutton.png");
	startGame_button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
	startGame_button->setScale(0.7);
	startGame_button->addClickEventListener(Widget::ccWidgetClickCallback(CC_CALLBACK_0(MainMenu::switchSceneToSelectModeA, this)));
	this->addChild(startGame_button);
*/
// add the label as a child to this layer
//Suvival(stand-alone)  ModeA
	auto MenuLabel = MenuItemLabel::create(Label::createWithTTF("Suvival(Stand-alone)", "fonts/Marker Felt.ttf", 36),
		CC_CALLBACK_1(MainMenu::switchSceneToSelectModeA, this));
	MenuLabel->setPosition(Vec2(origin.x / 2, origin.y / 2 + visibleSize.height / 4));
	MenuLabel->setColor(Color3B::RED);
	Menu * menu1 = Menu::create(MenuLabel, NULL);
	//menu1->setPosition(Vec2( origin.x/4,  origin.y/2));
	this->addChild(menu1);

	// add the label as a child to this layer
	//Mist Suvival(stand-alone)  ModeB
	auto MenuLabel2 = MenuItemLabel::create(Label::createWithTTF("Mist Suvival(stand-alone)", "fonts/Marker Felt.ttf", 36),
		CC_CALLBACK_1(MainMenu::switchSceneToSelectModeB, this));
	MenuLabel2->setPosition(Vec2(origin.x / 2, origin.y / 2 ));
	MenuLabel2->setColor(Color3B::RED);
	Menu * menu2 = Menu::create(MenuLabel2, NULL);
	//menu1->setPosition(Vec2( origin.x/4,  origin.y/2));
	this->addChild(menu2);


	// add the label as a child to this layer
	//Multiplayer  ModeC
	auto MenuLabel3 = MenuItemLabel::create(Label::createWithTTF("Multiplayer", "fonts/Marker Felt.ttf", 36),
		CC_CALLBACK_1(MainMenu::switchSceneToSelectModeC, this));
	MenuLabel3->setPosition(Vec2(origin.x / 2, origin.y / 2 - visibleSize.height / 4));
	MenuLabel3->setColor(Color3B::RED);
	Menu * menu3 = Menu::create(MenuLabel3, NULL);
	//menu1->setPosition(Vec2( origin.x/4,  origin.y/2));
	this->addChild(menu3);


	return true;
}

