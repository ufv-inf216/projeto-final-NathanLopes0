//
// Created by User on 14/11/2023.
//

#include "PowerUp.h"
#include "../Game.h"

PowerUp::PowerUp(Game *game) : Actor(game) {

    mDrawSprite = new DrawSpriteComponent(this, "../Assets/Icons/ExtraPoint.png", 32, 32, 0);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    mRigidBodyComponent->SetVelocity(Vector2(0, 200));

}

void PowerUp::OnUpdate(float deltaTime) {

    if(GetGame()->GetPlayer1()->GetState() == ActorState::Active) {
        if (GetComponent<CircleColliderComponent>()->Intersect(
                *GetGame()->GetPlayer1()->GetComponent<CircleColliderComponent>())) {

            GetGame()->GetPlayer1()->AddPontoExtra();
            SetState(ActorState::Destroy);

        }
    }

}