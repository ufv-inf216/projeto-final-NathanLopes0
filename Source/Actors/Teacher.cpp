//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include <string>
#include "Teacher.h"
#include "Projectiles/Question.h"
#include "Projectiles/Task.h"

Teacher::Teacher(Game *game, Type type)
    :Actor(game),
    mType(type),
    left(true),
    right(false),
    extraPointCounter(10),
    atkTimer(2)

{

    std::string prefix = "../Assets/Teachers/";
    switch(mType)
    {
        case Ricardo:
            prefix += "DPIBHRicardoStartPrototype";
            break;
        case Salles:
            prefix += "DPIBHSallesStartPrototypeScaled";
            break;
        default:
            SDL_Log("Teacher Sprite doesn't exist");
            break;
    }

    mDrawSprite = new DrawSpriteComponent(this, prefix + ".png", 128, 128, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 32);

}

void Teacher::OnUpdate(float deltaTime) {

    atkTimer -= deltaTime;
    if(atkTimer < 0)
    {
        TaskCreation(0.f, 360.f, 0.4f);
        atkTimer = 1;
    }

    if (GetGame()->p1Exists()) {
        for (auto it: GetGame()->GetPlayer1()->GetProjectiles()) {
            if (it->GetState() == ActorState::Active) {
                if (mColliderComponent->Intersect(*it->GetComponent<CircleColliderComponent>())) {
                    it->SetState(ActorState::Paused);
                    it->GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
                    extraPointCounter--;
                    break;
                }
            }
        }
    }

    if (GetGame()->p2Exists()) {
        for (auto it: GetGame()->GetPlayer2()->GetProjectiles()) {
            if (it->GetState() == ActorState::Active) {
                if (mColliderComponent->Intersect(*it->GetComponent<CircleColliderComponent>())) {
                    it->SetState(ActorState::Destroy);
                    extraPointCounter--;
                    break;
                }
            }
        }
    }

    if (extraPointCounter <= 0)
    {
        CreateExtraPoint();
        //mudar para 80 depois, 40 apenas para mostrar/debug
        extraPointCounter = 40;
        GetGame()->GetAudio()->PlaySound("extraPt.wav");
    }

    //Apenas para teste/melhor visualização. Movimento do Teacher
//    float border = 128;
//    int randNum = Random::GetIntRange(0, 99);
//    if(left)
//    {
//        GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150, 0));
//        if(randNum > 98) {
//            right = true;
//            left = false;
//        }
//    } else if(right)
//    {
//        GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
//        if(randNum > 98) {
//            right = false;
//            left = true;
//        }
//    }
//
//    if (GetPosition().x > (float)GetGame()->GetWindowWidth() - border || GetPosition().x < border) {
//        if(left) SetPosition(Vector2(GetPosition().x + (float)GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 8, GetPosition().y));
//        if(right) SetPosition(Vector2(GetPosition().x - (float)GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 8, GetPosition().y));
//        left = !left;
//        right = !right;
//    }

}

void Teacher::CreateExtraPoint() {
    auto point = new PowerUp(mGame);
    point->SetPosition(GetPosition() + Vector2(0, 64));
}


void Teacher::TaskCreation(float startAngle, float finalAngle, float frequency) {

    std::string spritePath = "../Assets/Icons/PlaceholderTask.png";
    float difAngle = finalAngle - startAngle;
    int numTasks = (difAngle * frequency); //numero de Tasks necessárias para preencher o intervalo inteiro, de acordo com a frequencia
    std::clamp(numTasks, 1, 360);
    float angleDifference = difAngle / numTasks;


    for (int i = 0; i < numTasks; i++)
    {
        auto task = new Task(GetGame(), this, spritePath, (-startAngle - i * (angleDifference)), 400);
        task->SetPosition(GetPosition());
    }

}