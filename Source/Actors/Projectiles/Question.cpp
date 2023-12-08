//
// Created by User on 16/11/2023.
//
#include "Question.h"


Question::Question(Game *game, Player *owner, std::string &spritePath)
    : Projectile(game, spritePath),
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
    SetPosition(GetPosition() + Vector2::Normalize(mGame->GetActiveTeacher()->GetPosition() - GetPosition()) * mFowardSpeed * deltaTime);

    if (GetPosition().y < -100) {
        SetState(ActorState::Paused);
        GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
    }
}
