//
//  HMISystem.h
//  gship
//
//  Created by Andrea Melle on 28/08/2015.
//
//

#ifndef __gship__HMISystem__
#define __gship__HMISystem__

#include <stdio.h>
#include "GameComponent.h"
#include <memory>

namespace engine
{
    class HMISystem : public IObject, public IUpdatable
    {
    public:
        HMISystem();
        virtual ~HMISystem();
        
        void update(float dt) override;
        
        std::map<std::string, bool> m
        
    private:
        
        void doSetup() override;
        void doTeardown() override;
        
    };
    
    //typedef std::shared_ptr<HMISystem> HMISystemRef;
    
}

#endif /* defined(__gship__HMISystem__) */
