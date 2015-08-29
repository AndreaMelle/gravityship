//
//  GameScene.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__GameScene__
#define __gship__GameScene__

#include <stdio.h>
#include <memory.h>
#include "cocos2d.h"
#include "RootLayer.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "HMISystem.h"

namespace engine
{
    class GameScene : public IObject, public IUpdateLink
    {
        friend class PhysicsSystem;
    public:
        static std::shared_ptr<GameScene> Create();
        static std::weak_ptr<GameScene> CurrentGameScene();
        
        virtual ~GameScene();
        
        void load();
        void doSetup() override;
        void doTeardown() override;
        virtual void loop(float dt);
        
        cocos2d::Scene* getCCScene() { return mScene; }
        
        //std::weak_ptr<b2World> getPhysicsWorld() { return mPhysicsWorld; }
        
        cocos2d::Node* getRootTransform() { return mRootTransform; }
        void setRootTransform(cocos2d::Node* root) override { mRootTransform = root; }
        
    private:
        GameScene();
        
        // systems
        std::unique_ptr<PhysicsSystem> mPhysicsSystem;
        std::unique_ptr<HMISystem> mHMISystem;
        
        cocos2d::Scene *mScene;
        cocos2d::Node* mRootTransform;
        
        // list of all objects, useful for creation and deletion
        std::vector<GameObjectRef> mGameObjectList;
        
        //list of all objects we need to update
        std::vector<IUpdatableRef> mUpdatableList;
        
    };
    
    typedef std::shared_ptr<GameScene> GameSceneRef;
    
}

#endif /* defined(__gship__GameScene__) */
