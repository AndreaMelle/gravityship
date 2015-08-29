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

PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> gameObject)
    : GameComponent(gameObject)
    , mSmoothedPosition(b2Vec2(0,0))
    , mSmoothedAngle(0)
    , mPreviousPosition(b2Vec2(0,0))
    , mPreviousAngle(0)
{
    
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::doSetup()
{
//    pc->mDebugDraw = cocos2d::DrawNode::create();
//    pc->mDebugDraw->setPosition(0, 0);
//    
//    cocos2d::Vec2 size = cocos2d::Vec2(0.25f, 0.25f) * PTM_RATIO;
//    physicsComponent->mDebugDraw->drawRect(-size, size, cocos2d::Color4F::RED);
//    physicsComponent->mDebugDraw->drawPoint(cocos2d::Vec2::ZERO, 10.0f, cocos2d::Color4F::RED);
}

void PhysicsComponent::start()
{
    //mGameObject.lock()->getTransform()->getParent()->addChild(mDebugDraw,0);
}

void PhysicsComponent::doTeardown()
{
    //mGameObject.lock()->getTransform()->getParent()->removeChild(mDebugDraw);
    PhysicsSystem::GetCurrent()->remove(shared_from_this()); //invalidates body pointer!
}

void PhysicsComponent::update(float dt)
{
    mGameObject.lock()->updateTransform(mSmoothedPosition.x, mSmoothedPosition.y, mSmoothedAngle);
//
//    mDebugDraw->setPosition(mBody->GetPosition().x * PTM_RATIO, mBody->GetPosition().y * PTM_RATIO);
//    mDebugDraw->setRotation(-1 * CC_RADIANS_TO_DEGREES(mBody->GetAngle()));
    
}
