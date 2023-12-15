//
// Created by User on 10/11/2023.
//

#ifndef DPIBULLETHELL_PROJECTILE_H
#define DPIBULLETHELL_PROJECTILE_H

#include <cstddef>
#include <string>
#include "../Actor.h"
#include "../Player.h"
#include "../Teachers/Teacher.h"
#include "../../Components/ColliderComponents/CircleColliderComponent.h"


class Projectile : public Actor {

public:


    Projectile(class Scene* scene, std::string &spritePath);


protected:

    void OnUpdate(float deltaTime) override;

    class DrawSpriteComponent* mDrawSprite;
    class CircleColliderComponent* mColliderComponent;

private:


};


#endif //DPIBULLETHELL_PROJECTILE_H
