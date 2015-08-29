//
//  GameScene.cpp
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#include "GameScene.h"
#include "AppDelegate.h"

using namespace engine;

std::shared_ptr<GameScene> GameScene::Create()
{
    std::shared_ptr<GameScene> instance = std::shared_ptr<GameScene>(new GameScene());
    
    instance->mScene = RootLayer::createScene(instance);
    
    return instance;
}

std::weak_ptr<GameScene> GameScene::CurrentGameScene()
{
    AppDelegate *app = (AppDelegate*)cocos2d::Application::getInstance();
    return app->getCurrentScene();
}

//std::weak_ptr<b2World> GameScene::CurrentPhysicsWorld()
//{
//    AppDelegate *app = (AppDelegate*)cocos2d::Application::getInstance();
//    return app->getCurrentScene().lock()->getPhysicsWorld();
//}

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    teardown();
}

void GameScene::loop(float dt)
{
    //CCLOG("%f", dt);
    
    //destroy list
    
    //physics system handles fixed updates, collision handling, trigger handling and smooth animation step
    mPhysicsSystem->update(dt);
    
    //input processing and input state setting
    mHMISystem->update(dt);
    
    IUpdatableIt it;
    for(it = mUpdatableList.begin(); it != mUpdatableList.end(); ++it)
    {
        (*it)->update(dt);
    }
    
    // late update (?)
    mPhysicsSystem->lateUpdate(dt);
    
}

void GameScene::load()
{
    // create systems
    mPhysicsSystem = std::unique_ptr<PhysicsSystem>(new PhysicsSystem());
    mHMISystem = std::unique_ptr<HMISystem>(new HMISystem());
    
    mPhysicsSystem->setup();
    mHMISystem->setup();
    
    // load file stuff here
    GameObjectRef go = GameObject::Instantiate("helloworld");
    mGameObjectList.push_back(go);
}

void GameScene::doSetup()
{
    // create game objects here
    GameObjectIt it;
    for(it = mGameObjectList.begin(); it != mGameObjectList.end(); ++it)
    {
        (*it)->setup();
    }
}

void GameScene::doTeardown()
{
    GameObjectIt it;
    for(it = mGameObjectList.begin(); it != mGameObjectList.end(); ++it)
    {
        (*it)->teardown();
    }
    
    mGameObjectList.clear();
    
    mUpdatableList.clear();
    
    mPhysicsSystem->teardown();
    mHMISystem->teardown();
}