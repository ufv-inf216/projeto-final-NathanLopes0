//
// Created by User on 14/12/2023.
//

#ifndef DPIBULLETHELL_MAINMENU_H
#define DPIBULLETHELL_MAINMENU_H

#include "Scene.h"

class MainMenu : public Scene {

public:
    explicit MainMenu(class Game * game);

    void Load() override;
    void ProcessInput(const Uint8* keyState) override;

private:
    class Font* mMainMenuFont;

};


#endif //DPIBULLETHELL_MAINMENU_H
