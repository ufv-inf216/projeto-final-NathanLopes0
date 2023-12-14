//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include <string>
#include <iostream>
#include "Teacher.h"
#include "../Projectiles/Question.h"
#include "../Projectiles/Task.h"
#include "../../Components/AIComponents/FSMComponent.h"
#include "TStates/StartState.h"
#include "TStates/StateOne.h"
#include "TStates/StateTwo.h"
#include "TStates/StateThree.h"

Teacher::Teacher(Game *game, Type type)
    :Actor(game),
    mType(type),
    left(true),
    right(false),
    extraPointCounter(20)

{

    std::string prefix = "../Assets/Teachers/";
    //escolher a sprite de acordo com o tipo
    switch(mType)
    {
        case Ricardo:
            prefix += "DPIBHRicardoStartPrototype";
            break;
        case Salles:
            prefix += "DPIBHSallesStartPrototypeScaled";
            break;
        case Andre:
            prefix += "DPIBHAndrePrototype";
            break;
        default:
            SDL_Log("Teacher Sprite doesn't exist");
            break;
    }


    mGame->AddTeacher(this);
    //componentes
    mDrawSprite = new DrawSpriteComponent(this, prefix + ".png", 128, 128, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 32);

    //colocando os estados
    mFSMComponent = new FSMComponent(this);
    new StartState(mFSMComponent);
    new StateOne(mFSMComponent);
    new StateTwo(mFSMComponent);
    new StateThree(mFSMComponent);

}

void Teacher::Start() {
    mFSMComponent->Start("start");
}

void Teacher::OnUpdate(float deltaTime) {

    if (extraPointCounter <= 0)
    {
        CreateExtraPoint();

        extraPointCounter = Random::GetIntRange(40, 80);
        GetGame()->GetAudio()->PlaySound("kira00.wav");
    }

    if (!mGame->p1Exists()) mGame->Shutdown();
}

void Teacher::CreateExtraPoint() {
    auto point = new PowerUp(mGame);
    point->SetPosition(GetPosition() + Vector2(0, 64));
}

Task * Teacher::TaskCreation(float startAngle, float finalAngle, int numTasks, float speed, bool playerDirection, double waitTime) {

    std::string spritePath;
    switch (GetType())
    {
        
        case Type::Ricardo:
            spritePath = "../Assets/Teachers/Projectiles/DPIBHArduinoPrototype2.png";
            break;
        case Type::Salles:
            spritePath = "../Assets/Teachers/Projectiles/Capivara.png";
            break;
        default:
            spritePath = "../Assets/Icons/PlaceholderTask.png";
            break;

    }
    std::vector<Task*> allTasks;
    float difAngle = finalAngle - startAngle;
    float angleDifference;
    if (difAngle >= 0)
        angleDifference = difAngle / (numTasks + 1);
    else
        angleDifference = (difAngle + 360) / (numTasks + 1);

    for (int i = 0; i < numTasks; i++) {

        float currAngle = -startAngle - (angleDifference * (i + 1));
        auto task = new Task(GetGame(), this, spritePath, currAngle, speed, playerDirection, waitTime);
        task->SetPosition(GetPosition());
        return task;
    }
}