//
//  GameObject.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__GameObject__
#define __gship__GameObject__

#include <stdio.h>
#include <memory>
#include <vector>
#include "GameComponent.h"

namespace engine
{
    class GameObject : public IObject
    {
    public:
        static std::shared_ptr<GameObject> Instantiate(const std::string& templateName);
        static std::shared_ptr<GameObject> Instantiate(const std::string& templateName, cocos2d::Node* root);
        
        virtual ~GameObject();
        
        void doSetup() override;
        void doTeardown() override;
        
        cocos2d::Node* getTransform() { return mTransform; }
        void updateTransform(float x, float y, float rot = 0);
        
    private:
        GameObject();
        
        std::map<std::string, GameComponentRef> mComponents; //components are unique within the object!
        
        cocos2d::Node* mTransform; //every object must have a transform
        
    };
    
    typedef std::shared_ptr<GameObject> GameObjectRef;
    typedef std::vector<GameObjectRef>::iterator GameObjectIt;
}

#endif /* defined(__gship__GameObject__) */
