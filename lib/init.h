#ifndef INIT_H
#define INIT_H

#include "pilote.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Déclaration de la fonction pour charger les pilotes depuis un fichier
void chargement_pilotes(const char* filenom, Pilote pilotes[],int* compteur_pilote);

// Déclaration de la fonction pour rendre la scène INIT
void render_init(SDL_Renderer* renderer, TTF_Font* text_font, TTF_Font* button_font);

// Déclaration de la fonction pour initialiser la scène INIT
void init_championnat();

int handle_init_events(SDL_Event* event);
#endif  // INIT_H
