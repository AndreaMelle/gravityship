//
//  TemplateManager.h
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#ifndef __gship__TemplateManager__
#define __gship__TemplateManager__

#include <stdio.h>
#include "external/json/rapidjson.h"

namespace engine
{
    class TemplateManager
    {
    public:
        static TemplateManager& getInstance()
        {
            static TemplateManager instance;
            return instance;
        }
        
    private:
        TemplateManager() {};
        
        TemplateManager(TemplateManager const&)               = delete;
        void operator=(TemplateManager const&)  = delete;
        
    };
    
    struct SpriteComponentTemplate
    {
        std::string spriteName; //mandatory
        float x; //optional initial position x
        float y; //optional initial position y
        // etc... scale, rotation...
    };
    
    
    
}

#endif /* defined(#define __gship__TemplateManager__) */
