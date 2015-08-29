//
//  Interfaces.h
//  gship
//
//  Created by Andrea Melle on 28/08/2015.
//
//

#ifndef gship_Interfaces_h
#define gship_Interfaces_h

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
    
    class IUpdatable
    {
    public:
        virtual void update(float dt) = 0;
    };
    
    class IFixedUpdatable
    {
    public:
        virtual void fixedUpdate(float dt) = 0;
    };

    class ICollidable
    {
    public:
        virtual void onCollision() = 0; //todo we need collision arguments, but I don't know what it is yet
    };
    
    typedef std::shared_ptr<IUpdatable> IUpdatableRef;
    typedef std::vector<IUpdatableRef>::iterator IUpdatableIt;
    
    typedef std::shared_ptr<IFixedUpdatable> IFixedUpdatableRef;
    typedef std::vector<IFixedUpdatableRef>::iterator IFixedUpdatableIt;
    
    typedef std::shared_ptr<ICollidable> ICollidableRef;
    typedef std::vector<ICollidableRef>::iterator ICollidableIt;
}


#endif
