//
//  SpriteComponent.cpp
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#include "SpriteComponent.h"

using namespace engine;

std::shared_ptr<SpriteComponent> SpriteComponent::Create(std::weak_ptr<GameObject> gameObject,
                                                         cocos2d::Node* mParent,
                                                         const std::string& spriteName)
{
    SpriteComponentRef spriteComponent = SpriteComponentRef(new engine::SpriteComponent(gameObject));
    
    spriteComponent->mSprite = cocos2d::Sprite::create(spriteName);
    spriteComponent->mParent = mParent;
    
    return spriteComponent;
}

SpriteComponent::SpriteComponent(std::weak_ptr<GameObject> gameObject) : GameComponent(gameObject)
{
    
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::doSetup()
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    mSprite->setPosition(origin + visibleSize);
    
    mParent->addChild(mSprite, 0);
}

void SpriteComponent::start()
{
    
}

void SpriteComponent::doTeardown()
{
    if(mParent && mSprite)
    {
        mParent->removeChild(mSprite);
    }
}