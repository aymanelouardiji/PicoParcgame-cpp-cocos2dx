#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene=Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}



// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto menuTitle =
        MenuItemImage::create("gameover.png",
            "gameover.png");
    auto retryItem =
        MenuItemImage::create("retry.png",
            "retry.png",
            CC_CALLBACK_1(GameOver::GoToGameScene, this));
    auto mainMenuItem =
        MenuItemImage::create("menu.png",
            "menu.png",
            CC_CALLBACK_1(GameOver::GoToMainMenuScene, this));
    auto menu = Menu::create(menuTitle, retryItem, mainMenuItem,
        NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 100000);
    this->addChild(menu);

    return true;
}
void GameOver::GoToGameScene(cocos2d::Ref* pSender)
{
    auto scene = GameScreen::createScene();

    Director::getInstance()->replaceScene(scene);
}
void GameOver::GoToMainMenuScene(cocos2d::Ref* pSender)
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create
    (1.0, scene));
}
