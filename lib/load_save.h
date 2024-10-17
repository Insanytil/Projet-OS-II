#ifndef LOAD_SAVE_H
#define LOAD_SAVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define MAX_SAVES 10

extern char* saves[MAX_SAVES];

// Fonction pour initialiser la scène de chargement de sauvegarde
void init_load_save();

// Fonction pour gérer les événements (sélection des sauvegardes)
int handle_load_save_events(SDL_Event* event);

// Fonction pour rendre l'interface de chargement de sauvegarde
void render_load_save(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font);

#endif // LOAD_SAVE_H
