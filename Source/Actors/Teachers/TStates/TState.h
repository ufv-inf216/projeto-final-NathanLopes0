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


protected:

    class Teacher* mTeacher;
    float stateTime;

};


#endif //DPIBULLETHELL_TSTATE_H
