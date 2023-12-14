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
    void Movement(float deltaTime);

private:

    bool inCenter();
    bool centeredOnce;

    void moveToCenter(float deltaTime);
};


#endif //DPIBULLETHELL_STATETWO_H
