//
// Created by User on 16/11/2023.
//


#include "Task.h"
#include <algorithm>

Task::Task(Game *game, Teacher *owner, std::string &spritePath, float angleDirection, float fspeed)
    :Projectile(game, spritePath),
    mOwner(owner),
    mFowardSpeed(fspeed),
    mDirection(angleDirection)

{
    mDrawSprite = new DrawSpriteComponent(this, spritePath, 16, 16, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    float currVelocityX = Math::Cos(mDirection * (Math::Pi / 180)); //convertendo graus para radians e tirando sin e cos
    float currVelocityY = Math::Sin(mDirection * (Math::Pi / 180));

    mRigidBodyComponent->SetVelocity(Vector2(currVelocityX, currVelocityY) * mFowardSpeed);

    //mGame->AddTask(this);
}

Task::~Task() {

}

void Task::OnUpdate(float deltaTime)  {

    if(GetPosition().y > GetGame()->GetWindowHeight() || GetPosition().y < -GetComponent<DrawSpriteComponent>()->GetSpriteHeight()
    || GetPosition().x < -GetComponent<DrawSpriteComponent>()->GetSpriteWidth() || GetPosition().x > GetGame()->GetWindowWidth())
    {
        SetState(ActorState::Destroy);
    }

}
