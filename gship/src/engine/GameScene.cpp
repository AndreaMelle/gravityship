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

std::weak_ptr<b2World> GameScene::CurrentPhysicsWorld()
{
    AppDelegate *app = (AppDelegate*)cocos2d::Application::getInstance();
    return app->getCurrentScene().lock()->getPhysicsWorld();
}

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
}

void GameScene::loop(float dt)
{
    //CCLOG("%f", dt);
    
    //destroy list
    //fixed update
    
    float32 fixedTimeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    mPhysicsWorld->Step(fixedTimeStep, velocityIterations, positionIterations);
    
    //collision handling
    //trigger handling
    //input processing
    //update components
    //
    
    // internal animation loop
    GameObjectIt it;
    for(it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
    {
        (*it)->update();
    }
    
}

void GameScene::load()
{
    //b2Vec2 gravity(0.0f, -10.0f);
    b2Vec2 gravity(0.0f, -1.0f);
    mPhysicsWorld = std::shared_ptr<b2World>(new b2World(gravity));
    
    // load file stuff here
    GameObjectRef go = GameObject::Instantiate("helloworld");
    mGameObjects.push_back(go);
}

void GameScene::doSetup()
{
    // create game objects here
    GameObjectIt it;
    for(it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
    {
        (*it)->setup();
    }
}

void GameScene::doTeardown()
{
    GameObjectIt it;
    for(it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
    {
        (*it)->teardown();
    }
    
    mGameObjects.clear();
}