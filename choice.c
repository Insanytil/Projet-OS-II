#include "lib/choice.h"
#include "lib/button.h"
#include "lib/sdl_utils.h"
#include "lib/event_handler.h"


Button choice_buttons[3];

void init_choice() {
    choice_buttons[0] = (Button) { .rect = { 50, 500, 200, 30}, .label = "Result"};
    choice_buttons[1] = (Button) { .rect = { 300, 500, 200, 30}, .label = "Select Race"};
    choice_buttons[2] = (Button) { .rect = { 550, 500, 200, 30}, .label = "Save"};
}

int handle_choice_events(SDL_Event* event) {
    int clicked_button = handle_event(event, choice_buttons, 3);
    if (clicked_button == 2) {
        
    }
    return clicked_button;
}

void render_choice(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font) {
    SDL_Color white = { 255, 255, 255};
    SDL_Color red = { 255, 0, 0};

    for (int i = 0; i < 3; i++) {
        render_button(renderer, button_font, &choice_buttons[i], white);
    }

    render_text_fond_noir(renderer, title_font, "Menu de selection", red, 300, 200, 200);
}

void choice_save() {
    printf("Demande de sauvegarde du championnat");
}