#include "RootLayer.h"

USING_NS_CC;

using namespace engine;

Scene* RootLayer::createScene(IUpdateLinkRef updateLink)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object - static factory method calls init immediately!
    RootLayer* layer = RootLayer::create();
    
    layer->mUpdateLink = updateLink;
    updateLink->setRootTransform(layer);
    
    scene->addChild(layer);
    
    layer->scheduleUpdate();
    
    return scene;
}

// on "init" you need to initialize your instance
bool RootLayer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    return true;
}

void RootLayer::update(float delta)
{
    mUpdateLink->loop(delta);
}