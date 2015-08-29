//
//  GameComponent.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__GameComponent__
#define __gship__GameComponent__

#include <stdio.h>
#include <memory>
#include "commons/Interfaces.h"

namespace engine
{
    class GameObject;
    
    class GameComponent : public IObject
    {
    public:
        virtual void start() = 0;
        
    private:
        GameComponent() = delete;

        
    protected:
        GameComponent(std::weak_ptr<GameObject> gameObject);
        
        std::weak_ptr<GameObject> mGameObject;
        
    };
    
    typedef std::shared_ptr<GameComponent> GameComponentRef;
    typedef std::map<std::string, GameComponentRef>::iterator GameComponentIt;
}

#endif /* defined(__gship__GameComponent__) */
