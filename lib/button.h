#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Structure Button pour gérer les boutons dans le menu
typedef struct {
    SDL_Rect rect;     // Rectangle pour définir la taille et la position du bouton
    const char* label; // Texte affiché sur le bouton
} Button;

// Fonction pour rendre un bouton avec du texte
void render_button(SDL_Renderer* renderer, TTF_Font* font, Button* button, SDL_Color color);

#endif // BUTTON_H
