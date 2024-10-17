#ifndef CHOICE_H
#define CHOICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void init_choice();

int handle_choice_events(SDL_Event* event);

void render_choice(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font);

void choice_save();

#endif