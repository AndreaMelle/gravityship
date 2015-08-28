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

namespace engine
{
    class IObject
    {
    public:
        IObject() : mDidSetup(false){}
        virtual ~IObject() { teardown(); }
        
        virtual void setup()
        {
            if(mDidSetup) return;
            doSetup();
            mDidSetup = true;
        }
        
        virtual void teardown() final
        {
            if(!mDidSetup) return;
            doTeardown();
            mDidSetup = false;
        }
        
    protected:
        virtual void doSetup() = 0;
        virtual void doTeardown() = 0;
        
    private:
        bool mDidSetup;
    };
    
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
    
    class IUpdatable
    {
    public:
        virtual void update() = 0;
    };
    
    typedef std::shared_ptr<GameComponent> GameComponentRef;
    typedef std::map<std::string, GameComponentRef>::iterator GameComponentIt;
    
    typedef std::shared_ptr<IUpdatable> IUpdatableRef;
    typedef std::vector<IUpdatableRef>::iterator IUpdatableIt;
}

#endif /* defined(__gship__GameComponent__) */
