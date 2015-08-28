//
//  PhysicsComponent.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__PhysicsComponent__
#define __gship__PhysicsComponent__

#include <stdio.h>
#include "GameComponent.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 10.0f

namespace engine
{
    class PhysicsComponent : public GameComponent, public IUpdatable
    {
    public:
        static std::shared_ptr<PhysicsComponent> Create(std::weak_ptr<GameObject> gameObject);
        
        virtual ~PhysicsComponent();
        
        void doSetup() override;
        void doTeardown() override;
        
        void start() override;
        void update() override;
        
    protected:
        PhysicsComponent(std::weak_ptr<GameObject> gameObject);
        
        b2Body *mBody;
        
        std::shared_ptr<b2BodyDef> mBodyDef; //ok because copied
        std::shared_ptr<b2PolygonShape> mShape; //ok because copied
        std::shared_ptr<b2FixtureDef> mFixtureDef; //ok because copied
        
        cocos2d::DrawNode* mDebugDraw;
        
        
    };
    
    typedef std::shared_ptr<PhysicsComponent> PhysicsComponentRef;
    
}

#endif /* defined(__gship__PhysicsComponent__) */
