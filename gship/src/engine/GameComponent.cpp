//
//  GameComponent.cpp
//  gship
//
//  Created by Andrea Melle on 26/08/2015.
//
//

#include "GameComponent.h"

using namespace engine;

GameComponent::GameComponent(std::weak_ptr<GameObject> gameObject)
    : mGameObject(gameObject)
{
    
}