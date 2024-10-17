#include "lib/pilote.h"
#include "lib/sdl_utils.h"
#include "lib/event_handler.h"
#include "lib/scene.h"
#include "lib/button.h"
#include <fcntl.h>  /
#include <unistd.h> 
#include <stdio.h>
#include <string.h>

#define NUM_PILOTES 20

Button valide_button;

// Déclaration globale des pilotes (afin qu'il accessible dans toutes les scènes)
Pilote pilotes[NUM_PILOTES];
int compteur_pilote = 0;

// Fonction pour charger les pilotes depuis un fichier CSV
void chargement_pilotes(const char* filenom, Pilote pilotes[], int* compteur_pilote) {
    int fichier = open(filenom, O_RDONLY);
    if (fichier == -1) {
        perror("Erreur lors de l'ouverture du fichier de données des pilotes");
        return;
    }

    char buffer[2096];  // Taille du buffer pour stocker les données des pilotes
    int bytes_read = read(fichier, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Erreur lors de la lecture du fichier");
        close(fichier);
        return;
    }
    buffer[bytes_read] = '\0'; 

    char* line = strtok(buffer, "\n");  
    *compteur_pilote = 0;

    while (line != NULL && *compteur_pilote < NUM_PILOTES) {
        sscanf(line, "%[^,],%[^,],%d,%[^,],%s",
               pilotes[*compteur_pilote].prenom,
               pilotes[*compteur_pilote].nom,
               &pilotes[*compteur_pilote].numero,
               pilotes[*compteur_pilote].team,
               pilotes[*compteur_pilote].code);

        pilotes[*compteur_pilote].points = 0;  
        (*compteur_pilote)++;

        line = strtok(NULL, "\n");  
    }

    close(fichier);  
}

void init_championnat() {
    chargement_pilotes("saves/pilotes.csv", pilotes, &compteur_pilote);
    valide_button = (Button){ .rect = {600, 500, 180, 50}, .label = "Menu"};
}
// Rendu de la scène INIT 
void render_init(SDL_Renderer* renderer, TTF_Font* text_font, TTF_Font* button_font) {
    SDL_Color white = {255, 255, 255};
    SDL_Color black = { 0, 0, 0};
    SDL_Color red = { 255, 0, 0};
    char buffer[128];

    for (int i = 0; i < compteur_pilote; i++) {
        snprintf(buffer, sizeof(buffer), "%d. %s %s - %s", i + 1, pilotes[i].prenom, pilotes[i].nom, pilotes[i].team);
        render_text_fond_blanc(renderer, text_font, buffer, black, 50, 100 + i * 20, 300);
    }
    render_text_fond_noir(renderer, button_font, "Liste Pilotes", red, 50, 50, 300);
    render_text_fond_noir(renderer, button_font, "Liste Courses", red, 500, 50, 300);
    render_button(renderer, button_font, &valide_button, white);
}

int handle_init_events(SDL_Event* event) {
     if (handle_event(event, &valide_button, 1) == 0) {
        return -2;
     }
};



