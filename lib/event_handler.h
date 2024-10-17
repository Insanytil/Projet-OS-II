#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "button.h"

// Fonction pour gérer les événements et renvoyer l'index du bouton cliqué
int handle_event(SDL_Event* event, Button* buttons, int button_count);

#endif // EVENT_HANDLER_H
