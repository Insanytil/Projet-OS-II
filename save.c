#include "lib/save.h"
#include "lib/sdl_utils.h"
#include <string.h>
#include <stdbool.h>
#include "lib/button.h"
#include "lib/pilote.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define MAX_INPUT_LENGTH 50

char save_input[MAX_INPUT_LENGTH];
bool is_typing = false;
SDL_Rect input_rect;
Button save_button;

void init_save_scene() {
    input_rect = (SDL_Rect){100, 200, 600, 50};
    memset(save_input, 0, sizeof(save_input));
    is_typing = false;

    save_button = (Button){ .rect = {300, 400, 200, 50}, .label = "Sauvegarder"};
}

void render_save_scene(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &input_rect);

    render_text(renderer, font, save_input, black, 100, 200, 600);
    render_button(renderer, font, &save_button, white);

}

int handle_save_scene_events(SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        if (x >= input_rect.x && x <= input_rect.x + input_rect.w &&
            y >= input_rect.y && y <= input_rect.y + input_rect.h) {
            is_typing = true;  // Activer la saisie de texte
            SDL_StartTextInput();  // Commencer la saisie de texte
        }

        if (x >= save_button.rect.x && x <= save_button.rect.x + save_button.rect.w &&
            y >= save_button.rect.y && y <= save_button.rect.y + save_button.rect.h) {
                if (strlen(save_input) > 0) {
                    is_typing = false; 
                    SDL_StopTextInput(); 
                    printf("Nom de la sauvegarde: %s\n", save_input);
                    save_pilotes_to_file(save_input);
                    return 1;
            }
        }
    }

    if (is_typing && event->type == SDL_TEXTINPUT) {
        
        if (strlen(save_input) + strlen(event->text.text) < MAX_INPUT_LENGTH) {
            strcat(save_input, event->text.text);
        }
    }

    if (is_typing && event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE) {
        
        if (strlen(save_input) > 0) {
            save_input[strlen(save_input) - 1] = '\0';  
        }
    }

    return 0;
}

void save_pilotes_to_file(const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "saves/%s.csv", filename);

    int file = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    char buffer[256];
    for (int i = 0; i < compteur_pilote; ++i) {
        int length = snprintf(buffer, sizeof(buffer), "%s,%s,%d,%s,%s,%d\n",
        pilotes[i].prenom,
        pilotes[i].nom,
        pilotes[i].numero,
        pilotes[i].team,
        pilotes[i].code,
        pilotes[i].points);

        if(write(file, buffer, length) == -1) {
            perror("Erreur lors de l'écriture dans le fichier");
            close(file);
            return;
        }
    }
    close(file);
    printf("Sauveharde réussie dans le fichier : %s\n, filepath");
}
