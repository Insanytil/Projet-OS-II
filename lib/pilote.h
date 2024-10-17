#ifndef PILOTE_H
#define PILOTE_H

#define MAX_PILOTES 20

typedef struct {
    char prenom[20];
    char nom[30];
    int numero;
    char team[30];
    char code[4];
    int points;
} Pilote;

// Déclaration du tableau global de pilotes
extern Pilote pilotes[MAX_PILOTES];
extern int compteur_pilote;

#endif
