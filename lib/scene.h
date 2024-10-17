#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>   

// Enum pour définir les différentes scènes du simulateur
typedef enum {
    SCENE_MENU,             // Menu principal
    SCENE_INIT,        // Simulation de course
    SCENE_CHOICE,         // Affichage des résultats
    SCENE_RESULT,   // Fin de championnat
    SCENE_LOAD_SAVE,         // Ajout de la scène pour charger une sauvegarde
    SCENE_RACE_CHOICE,      // interface de sélection de la course
    SCENE_PRACTICE_CLASSIC,         // interface de simulation des practices
    SCENE_PRACTICE_SPRINT,          // interface de simulation des practices (weekend sprint)
    SCENE_CONTINUE_TO_QUALIF, // interface de demande de continuation vers les qualifs
    SCENE_CONTINUE_TO_QUALIF_SPRINT, // interface de demande de continuation vers les qualifs du sprint
    SCENE_CONTINUE_TO_SPRINT, // interfce de demande de continuation vers le sprint
    SCENE_CONTNUE_TO_RACE, // interface de demande de continuation vers la course
    SCENE_QUALIF, // interface de simulation des qualifs
    SCENE_QUALIF_SPRINT, // interface de simulation des qualifs du sprint
    SCENE_SPRINT,  // interface de simulation du sprint
    SCENE_RACE, // interface de simulation de la course
    SCENE_QUIT,              // Quitter le simulateur
} SceneType;

// Prototypes des fonctions
void init_scene(SceneType scene);
SceneType update_scene(SceneType current_scene, SDL_Event* event);
void render_scene(SceneType scene, SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font, TTF_Font* text_font);

#endif // SCENE_H
