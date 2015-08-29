//
//  PhysicsSystem.h
//  gship
//
//  Created by Andrea Melle on 28/08/2015.
//
//

#ifndef __gship__PhysicsSystem__
#define __gship__PhysicsSystem__

#include <stdio.h>
#include "GameComponent.h"
#include "PhysicsComponent.h"
#include "Box2D/Box2D.h"
#include <memory>

#define PTM_RATIO 10.0f

namespace engine
{
    class PhysicsSystem : public IObject, public IUpdatable
    {
    public:
        static std::shared_ptr<PhysicsComponent> Create(std::weak_ptr<GameObject> gameObject);
        
        PhysicsSystem();
        ~PhysicsSystem();
        
        static PhysicsSystem* GetCurrent();
        
        void update(float dt) override;
        void lateUpdate(float dt);// override;
        
        void remove(PhysicsComponentRef pc);
        
    protected:
        void doSetup() override;
        void doTeardown() override;
        
    private:
        
        static const float FIXED_TIMESTEP;
        static const int MAX_STEPS;
        
        int32 mVelocityIterations;
        int32 mPositionIterations;
        
        float mFixedTimestepAccumulator;
        float mFixedTimestepAccumulatorRatio;
        
        std::shared_ptr<b2World> mPhysicsWorld;
        
        void singleStep(float dt);
        
        void smoothStates();
        void resetSmoothStates();
        
        void callFixedUpdates(float dt);
        void consumeContacts();
        
        //all the physics components
        std::vector<IFixedUpdatableRef> mFixedUpdatableList;
        
        //list of all objects we need to call custom fixedUpdate(float dt)
        std::vector<PhysicsComponentRef> mPhysicsComponentList;
        
        //list of all objects registered for collision callback
        std::vector<ICollidableRef> mCollidableList;
        
        // no need to keep list of objects registered for physics or animation -> they are in the b2World!
    };
    
    //typedef std::shared_ptr<PhysicsSystem> PhysicsSystemRef;
    
}


#endif /* defined(__gship__PhysicsSystem__) */
