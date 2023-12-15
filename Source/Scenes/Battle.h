//
// Created by User on 14/12/2023.
//

#ifndef DPIBULLETHELL_BATTLE_H
#define DPIBULLETHELL_BATTLE_H

#include "Scene.h"

class Battle : public Scene {

public:
    explicit Battle(class Game* game);
    void Load() override;

    class Teacher * GetActiveTeacher() override;
    class Player* GetPlayer() override;
private:

    class Player * mPlayer;
    class Teacher * mActiveTeacher;
    class LimiterMenu* mLimiterMenu;


    void ProcessInput(const Uint8 *keyState);

    LimiterMenu *GetLimiterMenu();
};


#endif //DPIBULLETHELL_BATTLE_H
