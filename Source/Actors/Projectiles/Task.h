//
// Created by User on 16/11/2023.
//

#ifndef DPIBULLETHELL_TASK_H
#define DPIBULLETHELL_TASK_H

#include "Projectile.h"
#include "../../Components/RigidBodyComponent.h"
#include "../Teachers/Teacher.h"

class Task : public Projectile {

public:

    Task(class Scene *scene, Teacher *owner, std::string &spritePath, float angleDirection, float fspeed, bool playerDirection, double waitTime);
    ~Task();

    Teacher * GetOwner() { return mOwner; }
    float GetSpeed() { return mFowardSpeed; }
    float GetAngle() { return mDirection; }
    void SetSpeed (float newSpeed) { mFowardSpeed = newSpeed; }
    void SetAngle (int newAngle) { mDirection = (float) (newAngle % 360); }


private:

    float mDirection;
    float mFowardSpeed;
    class Teacher * mOwner;
    RigidBodyComponent * mRigidBodyComponent;


    void OnUpdate(float deltaTime);

    bool playerDirection;
    double waitTime;
};


#endif //DPIBULLETHELL_TASK_H
