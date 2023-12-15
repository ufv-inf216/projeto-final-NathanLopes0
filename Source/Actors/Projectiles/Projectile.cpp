//
// Created by User on 10/11/2023.
//

#include <cstddef>
#include <string>
#include "Projectile.h"

Projectile::Projectile(class Scene *scene, std::string &spritePath)
        : Actor(scene),
        mDrawSprite(nullptr),
        mColliderComponent(nullptr)

{

}

void Projectile::OnUpdate(float deltaTime) {



}