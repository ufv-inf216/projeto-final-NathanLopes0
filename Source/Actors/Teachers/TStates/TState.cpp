//
// Created by User on 29/11/2023.
//

#include "TState.h"
#include "../Teacher.h"
#include "../../../Components/AIComponents/FSMComponent.h"

TState::TState(FSMComponent *fsm, const std::string &name) : FSMState(fsm, name) {

    mTeacher = dynamic_cast<Teacher *>(mFSM->GetOwner());

}

void TState::Update(float deltaTime) {

}