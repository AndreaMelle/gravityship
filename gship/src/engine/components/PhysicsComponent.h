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

namespace engine
{
    class PhysicsComponent
        : public GameComponent
        , public IUpdatable
        , public std::enable_shared_from_this<PhysicsComponent>
    {
        friend class PhysicsSystem;
        
    public:
        virtual ~PhysicsComponent();
        
        void doSetup() override;
        void doTeardown() override;
        
        void start() override;
        void update(float dt) override;
        
        b2Body *mBody;
        
        b2Vec2 mSmoothedPosition;
        float mSmoothedAngle;
        
        b2Vec2 mPreviousPosition;
        float mPreviousAngle;
        
    protected:
        PhysicsComponent(std::weak_ptr<GameObject> gameObject);
        
        std::shared_ptr<b2BodyDef> mBodyDef; //ok because copied
        std::shared_ptr<b2PolygonShape> mShape; //ok because copied
        std::shared_ptr<b2FixtureDef> mFixtureDef; //ok because copied
        
        cocos2d::DrawNode* mDebugDraw;
        
        
    };
    
    typedef std::shared_ptr<PhysicsComponent> PhysicsComponentRef;
    
    inline cocos2d::Vec2 fromBox2D(const b2Vec2& v, float scale = 1.0f)
    {
        return (cocos2d::Vec2(v.x, v.y) * scale);
    }
    
}

#endif /* defined(__gship__PhysicsComponent__) */
