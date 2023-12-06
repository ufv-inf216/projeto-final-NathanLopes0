//
// Created by User on 06/12/2023.
//

#ifndef DPIBULLETHELL_STATETWO_H
#define DPIBULLETHELL_STATETWO_H


#include "TState.h"

class StateTwo : public TState{

public:
    explicit StateTwo(FSMComponent* fsm);

    void Start() override;
    void Update(float deltaTime) override;
    void HandleStateTransition(float stateTimer) override;
    void Movement();

private:

    float atkTimer;

    bool inCenter();

    void moveToCenter();
};


#endif //DPIBULLETHELL_STATETWO_H
