//
// Created by User on 01/12/2023.
//

#include "StateOne.h"
#include "../Teacher.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"

StateOne::StateOne(FSMComponent *fsm)
    : TState(fsm, "stateOne"),
    atkTimer(0)
{

}

void StateOne::Start() {

    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);

}

void StateOne::Update(float deltaTime) {

    stateTime += deltaTime;

    Movement();
    atkTimer -= deltaTime;
    if (atkTimer < 0)
    {
        int numTasks = 40;
        float startAngle = 0;
        float finalAngle = 360;
        float angleInterval = (finalAngle - startAngle) / (float)numTasks;
        bool pD = false;
        for (int i = 0; i < numTasks; i++) {
            pD = !pD;
            if (!mTeacher->GetGame()->p1Exists()) pD = false;
            mTeacher->TaskCreation(startAngle + angleInterval * i, startAngle + angleInterval * i,
                                   1, 250, pD, 1);
        }
        atkTimer = 1;
    }
    DetectCollision();

}

void StateOne::Movement()
{
    float border = 128;
    int randNum = Random::GetIntRange(0, 99);
    if(mTeacher->left)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150, 0));
        if(randNum > 98) {
            mTeacher->right = true;
            mTeacher->left = false;
        }
    } else if(mTeacher->right)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
        if(randNum > 98) {
            mTeacher->right = false;
            mTeacher->left = true;
        }
    }

    if (mTeacher->GetPosition().x > (float)mTeacher->GetGame()->GetGameWindowWidth() - border || mTeacher->GetPosition().x < border) {
        if(mTeacher->left) mTeacher->SetPosition(Vector2(mTeacher->GetPosition().x + (float)mTeacher->GetSpriteWidth() / 6, mTeacher->GetPosition().y));
        if(mTeacher->right) mTeacher->SetPosition(Vector2(mTeacher->GetPosition().x - (float)mTeacher->GetSpriteWidth() / 6, mTeacher->GetPosition().y));
        mTeacher->left = !mTeacher->left;
        mTeacher->right = !mTeacher->right;
    }

}
void StateOne::DetectCollision() {
    if (mTeacher->GetGame()->p1Exists()) {
        for (auto it: mTeacher->GetGame()->GetPlayer1()->GetProjectiles()) {
            if (it->GetState() == ActorState::Active) {
                if (mTeacher->GetComponent<CircleColliderComponent>()->Intersect(*it->GetComponent<CircleColliderComponent>())) {
                    it->SetState(ActorState::Paused);
                    it->GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
                    mTeacher->extraPointCounter--;
                    break;
                }
            }
        }
    }
    if (mTeacher->GetGame()->p2Exists()) {
        for (auto it: mTeacher->GetGame()->GetPlayer2()->GetProjectiles()) {
            if (it->GetState() == ActorState::Active) {
                if (mTeacher->GetComponent<CircleColliderComponent>()->Intersect(*it->GetComponent<CircleColliderComponent>())) {
                    it->SetState(ActorState::Destroy);
                    mTeacher->extraPointCounter--;
                    break;
                }
            }
        }
    }
}



void StateOne::HandleStateTransition(float stateTimer) {

    if (stateTimer > 30)
    {
        mFSM->SetState("stateTwo");
    }
}

