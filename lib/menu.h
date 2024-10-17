#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Fonction pour initialiser les éléments du menu (comme les boutons)
void init_menu();

// Fonction pour gérer les événements dans le menu
int handle_menu_events(SDL_Event* event);

// Fonction pour rendre le menu (affichage)
void render_menu(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font);

#endif // MENU_H
