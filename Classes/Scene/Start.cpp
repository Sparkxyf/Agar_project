#include "Start.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h" 

USING_NS_CC;
#include<ui/CocosGUI.h>
#include<ctime>

using namespace ui;
Scene* Start::createScene()
{
    return Start::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
  auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Start::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
	
    // create menu, it's an autorelease object
   auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	*/
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "start menu"
    // create and initialize a label

   // auto label = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 36);
	
 
   
  //add "init" splash screen"
    auto sprite = Sprite::create("init.png");
    if (sprite == nullptr)
    {
        problemLoading("'init.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


	auto MenuLabel = MenuItemLabel::create(Label::createWithTTF("START", "fonts/Marker Felt.ttf", 36),
		CC_CALLBACK_1(Start::menuCloseCallback, this));
	MenuLabel->setPosition(Vec2(origin.x/2,  origin.y / 2 - visibleSize.height / 4));
	MenuLabel->setColor(Color3B::RED);
	// add the label as a child to this layer

	 
	Menu * menu1 = Menu::create(MenuLabel, NULL);
	//menu1->setPosition(Vec2( origin.x/4,  origin.y/2));
	this->addChild(menu1);



    return true;
}


void Start::menuCloseCallback(Ref* pSender)
{


	auto Scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(Scene);
   // Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
