//
//  GameObject.cpp
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#include "GameObject.h"
#include "GameScene.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

using namespace engine;

std::shared_ptr<GameObject> GameObject::Instantiate(const std::string& templateName)
{
    cocos2d::Node* mRoot = GameScene::CurrentGameScene().lock()->getRootTransform();
    return GameObject::Instantiate(templateName, mRoot);
}

std::shared_ptr<GameObject> GameObject::Instantiate(const std::string& templateName, cocos2d::Node* root)
{
    // we use the template to create the necessary Components
    
    // components are of different types, we use enum and a switch
    
    // components are created via factory, which again uses a template
    
    // components should be added / add themselves to the correct update list.
    
    GameObjectRef go = GameObjectRef(new GameObject());
    
    GameComponentRef spriteComponent;
    spriteComponent = SpriteComponent::Create(go, root, "HelloWorld.png");
    go->mTransform = ((SpriteComponent*)spriteComponent.get())->getTransform();
    
    PhysicsComponentRef physicsComponent;
    physicsComponent = PhysicsSystem::Create(go);
    
    
    go->mComponents["sprite_c"] = spriteComponent;
    go->mComponents["physics_c"] = physicsComponent;
    
    return go;
}

GameObject::~GameObject()
{
}

GameObject::GameObject()
{
    
}

void GameObject::doSetup()
{
    GameComponentIt it;
    for(it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        (*it).second->setup();
    }
    
    for(it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        (*it).second->start();
    }
}

void GameObject::doTeardown()
{
    GameComponentIt it;
    for(it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        (*it).second->teardown();
    }
    
    mComponents.clear();
}

void GameObject::updateTransform(float x, float y, float rot)
{
    mTransform->setPosition(x * PTM_RATIO, y * PTM_RATIO);
    mTransform->setRotation(-1 * CC_RADIANS_TO_DEGREES(rot));
}

