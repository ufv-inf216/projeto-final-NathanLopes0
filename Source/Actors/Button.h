//
// Created by User on 11/02/2024.
//

#ifndef DPIBULLETHELL_BUTTON_H
#define DPIBULLETHELL_BUTTON_H

#include <string>
#include "Actor.h"

class Button : public Actor{

public:
    Button(class Scene* scene, std::string& spritepath, std::string& subjectCode);
    void OnUpdate(float deltaTime) override;
    void changeSelected() {selected = !selected;}
    bool isSelected() {return selected;}
private:
    bool selected;
    int width, height;
    class Font* mFont;
    class DrawSpriteWColorEffect* mDrawComponent;
    class DrawTextComponent* mDrawTextComponent;

    void SetButtonText(std::string &newText);
};


#endif //DPIBULLETHELL_BUTTON_H
