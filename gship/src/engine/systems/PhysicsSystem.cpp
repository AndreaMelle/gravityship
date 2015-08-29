//
//  PhysicsSystem.cpp
//  gship
//
//  Created by Andrea Melle on 28/08/2015.
//
//

#include "PhysicsSystem.h"
#include "GameScene.h"

using namespace engine;

const float PhysicsSystem::FIXED_TIMESTEP = 1.f / 60.f;
const int PhysicsSystem::MAX_STEPS = 5; // Maximum number of steps, to avoid degrading to an halt.

std::shared_ptr<PhysicsComponent> PhysicsSystem::Create(std::weak_ptr<GameObject> gameObject)
{
    PhysicsComponentRef pc = PhysicsComponentRef(new PhysicsComponent(gameObject));
    
    //this actually comes from the template...
    pc->mBodyDef = std::shared_ptr<b2BodyDef>(new b2BodyDef());
    pc->mShape = std::shared_ptr<b2PolygonShape>(new b2PolygonShape());
    pc->mFixtureDef = std::shared_ptr<b2FixtureDef>(new b2FixtureDef());
    
    pc->mBodyDef->type = b2_dynamicBody;
    pc->mBodyDef->position.Set(20.0f, 20.0f);
    //pc->mBodyDef->userData = gameObject;
    
    pc->mShape->SetAsBox(0.25f, 0.25f);
    
    pc->mFixtureDef->shape = pc->mShape.get();
    pc->mFixtureDef->density = 10.0f;
    pc->mFixtureDef->friction = 0.4f;
    pc->mFixtureDef->restitution = 0.1f;
    
    std::shared_ptr<b2World> world = PhysicsSystem::GetCurrent()->mPhysicsWorld;
    
    pc->mBody = world->CreateBody(pc->mBodyDef.get());
    pc->mBody->CreateFixture(pc->mFixtureDef.get());
    
    PhysicsSystem::GetCurrent()->mPhysicsComponentList.push_back(pc);
    
    return pc;
}

PhysicsSystem::PhysicsSystem()
    : mFixedTimestepAccumulator (0)
    , mFixedTimestepAccumulatorRatio (0)
    , mVelocityIterations(6)
    , mPositionIterations(2)
{
    
}

PhysicsSystem::~PhysicsSystem()
{
    teardown();
}

PhysicsSystem* PhysicsSystem::GetCurrent()
{
    return GameScene::CurrentGameScene().lock()->mPhysicsSystem.get();
}

void PhysicsSystem::doSetup()
{
    b2Vec2 gravity(0.0f, -10.0f);
    mPhysicsWorld = std::shared_ptr<b2World>(new b2World(gravity));
    mPhysicsWorld->SetAutoClearForces (false);
}

void PhysicsSystem::doTeardown()
{
    mFixedUpdatableList.clear();
    mCollidableList.clear();
}

void PhysicsSystem::remove(PhysicsComponentRef pc)
{
    if(pc->mBody)
    {
        mPhysicsWorld->DestroyBody(pc->mBody);
        pc->mBody = nullptr;
    }
    
    std::vector<PhysicsComponentRef>::iterator it = std::find(mPhysicsComponentList.begin(), mPhysicsComponentList.end(), pc);
    
    if(it != mPhysicsComponentList.end())
    {
        mPhysicsComponentList.erase(it);
    }
    
}

