//
// Created by User on 16/11/2023.
//


#include "Task.h"
#include <algorithm>

Task::Task(Game *game, Teacher *owner, std::string &spritePath, float angleDirection, float fspeed, bool b, double d)
    :Projectile(game, spritePath),
    mOwner(owner),
    mFowardSpeed(fspeed),
    mDirection(angleDirection),
    playerDirection(b),
    waitTime(d)

{
    mDrawSprite = new DrawSpriteComponent(this, spritePath, 16, 16, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);


    float currVelocityX = Math::Cos(mDirection * (Math::Pi / 180)); //convertendo graus para radians e tirando sin e cos
    float currVelocityY = Math::Sin(mDirection * (Math::Pi / 180));

    mRigidBodyComponent->SetVelocity(Vector2(currVelocityX, currVelocityY) * mFowardSpeed);

    mGame->AddTask(this);
}

Task::~Task() {

}

void Task::OnUpdate(float deltaTime)  {

    if(GetPosition().y > GetGame()->GetWindowHeight() || GetPosition().y < -GetComponent<DrawSpriteComponent>()->GetSpriteHeight()
    || GetPosition().x < -GetComponent<DrawSpriteComponent>()->GetSpriteWidth() || GetPosition().x > GetGame()->GetWindowWidth())
    {
        SetState(ActorState::Destroy);
        mGame->RemoveTask(this);
    }
    if (playerDirection) {
        if (waitTime > 0) {
            waitTime -= deltaTime;
        } else {
            float currVelocityX;
            float currVelocityY;
            float angleToPlayer;

            if (GetGame()->p1Exists())
            {
                auto Ovc = Vector2(GetPosition().x, GetPosition().y);
                float Ox1 = Ovc.x;
                float Oy = Ovc.y;

                auto Pvc = GetGame()->GetPlayer1()->GetPosition();
                float Px = Pvc.x;
                float Py = Pvc.y;

                auto formula =( (Ox1 * Px) + (Oy * Py) / (Pvc.Length() * Ovc.Length()));

                angleToPlayer = acos(formula);
                currVelocityX = Math::Cos(angleToPlayer);
                currVelocityY = Math::Sin(angleToPlayer);
                SDL_Log("%f", angleToPlayer);
                mDirection = angleToPlayer * 180 / Math::Pi;

                mRigidBodyComponent->SetVelocity(Vector2(currVelocityX, -currVelocityY));
                playerDirection = false;
            }

        }
    }

}
