/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto scene=Scene::create();
    auto layer=GameScreen::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}



// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create("menu.png", "menu.png",CC_CALLBACK_1(GameScreen::GoToPauseScene, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width -(pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height +(pauseItem->getContentSize().width / 4) + origin.y));
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    //CREATE SCENE1
    auto backgroundSprite = Sprite::create("scene1.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) +origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);
    //CREATE PLAYER
    auto mySprite = Sprite::create("player.png");
    mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(mySprite);
    //edit the position init
    auto action = Place::create(Point(20, 160));
    mySprite->runAction(action);
    //********************************************************************************************************
// create a static PhysicsBody
   
    //********************************************************************************************************
    auto eventListener = EventListenerKeyboard::create();



    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        int offsetX = 0, offsetY = 0;

        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            offsetX = -30;

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            offsetX = 30;
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            offsetY = 30;
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            offsetY = -30;
            break;
        }


        auto moveTo = MoveTo::create(0.3, Vec2(event->getCurrentTarget()->getPositionX() + offsetX, event->getCurrentTarget()->getPositionY() + offsetY));
        event->getCurrentTarget()->runAction(moveTo);


    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, mySprite);
//************************************************************************************************************
   /* auto body = PhysicsBody::createBox(mySprite->getContentSize());
    mySprite->setPhysicsBody(body);

    // Set up key press event listener
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [=](::EventKeyboard::KeyCode keyCode,Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            jump();
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);*/

    return true;
}

void GameScreen::GoToPauseScene(cocos2d::Ref* pSender)
{
    auto scene = PauseMenu::createScene();

    Director::getInstance()->pushScene(scene);
}
void GameScreen::GoToGameOverScene(cocos2d::Ref* pSender)
{
    auto scene = GameOver::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create
    (1.0, scene));
}

/*void GameScreen::jump()
{
    // Apply impulse force to character's physics body
    auto body = mySprite->getPhysicsBody();
    body->applyImpulse(cocos2d::Vec2(0, 50));
};*/
