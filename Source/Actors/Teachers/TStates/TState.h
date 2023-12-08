//
// Created by User on 29/11/2023.
//

#ifndef DPIBULLETHELL_TSTATE_H
#define DPIBULLETHELL_TSTATE_H


#include "../../../Components/AIComponents/FSMState.h"

class TState : public FSMState {


public:

    TState(FSMComponent* fsm, const std::string& name);
    void Update(float deltaTime);
    float GetStateTime() const { return stateTime; }


protected:

    bool DetectCollision();
    void Attack(float deltaTime, float startAngle,
                float finalAngle, bool dividefocus, bool playerDirection,
                float atkTimer_, int numTasks, float speed, float waitTime);
    class Teacher* mTeacher;
    float atkTimer;
    float stateTime;
    float soundTime;
    float moveTime;
    void PlayAttackAudio();


};


#endif //DPIBULLETHELL_TSTATE_H
