#ifndef __ROOT_LAYER_H__
#define __ROOT_LAYER_H__

#include "cocos2d.h"
#include <memory>

namespace engine
{
    class RootLayer;
    
    class IUpdateLink
    {
    public:
        virtual void loop(float dt) = 0;
        virtual void setRootTransform(cocos2d::Node* root) = 0;
    };
    
    typedef std::shared_ptr<IUpdateLink> IUpdateLinkRef;
    
    class RootLayer : public cocos2d::Layer
    {
    public:
        CREATE_FUNC(RootLayer);
        static cocos2d::Scene* createScene(IUpdateLinkRef updateLink);
        virtual bool init();
        
        void update	(float delta) override;

    private:
        IUpdateLinkRef mUpdateLink;
    };
    
    typedef std::shared_ptr<RootLayer> RootLayerRef;
    
}



#endif // __ROOT_LAYER_H__
