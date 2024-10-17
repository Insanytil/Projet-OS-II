#include "lib/load_save.h"
#include "lib/sdl_utils.h"
#include "lib/button.h"
#include "lib/event_handler.h"
#include "lib/pilote.h"
#include "lib/global.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

char* saves[MAX_SAVES];
int num_saves = 0;
Button save_buttons[MAX_SAVES];
Button back_button;  


int is_regular_file(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

// Fonction pour initialiser la scène de chargement de sauvegarde
void init_load_save() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("saves")) != NULL) {
        int i = 0;
        while ((ent = readdir(dir)) != NULL && i < MAX_SAVES) {
            char full_path[256];
            int required_size = snprintf(full_path, sizeof(full_path), "saves/%s", ent->d_name);

            if (required_size >= sizeof(full_path)) {
                char* dynamic_path = malloc(required_size + 1);
                if (dynamic_path) {
                    snprintf(dynamic_path, required_size + 1, "saves/%s", ent->d_name);
                    free(dynamic_path);
                } else {
                    printf("Erreur : allocation mémoire échouée pour dynamic_path\n");
                }
            }

            if (is_regular_file(full_path)) {
                saves[i] = strdup(ent->d_name);
                save_buttons[i] = (Button){ .rect = {0, 0, 200, 30}, .label = saves[i] };
                i++;
            }
        }
        num_saves = i;
        closedir(dir);
    } else {
        printf("Erreur: Impossible d'ouvrir le répertoire des sauvegardes.\n");
    }

    // Initialiser le bouton "Retour au menu" en bas à droite
    back_button = (Button){ .rect = {600, 500, 180, 50}, .label = "Menu" };
}

// Gestion des événements de la scène de chargement de sauvegarde
int handle_load_save_events(SDL_Event* event) {
    int clicked_button = handle_event(event, save_buttons, num_saves);

   if (clicked_button >= 0 && clicked_button < num_saves) {
        snprintf(chemin_sauvegarde, sizeof(chemin_sauvegarde), "saves/%s", saves[clicked_button]);
        printf("Chemin de la sauvegarde sélectionnée : %s\n", chemin_sauvegarde);
        fflush(stdout);
        return 1;  // Indiquer qu'une sauvegarde a été sélectionnée
    }


    // Vérifier si le bouton "Retour au menu" a été cliqué
    if (handle_event(event, &back_button, 1) == 0) {
        return -2;  // Permet de retourner vers le menu
    }


    return clicked_button;
}

// Rendu de la scène load_save
void render_load_save(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font) {
    SDL_Color white = {255, 255, 255};  // Couleur blanche pour le texte

    for (int i = 0; i < num_saves; ++i) {
        save_buttons[i].rect.x = (800 - save_buttons[i].rect.w) / 2;
        save_buttons[i].rect.y = 150 + i * 60;
        render_button(renderer, button_font, &save_buttons[i], white);
    }

    // afficher le bouton Menu
    render_button(renderer, title_font, &back_button, white);
}