void PhysicsSystem::update(float dt)
{
    mFixedTimestepAccumulator += dt;
    const int nSteps = static_cast<int> (std::floor (mFixedTimestepAccumulator / FIXED_TIMESTEP));
    
    // To avoid rounding errors, touches fixedTimestepAccumulator_ only if needed.
    if (nSteps > 0)
    {
        mFixedTimestepAccumulator -= nSteps * FIXED_TIMESTEP;
    }
    
#if defined(DEBUG)
    assert ("Accumulator must have a value lesser than the fixed time step"
            && mFixedTimestepAccumulator < FIXED_TIMESTEP + FLT_EPSILON);
#endif
    
    mFixedTimestepAccumulatorRatio = mFixedTimestepAccumulator / FIXED_TIMESTEP;
    
    // This is similar to clamp "dt":
    //	dt = std::min (dt, MAX_STEPS * FIXED_TIMESTEP)
    // but it allows above calculations of fixedTimestepAccumulator_ and
    // fixedTimestepAccumulatorRatio_ to remain unchanged.
    const int nStepsClamped = std::min (nSteps, MAX_STEPS);
    for (int i = 0; i < nStepsClamped; ++ i)
    {
        // In singleStep_() the CollisionManager could fire custom
        // callbacks that uses the smoothed states. So we must be sure
        // to reset them correctly before firing the callbacks.
        resetSmoothStates ();
        singleStep (FIXED_TIMESTEP);
    }
    
    mPhysicsWorld->ClearForces ();
    
    // We "smooth" positions and orientations using
    // fixedTimestepAccumulatorRatio_ (alpha).
    smoothStates();
    
}

void PhysicsSystem::lateUpdate(float dt)
{
    for(auto pc : mPhysicsComponentList)
    {
        pc->update(dt);
    }
}

void PhysicsSystem::singleStep(float dt)
{
    callFixedUpdates(dt); //equivalent to fixedStep update in Unity
    mPhysicsWorld->Step (dt, mVelocityIterations, mPositionIterations);
    consumeContacts(); //fires callbacks
}

void PhysicsSystem::smoothStates ()
{
    const float oneMinusRatio = 1.f - mFixedTimestepAccumulatorRatio;
    
    for(auto pc : mPhysicsComponentList)
    {
        b2Body *b = pc->mBody;
        if (b->GetType () == b2_staticBody)
        {
            continue;
        }
        
        //PhysicsComponent & c = PhysicsComponent::b2BodyToPhysicsComponent (* b);
        
        pc->mSmoothedPosition = mFixedTimestepAccumulatorRatio * b->GetPosition() + oneMinusRatio * pc->mPreviousPosition;
        
        pc->mSmoothedAngle = mFixedTimestepAccumulatorRatio * b->GetAngle() + oneMinusRatio * pc->mPreviousAngle;
    }
}

void PhysicsSystem::resetSmoothStates()
{
    for(auto pc : mPhysicsComponentList)
    {
        b2Body *b = pc->mBody;
        if (b->GetType () == b2_staticBody)
        {
            continue;
        }
        
        //PhysicsComponent & c = PhysicsComponent::b2BodyToPhysicsComponent (* b);
        pc->mSmoothedPosition = pc->mPreviousPosition = b->GetPosition ();
        pc->mSmoothedAngle = pc->mPreviousAngle = b->GetAngle ();
    }
}

void PhysicsSystem::callFixedUpdates(float dt)
{
    // loop through all the components registered for fixedUpdate callback
    for(auto it : mFixedUpdatableList)
    {
        it->fixedUpdate(dt);
    }
}

void PhysicsSystem::consumeContacts()
{
    // loop through all the components registered for collisions callback
    for(auto it :mCollidableList)
    {
        it->onCollision();
    }
}

//void PhysicsSystem::smoothStates_ ()
//{
//    const float dt = fixedTimestepAccumulatorRatio_ * FIXED_TIMESTEP;
//    
//    for (b2Body * b = world_->GetBodyList (); b != NULL; b = b->GetNext ())
//    {
//        if (b->GetType () == b2_staticBody)
//        {
//            continue;
//        }
//        
//        PhysicsComponent & c = PhysicsComponent::b2BodyToPhysicsComponent (* b);
//        c.smoothedPosition_ = b->GetPosition () + dt * b->GetLinearVelocity ();
//        c.smoothedAngle_ = b->GetAngle () + dt * b->GetAngularVelocity ();
//    }
//}
//
//
//
//void PhysicsSystem::resetSmoothStates_ ()
//{
//    for (b2Body * b = world_->GetBodyList (); b != NULL; b = b->GetNext ())
//    {
//        if (b->GetType () == b2_staticBody)
//        {
//            continue;
//        }
//        
//        PhysicsComponent & c = PhysicsComponent::b2BodyToPhysicsComponent (* b);
//        c.smoothedPosition_ = b->GetPosition ();
//        c.smoothedAngle_ = b->GetAngle ();
//    }
//}

