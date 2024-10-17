#include "lib/button.h"
#include "lib/sdl_utils.h"

// Fonction permettant d'afficher un bouton avec un texte centré
void render_button(SDL_Renderer* renderer, TTF_Font* font, Button* button, SDL_Color color) {
    if (!button->label || strlen(button->label) == 0) {
        printf("Erreur : le label du bouton est NULL ou vide.\n");
        return;
    }
    // Dessiner le rectangle du bouton avec un fond blanc
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50); 
    SDL_RenderFillRect(renderer, &button->rect);

    
    render_text(renderer, font, button->label, color, button->rect.x, button->rect.y, button->rect.w);
}
