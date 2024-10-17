#include "lib/score.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "lib/button.h"
#include "lib/sdl_utils.h"
#include "lib/global.h"
#include "lib/event_handler.h"
#include "lib/pilote.h"

Button score_button[1];
void init_score_scene() {
    score_button[0] = (Button){ .rect = {600, 550, 150, 30}, .label = "Back"};

}

void copy_drivers(Pilote source[], Pilote dest[], int compteur_pilote) {
    for (int i = 0; i < compteur_pilote; i++) {
        dest[i] = source[i];
    }
}

void sort_drivers_from_copy(Pilote temp_pilote[], int compteur_pilote) {
    for (int i = 0; i < compteur_pilote -1; i++) {
        for (int j = 0; j < compteur_pilote - i - 1; j++) {
            if (temp_pilote[j].points < temp_pilote[j + 1].points) {
                Pilote temp = temp_pilote[j];
                temp_pilote[j] = temp_pilote[j + 1];
                temp_pilote[j + 1] = temp;
            }
        }
    }
}

void render_score_scene(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font, TTF_Font* text_font) {

    SDL_Color black = { 0, 0, 0 };
    SDL_Color red = { 255, 0, 0} ;
    SDL_Color white = { 255, 255, 255};
    char buffer[128];

    Pilote temp_pilote[MAX_PILOTES];
    copy_drivers(pilotes, temp_pilote, compteur_pilote);

    sort_drivers_from_copy(temp_pilote, compteur_pilote);

    for (int i = 0; i < compteur_pilote; i++) {
        snprintf(buffer, sizeof(buffer), "%d. [ %s ] - %s %s - [POINTS : %d]", 
        i + 1, temp_pilote[i].code, temp_pilote[i].prenom, temp_pilote[i].nom, temp_pilote[i].points);
        render_text_fond_blanc(renderer, text_font, buffer, black,250, 100 + i * 20, 300);
    }

    render_text_fond_noir(renderer, title_font, "Classement", red, 300, 50, 200);
    render_button(renderer, button_font, &score_button[0], white);


}

int handle_score_events(SDL_Event* event) {
    int clicked_button = handle_event(event, score_button, 1);
    return clicked_button;
}