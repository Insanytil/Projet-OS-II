#include "lib/pilote.h"
#include "lib/sdl_utils.h"
#include "lib/event_handler.h"
#include "lib/scene.h"
#include "lib/button.h"
#include "lib/courses.h"
#include <fcntl.h>  
#include <unistd.h> 
#include <stdio.h>
#include <string.h>
#include "lib/global.h"

#define NUM_PILOTES 20

Button init_buttons[2];

// Déclaration globale des pilotes (afin qu'il accessible dans toutes les scènes)
Pilote pilotes[NUM_PILOTES];
int compteur_pilote = 0;
// Déclaration globale des courses (accessible dans toutes les scènes)
Course courses[MAX_COURSES];
int compteur_course;


// Fonction pour charger les pilotes depuis un fichier CSV
void chargement_pilotes(const char* filenom, Pilote pilotes[], int* compteur_pilote) {
    int fichier = open(filenom, O_RDONLY);
    if (fichier == -1) {
        perror("Erreur lors de l'ouverture du fichier de données des pilotes");
        return;
    }

    char buffer[4096];  // Taille du buffer pour stocker les données des pilotes
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
        sscanf(line, "%[^,],%[^,],%d,%[^,],%[^,],%d",
               pilotes[*compteur_pilote].prenom,
               pilotes[*compteur_pilote].nom,
               &pilotes[*compteur_pilote].numero,
               pilotes[*compteur_pilote].team,
               pilotes[*compteur_pilote].code,
               &pilotes[*compteur_pilote].points);

        (*compteur_pilote)++;

        line = strtok(NULL, "\n");
    }

    close(fichier);
}

void chargement_courses(const char* filename, Course courses[], int* compteur_course) {
    int fichier = open(filename, O_RDONLY);
    if (fichier == -1) {
        perror("Erreur lors de l'ouverture du fichier courses.csv");
        return;
    }

    char buffer[4096];   
    char *ligne;         
    int bytes_read;
    *compteur_course = 0;

    
    bytes_read = read(fichier, buffer, sizeof(buffer) - 1); 
    if (bytes_read == -1) {
        perror("Erreur lors de la lecture du fichier courses.csv");
        close(fichier);
        return;
    }

    buffer[bytes_read] = '\0';

    ligne = strtok(buffer, "\n");

    while (ligne != NULL && *compteur_course < MAX_COURSES) {
        Course course;
        sscanf(ligne, "%[^,],%[^,],%d,%d,%d,%d",
               course.nom_circuit,
               course.pays,
               &course.tours,
               &course.m_par_tour,
               &course.total_m,
               &course.est_un_sprint);

        
        courses[*compteur_course] = course;
        (*compteur_course)++;

        ligne = strtok(NULL, "\n");
    }

    close(fichier);  
}

void init_championnat() {

    if (strcmp(chemin_sauvegarde, "") == 0) {
        chargement_pilotes("ressources/pilotes.csv", pilotes, &compteur_pilote);
    } else {
        // Sinon, on utilise le chemin sauvegardé
        chargement_pilotes(chemin_sauvegarde, pilotes, &compteur_pilote);
    }
    
    chargement_courses("courses.csv", courses, &compteur_course);
    init_buttons[0] = (Button){ .rect = {50, 550, 180, 30}, .label = "Menu"};
    init_buttons[1] = (Button){ .rect = { 570, 550, 180, 30}, .label = "Continue"};
}
// Rendu de la scène INIT 
void render_init(SDL_Renderer* renderer, TTF_Font* text_font, TTF_Font* button_font) {
    SDL_Color white = {255, 255, 255};
    SDL_Color black = { 0, 0, 0};
    SDL_Color red = { 255, 0, 0};
    char buffer[128];

    for (int i = 0; i < compteur_pilote; i++) {
        snprintf(buffer, sizeof(buffer), "%d. %s %s - %s / [ %d ]", i + 1, pilotes[i].prenom, pilotes[i].nom, pilotes[i].team, pilotes[i].points);
        render_text_fond_blanc(renderer, text_font, buffer, black, 25, 80 + i * 20, 300);
    }

    for (int i = 0; i < compteur_course; i++) {
        snprintf(buffer, sizeof(buffer), "%d. %s - %s", i + 1, courses[i].nom_circuit, courses[i].pays);
        render_text_fond_blanc(renderer, text_font, buffer, black, 450, 80 + i * 17, 300);
    }
    render_text_fond_noir(renderer, button_font, "Liste Pilotes", red, 25, 25, 300);
    render_text_fond_noir(renderer, button_font, "Liste Courses", red, 450, 25, 300);
    for (int i = 0; i < 2; i++) {
    render_button(renderer, button_font, &init_buttons[i], white);
    }
}

int handle_init_events(SDL_Event* event) {
     if (handle_event(event, init_buttons, 2) == 0) {
        return -2;
     } else if (handle_event(event, init_buttons, 2) == 1) {
        return 1;
     }
};



