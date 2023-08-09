#include "button.h"
void Button::is_pressed(Vector2i mousePosition, Event event) {
    if (mousePosition.x >= posX && mousePosition.x <= posX + Ancho && mousePosition.y >= posY && mousePosition.y <= posY + Alto && estado == false) {
        if (event.type == Event::MouseButtonPressed && !lock) {
            estado = true;
        }
        spr.setScale(1 + 0.01f, 1 + 0.01f);
        spr.setPosition(posX - 1.5, posY - 1.5);
    }
    else {
        spr.setScale(1, 1);
        spr.setPosition(posX, posY);
    }
}
