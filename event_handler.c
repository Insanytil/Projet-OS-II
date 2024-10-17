#include "lib/event_handler.h"

int handle_event(SDL_Event* event, Button* buttons, int button_count) {
    //  Permet de vérifier si un événement de clic de souris est détecté
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;  // Position x du clic
        int y = event->button.y;  // Position y du clic

        
        for (int i = 0; i < button_count; ++i) {
            if (x >= buttons[i].rect.x && x <= buttons[i].rect.x + buttons[i].rect.w &&
                y >= buttons[i].rect.y && y <= buttons[i].rect.y + buttons[i].rect.h) {
                return i;  // Retourner l'index du bouton cliqué
            }
        }
    }
    return -1;
}
