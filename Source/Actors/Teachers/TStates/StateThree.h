//
// Created by User on 13/12/2023.
//

#ifndef DPIBULLETHELL_STATETHREE_H
#define DPIBULLETHELL_STATETHREE_H


#include "TState.h"

class StateThree : public TState {
public:

    explicit StateThree(FSMComponent * fsm);

    void Start() override;
    void Update(float deltaTime) override;
    void HandleStateTransition(float stateTimer) override;
    void Movement(float deltaTime);

private:

    bool inCenter();
    bool centeredOnce;

    void moveToCenter(float deltaTime);

};


#endif //DPIBULLETHELL_STATETHREE_H
