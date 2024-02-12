//
// Created by User on 14/12/2023.
//

#ifndef DPIBULLETHELL_STAGESELECT_H
#define DPIBULLETHELL_STAGESELECT_H

#include "Scene.h"

class StageSelect : public Scene {
public:
    StageSelect(class Game* game);
    void Load() override;
    void ProcessInput(const Uint8* keyState) override;

private:
    class Font* mStageSelectFont;
    std::vector<class Button*> button;
    int mButtonSelected, numMat, mTimer;


};


#endif //DPIBULLETHELL_STAGESELECT_H
