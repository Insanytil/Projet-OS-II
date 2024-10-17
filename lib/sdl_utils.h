#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Fonction pour initialiser SDL et ses sous-systèmes
int init_sdl(SDL_Window** window, SDL_Renderer** renderer, const char* title, int width, int height);

// Fonction pour nettoyer SDL et ses sous-systèmes
void cleanup_sdl(SDL_Window* window, SDL_Renderer* renderer);

// Fonction pour afficher du texte centré dans une zone
void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width);

void render_text_fond_blanc(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width);

void render_text_fond_noir(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width);
#endif // SDL_UTILS_H
