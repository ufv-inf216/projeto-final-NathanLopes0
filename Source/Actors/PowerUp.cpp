//
// Created by User on 14/11/2023.
//

#include "PowerUp.h"
#include "../Game.h"

PowerUp::PowerUp(Game *game) : Actor(game) {

    mDrawSprite = new DrawSpriteComponent(this, "../Assets/Icons/ExtraPoint.png", 32, 32, 99);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    mRigidBodyComponent->SetVelocity(Vector2(0, 200));

}

void PowerUp::OnUpdate(float deltaTime) {

    if(mGame->p1Exists()) {
        if (GetComponent<CircleColliderComponent>()->Intersect(
                *mGame->GetPlayer1()->GetComponent<CircleColliderComponent>())) {

            mGame->GetPlayer1()->AddPontoExtra();
            mGame->GetAudio()->PlaySound("powerup.wav");
            SetState(ActorState::Destroy);

        }
    }

}