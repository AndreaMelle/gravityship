//
//  SpriteComponent.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__SpriteComponent__
#define __gship__SpriteComponent__

#include <stdio.h>
#include "GameComponent.h"

namespace engine
{
    class SpriteComponent : public GameComponent
    {
    public:
        static std::shared_ptr<SpriteComponent> Create(std::weak_ptr<GameObject> gameObject,
                                                       cocos2d::Node* mParent,
                                                       const std::string& spriteName);
        
        virtual ~SpriteComponent();
        
        void doSetup() override;
        void doTeardown() override;
        
        void start() override;
        
        cocos2d::Node* getTransform() { return mSprite; }
        
    protected:
        SpriteComponent(std::weak_ptr<GameObject> gameObject);
        
        cocos2d::Node* mParent;
        cocos2d::Sprite *mSprite;
        
    };
    
    typedef std::shared_ptr<SpriteComponent> SpriteComponentRef;
    
}

#endif /* defined(__gship__SpriteComponent__) */
