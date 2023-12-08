//
// Created by User on 01/12/2023.
//

#ifndef DPIBULLETHELL_STATEONE_H
#define DPIBULLETHELL_STATEONE_H


#include "TState.h"

class StateOne : public TState {

public:

    explicit StateOne(FSMComponent* fsm);
    void Start() override;
    void Update(float deltaTime);
    void Movement(float deltaTime);
    void HandleStateTransition(float stateTimer) override;

protected:

private:
    float mTaskSpeed;
    float stateAtkfrequency;

};


#endif //DPIBULLETHELL_STATEONE_H
