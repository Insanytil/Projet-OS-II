#include "lib/menu.h"
#include "lib/button.h"
#include "lib/sdl_utils.h"
#include "lib/event_handler.h"

// Boutons pour le menu
Button menu_buttons[2];

// Initialisation du menu (crée les boutons et leur donne du texte)
void init_menu() {
    // Initialiser les boutons avec leurs labels
    menu_buttons[0] = (Button){ .rect = {0, 0, 400, 30}, .label = "Nouveau championnat" };
    menu_buttons[1] = (Button){ .rect = {0, 0, 400, 30}, .label = "Charger une sauvegarde" };
}

// Gestion des événements du menu
int handle_menu_events(SDL_Event* event) {
    int clicked_button = handle_event(event, menu_buttons, 2);
    return clicked_button;  // Retourner l'index du bouton cliqué
}

// Rendu du menu (affiche le titre et les boutons avec leur texte)
void render_menu(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font) {
    SDL_Color white = {255, 255, 255};
    SDL_Color red = { 255, 0, 0};


    // Afficher le titre
    render_text(renderer, title_font, "F1 Championship Simulator", red, 0, 100, 800);

    // Positionner les boutons
    menu_buttons[0].rect.x = 200;  // rect.x = position horizontale
    menu_buttons[0].rect.y = 450;  // rect.y = position verticale
    menu_buttons[1].rect.x = 200;
    menu_buttons[1].rect.y = 500;

    // Afficher les boutons avec du texte
    for (int i = 0; i < 2; ++i) {
        render_button(renderer, button_font, &menu_buttons[i], white);
    }
}
