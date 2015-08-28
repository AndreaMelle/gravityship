//
//  PhysicsComponent.cpp
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#include "PhysicsComponent.h"
#include "GameScene.h"

using namespace engine;

std::shared_ptr<PhysicsComponent> PhysicsComponent::Create(std::weak_ptr<GameObject> gameObject)
{
    PhysicsComponentRef physicsComponent = PhysicsComponentRef(new PhysicsComponent(gameObject));
    
    //this actually comes from the template...
    physicsComponent->mBodyDef = std::shared_ptr<b2BodyDef>(new b2BodyDef());
    physicsComponent->mShape = std::shared_ptr<b2PolygonShape>(new b2PolygonShape());
    physicsComponent->mFixtureDef = std::shared_ptr<b2FixtureDef>(new b2FixtureDef());
    
    physicsComponent->mBodyDef->type = b2_dynamicBody;
    physicsComponent->mBodyDef->position.Set(20.0f, 20.0f);
    //physicsComponent->mBodyDef->userData = gameObject;
    
    physicsComponent->mShape->SetAsBox(0.25f, 0.25f);
    
    physicsComponent->mFixtureDef->shape = physicsComponent->mShape.get();
    physicsComponent->mFixtureDef->density = 10.0f;
    physicsComponent->mFixtureDef->friction = 0.4f;
    physicsComponent->mFixtureDef->restitution = 0.1f;
    
    physicsComponent->mDebugDraw = cocos2d::DrawNode::create();
    physicsComponent->mDebugDraw->setPosition(0, 0);
    
    cocos2d::Vec2 size = cocos2d::Vec2(0.25f, 0.25f) * PTM_RATIO;
    physicsComponent->mDebugDraw->drawRect(-size, size, cocos2d::Color4F::RED);
    physicsComponent->mDebugDraw->drawPoint(cocos2d::Vec2::ZERO, 10.0f, cocos2d::Color4F::RED);
    
    
    
    return physicsComponent;
}

PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> gameObject) : GameComponent(gameObject)
{
    
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::doSetup()
{
    mBody = GameScene::CurrentPhysicsWorld().lock()->CreateBody(mBodyDef.get());
    mBody->CreateFixture(mFixtureDef.get());
    
}

void PhysicsComponent::start()
{
    mGameObject.lock()->getTransform()->getParent()->addChild(mDebugDraw,0);
}

void PhysicsComponent::doTeardown()
{
    mGameObject.lock()->getTransform()->getParent()->removeChild(mDebugDraw);
    
    std::shared_ptr<b2World> world = GameScene::CurrentPhysicsWorld().lock();
    if(world && mBody)
    {
        world->DestroyBody(mBody);
    }
}

void PhysicsComponent::update()
{
//    cocos2d::Node *node = mGameObject.lock()->getTransform();
//    node->setPosition(mBody->GetPosition().x * PTM_RATIO, mBody->GetPosition().y * PTM_RATIO);
//    node->setRotation(-1 * CC_RADIANS_TO_DEGREES(mBody->GetAngle()));
//    
//    mDebugDraw->setPosition(mBody->GetPosition().x * PTM_RATIO, mBody->GetPosition().y * PTM_RATIO);
//    mDebugDraw->setRotation(-1 * CC_RADIANS_TO_DEGREES(mBody->GetAngle()));
    
}
