#ifndef COURSES_H
#define COURSES_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_COURSES 25
#define MAX_NOM_CIRCUIT 40
#define MAX_NOM_PAYS 30

typedef struct {
    char nom_circuit[MAX_NOM_CIRCUIT];  
    char pays[MAX_NOM_PAYS];     
    int tours;                             
    int m_par_tour;                   
    int total_m;                         
    int est_un_sprint;   // valeur 0 pour faux et 1 pour vrai                    
} Course;


extern Course courses[MAX_COURSES];
extern int compteur_course;

#endif 