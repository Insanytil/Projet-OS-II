#ifndef SCORE_H
#define SCORE_H

#include "pilote.h"
#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void init_score_scene();

void copy_drivers(Pilote source[], Pilote dest[], int compteur_pilote);

void sort_drivers_from_copy(Pilote temp_pilotes[], int compteur_pilote);




void render_score_scene(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_text, TTF_Font* text_font);

int handle_score_events(SDL_Event* event);
#endif