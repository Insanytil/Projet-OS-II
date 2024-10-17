#include "lib/sdl_utils.h"
#include "lib/scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Pour SDL_ttf
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Initialisation de SDL
    if (init_sdl(&window, &renderer, "Simulateur de championnat F1", WINDOW_WIDTH, WINDOW_HEIGHT) < 0) {
        return EXIT_FAILURE;
    }

    // Initialiser SDL_image pour charger les images (comme celle du background)
    if (IMG_Init(IMG_INIT_JPG) == 0) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }

    // Charger l'image de fond (utilisée dans toutes les scènes sauf la simulation)
    SDL_Surface* bg_surface = IMG_Load("ressources/background.jpg");
    if (!bg_surface) {
        printf("Erreur lors du chargement de l'image de fond : %s\n", IMG_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }
    SDL_Texture* bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    // Initialisation de SDL_mixer pour gérer le son
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer : %s\n", Mix_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }

    // Charger la musique de fond (Racing-Spirit.mp3)
    Mix_Music* music = Mix_LoadMUS("ressources/Racing_Spirit.mp3");
    if (!music) {
        printf("Erreur lors du chargement de la musique : %s\n", Mix_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }

    // Charger le son des clics de boutons (bouton.wav)
    Mix_Chunk* click_sound = Mix_LoadWAV("ressources/bouton.wav");
    if (!click_sound) {
        printf("Erreur lors du chargement du son : %s\n", Mix_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }

    // Charger la police
    TTF_Font* button_font = TTF_OpenFont("ressources/arial.ttf", 24); // Assurez-vous de spécifier le bon chemin
    if (!button_font) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        cleanup_sdl(window, renderer);
        return EXIT_FAILURE;
    }
    

    TTF_Font* title_font = TTF_OpenFont("ressources/arial.ttf", 35);
    if (!title_font) {
        printf("Erreur lors du chargement de la police Title");
    }

    TTF_Font* text_font = TTF_OpenFont("ressources/arial.ttf", 17);
    if (!text_font) {
        printf("Erreur lors du chargement de la police texte");
    }

    TTF_SetFontStyle(title_font, TTF_STYLE_BOLD);
    TTF_SetFontStyle(text_font, TTF_STYLE_BOLD);
    TTF_SetFontStyle(button_font, TTF_STYLE_BOLD);
    // Initialisation de la scène
    SceneType current_scene = SCENE_MENU;  // Commence avec le menu principal
    init_scene(current_scene);  // Initialiser la scène du menu
    Mix_PlayMusic(music, -1);   // Jouer la musique en boucle dans le menu

    bool running = true;
    SDL_Event event;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Mettre à jour la scène actuelle en fonction des événements
            SceneType new_scene = update_scene(current_scene, &event);

            // Si la scène a changé
            if (new_scene != current_scene) {

                // Si on passe entre SCENE_MENU et SCENE_LOAD_SAVE ou SCENE_INIT cela permet de ne pas arrêter la musique
                if (!((current_scene == SCENE_LOAD_SAVE || current_scene == SCENE_MENU || current_scene == SCENE_INIT) &&
                      (new_scene == SCENE_LOAD_SAVE || new_scene == SCENE_MENU || new_scene == SCENE_INIT))) {
                    Mix_HaltMusic();  // Arrêter la musique si on quitte une de ces scènes pour une autre non comprise 
                }

                // Si on entre dans SCENE_MENU ou SCENE_LOAD_SAVE, jouer la musique
                if ((new_scene == SCENE_MENU || new_scene == SCENE_LOAD_SAVE || new_scene == SCENE_INIT) && !Mix_PlayingMusic() ) {
                    Mix_PlayMusic(music, -1);
                }

                // Initialiser la nouvelle scène
                init_scene(new_scene);
                current_scene = new_scene;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        // Afficher l'image de fond pour toutes les scènes sauf celles de simulation de course
        if (
            current_scene != SCENE_PRACTICE_CLASSIC 
            || current_scene != SCENE_PRACTICE_SPRINT
            || current_scene != SCENE_QUALIF
            || current_scene != SCENE_QUALIF_SPRINT
            || current_scene != SCENE_RACE
            || current_scene != SCENE_SPRINT 
            ) {
            SDL_RenderCopy(renderer, bg_texture, NULL, NULL);  // Afficher l'image de fond
        }

        // rendre (envoyer à l'affichage) la scène actuelle
        render_scene(current_scene, renderer, title_font, button_font, text_font);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources
    SDL_DestroyTexture(bg_texture);
    Mix_FreeChunk(click_sound);
    Mix_FreeMusic(music);
    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);
    TTF_CloseFont(text_font);
    IMG_Quit();  
    cleanup_sdl(window, renderer);
    Mix_CloseAudio();  

    return EXIT_SUCCESS;
}
