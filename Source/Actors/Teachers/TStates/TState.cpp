//
// Created by User on 29/11/2023.
//

#include "TState.h"
#include "../Teacher.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"

TState::TState(FSMComponent *fsm, const std::string &name) : FSMState(fsm, name), atkTimer(0), stateTime(0), soundTime(0) {

    mTeacher = dynamic_cast<Teacher *>(mFSM->GetOwner());

}

void TState::Update(float deltaTime) {

}

bool TState::DetectCollision() {
    if (mTeacher->GetGame()->p1Exists()) {
        for (auto it: mTeacher->GetGame()->GetPlayer1()->GetProjectiles()) {
            if (it->GetState() == ActorState::Active) {
                if (mTeacher->GetComponent<CircleColliderComponent>()->Intersect(*it->GetComponent<CircleColliderComponent>())) {
                    it->SetState(ActorState::Paused);
                    it->GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
                    mTeacher->extraPointCounter--;
                    return true;
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
                    return true;
                }
            }
        }
    }
    return false;
}

void TState::Attack(float deltaTime, float startAngle, float finalAngle, bool dividefocus, bool playerDirection_, float atkTimer_, int numTasks, float speed, float waitTime) {
    atkTimer -= deltaTime;
    soundTime -= deltaTime;
    if(atkTimer < 0)
    {
        float angleInterval = (finalAngle - startAngle) / (float)numTasks;
        bool playerDirection = playerDirection_;
        PlayAttackAudio();
        for(int i = 0; i < numTasks; i++)
        {
            if(dividefocus && playerDirection_) playerDirection = !playerDirection;
            if(!mTeacher->GetGame()->p1Exists()) playerDirection = false;
            float angle = startAngle + angleInterval * i;
            mTeacher->TaskCreation(angle, angle, 1, speed, playerDirection, waitTime);
        }
        atkTimer = atkTimer_;
    }
}

void TState::PlayAttackAudio()
{
    if(soundTime < 0) {
        auto audio = mTeacher->GetGame()->GetAudio();
        switch (mTeacher->GetType()) {
            case Teacher::Ricardo:
                audio->PlaySound("tan01.wav");
                break;
            case Teacher::Salles:
                audio->CacheSound("tan00.wav");
                audio->PlaySound("tan00.wav");
                break;
            default:
                break;
        }
        soundTime = 0.5;
    }
}