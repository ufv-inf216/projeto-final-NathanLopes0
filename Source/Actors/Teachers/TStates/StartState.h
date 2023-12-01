//
// Created by User on 29/11/2023.
//

#ifndef DPIBULLETHELL_STARTSTATE_H
#define DPIBULLETHELL_STARTSTATE_H

#include "TState.h"

class StartState : public TState {

public:

    explicit StartState(FSMComponent* fsm);
    void Start() override;

    void Update(float deltaTime) override;

    void HandleStateTransition(float stateTime) override;

private:



};


#endif //DPIBULLETHELL_STARTSTATE_H
