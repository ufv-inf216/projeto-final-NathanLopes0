//
// Created by User on 29/11/2023.
//

#ifndef DPIBULLETHELL_TSTATE_H
#define DPIBULLETHELL_TSTATE_H


#include "../../../Components/AIComponents/FSMState.h"
#include <vector>

class TState : public FSMState {


public:

    TState(FSMComponent* fsm, const std::string& name);
    void Update(float deltaTime);
    float GetStateTime() const { return stateTime; }


protected:

    bool DetectCollision();
    std::vector<class Task *> Attack(float deltaTime, float startAngle,
                               float finalAngle, bool dividefocus, bool playerDirection,
                               float atkTimer_, int numTasks, float speed, float waitTime);
    class Teacher* mTeacher;

    //how much the boss atacks
    float atkTimer;

    //how much time has passed from the start of the State
    float stateTime;

    //new sound add control variable
    float soundTime;

    //movement change control variable
    float moveTime;

    //variables for the Attack
    float mTaskSpeed;
    float stateAtkfrequency;

    void PlayAttackAudio();


};


#endif //DPIBULLETHELL_TSTATE_H
