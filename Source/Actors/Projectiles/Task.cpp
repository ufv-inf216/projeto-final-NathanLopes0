//
// Created by User on 16/11/2023.
//


#include "Task.h"
#include <algorithm>
#include "../../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../../Scenes/Scene.h"
#include "../../Game.h"

Task::Task(Scene *scene, Teacher *owner, std::string &spritePath, float angleDirection, float fspeed, bool b, double d)
    :Projectile(scene, spritePath),
    mOwner(owner),
    mFowardSpeed(fspeed),
    mDirection(angleDirection),
    playerDirection(b),
    waitTime(d)

{
    mDrawSprite = new DrawSpriteWColorEffect(this, spritePath, 32, 32, 97);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, GetComponent<DrawSpriteWColorEffect>()->GetSpriteWidth() / 2);


    float currVelocityX = Math::Cos(mDirection * (Math::Pi / 180)); //convertendo graus para radians e tirando sin e cos
    float currVelocityY = Math::Sin(mDirection * (Math::Pi / 180));

    mRigidBodyComponent->SetVelocity(Vector2(currVelocityX, currVelocityY) * mFowardSpeed);

    mScene->GetGame()->AddTask(this);
}

Task::~Task() {

}

void Task::OnUpdate(float deltaTime)  {

    if(GetPosition().y > mScene->GetGame()->GetWindowHeight() || GetPosition().y < -GetComponent<DrawSpriteWColorEffect>()->GetSpriteHeight()
    || GetPosition().x < -GetComponent<DrawSpriteWColorEffect>()->GetSpriteWidth() || GetPosition().x > mScene->GetGame()->GetWindowWidth())
    {
        SetState(ActorState::Destroy);
        mScene->GetGame()->RemoveTask(this);
    }
    if (playerDirection) {
        if (waitTime > 0) {
            waitTime -= deltaTime;
        } else {
            auto dTP = mScene->GetPlayer()->directionToPlayer(this);
            mRigidBodyComponent->SetVelocity(dTP * mFowardSpeed);
            playerDirection = false;
        }
    }
}
