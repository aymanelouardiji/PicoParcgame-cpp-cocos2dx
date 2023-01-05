#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScreen : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScreen);
    void GoToPauseScene(Ref* pSender);
    void GoToGameOverScene(Ref* pSender);
    cocos2d::Sprite *backgroundSprite;
    cocos2d::Sprite* characterSprite;
    private:
      cocos2d::PhysicsWorld* sceneWorld;
     void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };


};

#endif 
