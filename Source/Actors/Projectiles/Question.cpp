//
// Created by User on 16/11/2023.
//
#include "Question.h"
#include "../../Scenes/Scene.h"
#include "../../Game.h"


Question::Question(Scene *scene, Player *owner, std::string &spritePath)
    : Projectile(scene, spritePath),
    mOwner(owner),
    mFowardSpeed(800)
{
    mDrawSprite = new DrawSpriteComponent(this, spritePath, 32, 32, 98);
    mColliderComponent = new CircleColliderComponent(this, 32);
}

void Question::OnUpdate(float deltaTime) {

    //modo dificil
    //SetPosition(GetPosition() + Vector2(0, -mFowardSpeed * deltaTime));

    //modo normal
    auto actTeacher = mScene->GetGame()->GetActiveTeacher();
    if (actTeacher != nullptr)
        SetPosition(GetPosition() + Vector2::Normalize(mScene->GetGame()->GetActiveTeacher()->GetPosition() - GetPosition()) * mFowardSpeed * deltaTime);

    if (GetPosition().y < -100) {
        SetState(ActorState::Paused);
        GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
    }
}
