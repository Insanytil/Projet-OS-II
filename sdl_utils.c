#include "lib/sdl_utils.h"
#include <stdio.h>

// Fonction d'initialisation de SDL et des fenêtres et du renderer
int init_sdl(SDL_Window** window, SDL_Renderer** renderer, const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Créer la fenêtre
    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    // Créer le renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return -1;
    }

    // Initialiser SDL_ttf pour le texte
    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return -1;
    }

    return 0;  // Initialisation réussie
}

// Fonction pour nettoyer et quitter SDL proprement
void cleanup_sdl(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// Fonction pour rendre du texte à l'écran avec gestion des erreurs et messages de débogage
void render_text_fond_blanc(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width) {
    if (!font) {
        printf("Erreur : La police (font) est NULL.\n");
        return;
    }

    // Vérifier si le texte est NULL ou vide
    if (!text || strlen(text) == 0) {
        printf("Erreur : Le texte est NULL ou vide.\n");
        return;
    }

    // Créer la surface de texte à partir de la police et du texte donné
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Obtenir la taille du texte
    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    // Calculer la position pour centrer le texte
    SDL_Rect dstrect = { x + (width - text_width) / 2, y, text_width, text_height };

    // Définir la couleur de fond (blanc) et dessiner un rectangle derrière le texte
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
    SDL_RenderFillRect(renderer, &dstrect);  

    // afficher le texte à l'écran
    if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0) {
        printf("Erreur lors du rendu du texte : %s\n", SDL_GetError());
    }

    // Nettoyage des ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width) {
    if (!font) {
        printf("Erreur : La police (font) est NULL.\n");
        return;
    }

    // Vérifier si le texte est NULL ou vide
    if (!text || strlen(text) == 0) {
        printf("Erreur : Le texte est NULL ou vide.\n");
        return;
    }
    // Créer la surface de texte à partir de la police et du texte donné
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Obtenir la taille du texte
    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);
    
    

    // Calculer la position pour centrer le texte dans le bouton ou à l'écran
    SDL_Rect dstrect = { x + (width - text_width) / 2, y, text_width, text_height };

    // Rendre le texte à l'écran
    if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0) {
        printf("Erreur lors du rendu du texte : %s\n", SDL_GetError());
    }

    // Nettoyage des ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void render_text_fond_noir(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int width) {
    if (!font) {
        printf("Erreur : La police (font) est NULL.\n");
        return;
    }

    // Vérifier si le texte est NULL ou vide
    if (!text || strlen(text) == 0) {
        printf("Erreur : Le texte est NULL ou vide.\n");
        return;
    }

    // Créer la surface de texte à partir de la police et du texte donné
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        return;
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Obtenir la taille du texte
    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    // Calculer la position pour centrer le texte
    SDL_Rect dstrect = { x + (width - text_width) / 2, y, text_width, text_height };

    // Définir la couleur de fond (blanc) et dessiner un rectangle derrière le texte
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Couleur blanche
    SDL_RenderFillRect(renderer, &dstrect);  // Remplir le rectangle

    // Rendre le texte à l'écran
    if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0) {
        printf("Erreur lors du rendu du texte : %s\n", SDL_GetError());
    }

    // Nettoyage des ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


    