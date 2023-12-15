//
// Created by User on 14/11/2023.
//

#ifndef DPIBULLETHELL_POWERUP_H
#define DPIBULLETHELL_POWERUP_H

#include "Actor.h"
#include "Player.h"

class PowerUp : public Actor {
public:
    PowerUp(Scene * scene);
    void OnUpdate(float deltaTime) override;

private:

    class DrawSpriteComponent* mDrawSprite;
    class CircleColliderComponent* mColliderComponent;
    class RigidBodyComponent* mRigidBodyComponent;
};


#endif //DPIBULLETHELL_POWERUP_H
