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
#include "Box2D/Box2D.h"

namespace engine
{
    class GameScene : public IObject, public IUpdateLink
    {
    public:
        static std::shared_ptr<GameScene> Create();
        static std::weak_ptr<GameScene> CurrentGameScene();
        static std::weak_ptr<b2World> CurrentPhysicsWorld();
        
        virtual ~GameScene();
        
        void load();
        void doSetup() override;
        void doTeardown() override;
        virtual void loop(float dt);
        
        cocos2d::Scene* getCCScene() { return mScene; }
        cocos2d::Node* getRootTransform() { return mRootTransform; }
        std::weak_ptr<b2World> getPhysicsWorld() { return mPhysicsWorld; }
        
        void setRootTransform(cocos2d::Node* root) override { mRootTransform = root; }
        
    private:
        GameScene();
        
        cocos2d::Scene *mScene;
        std::vector<GameObjectRef> mGameObjects;
        cocos2d::Node* mRootTransform;
        std::shared_ptr<b2World> mPhysicsWorld;
        
        
    };
    
    typedef std::shared_ptr<GameScene> GameSceneRef;
    
}

#endif /* defined(__gship__GameScene__) */
