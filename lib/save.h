#ifndef SAVE_H
#define SAVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void init_save_scene();
void render_save_scene(SDL_Renderer* renderer, TTF_Font* font);
int handle_save_scene_events(SDL_Event* event);
void save_pilotes_to_file(const char* filename);



#endif