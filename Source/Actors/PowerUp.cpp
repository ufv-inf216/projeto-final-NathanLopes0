//
// Created by User on 14/11/2023.
//

#include "PowerUp.h"
#include "../Game.h"
#include "../Components/RigidBodyComponent.h"
#include "../Scenes/Scene.h"

PowerUp::PowerUp(Scene *scene) : Actor(scene) {

    mDrawSprite = new DrawSpriteComponent(this, "../Assets/Icons/ExtraPoint.png", 32, 32, 99);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    mRigidBodyComponent->SetVelocity(Vector2(0, 200));

}

void PowerUp::OnUpdate(float deltaTime) {

        if (GetComponent<CircleColliderComponent>()->Intersect(
                *mScene->GetPlayer()->GetComponent<CircleColliderComponent>())) {

            mScene->GetPlayer()->AddPontoExtra();
            SetState(ActorState::Destroy);

        }
}