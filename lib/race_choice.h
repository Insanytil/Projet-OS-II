#ifndef RACE_CHOICE_H
#define RACE_CHOICE_H

#include "courses.h"
#include "event_handler.h"
#include "global.h"
#include "sdl_utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void init_course_selection();

void render_course_selection(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* buttonf_font);



int handle_course_selection_events(SDL_Event* event);

int check_is_sprint(int button_race);

#endif