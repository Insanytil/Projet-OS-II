#include "lib/scene.h"
#include "lib/menu.h"
#include "lib/load_save.h"
#include "lib/init.h"
/*
#include "lib/result.h"
#include "lib/race_choice.h"
#include "lib/practice_classic.h"
#include "lib/qualif_classic.h"
#include "lib/qualif_sprint.h"
#include "lib/sprint.h"
#include "lib/race.h"
#include "lib/quit.h"
#include "lib/continue_to_qualif_classic.h"
#include "lib/practice_sprint.h"
#include "lib/continue_to_qualif_sprint.h"
#include "lib/continue_to_race.h"
#include "lib/continue_to_sprint.h"
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

// Fonction pour initialiser une scène
void init_scene(SceneType scene) {
    switch (scene) {
        case SCENE_MENU:
            init_menu();  // Initialisation du menu principal
            break;
        case SCENE_LOAD_SAVE:
            init_load_save();  // Initialisation de la scène de chargement des sauvegardes
            break;
        case SCENE_INIT:
            init_championnat();
            break;
       /*
        case SCENE_RACE_CHOICE:
            init_course_selection(); // Initialisation de la scène de sélection des courses (attention)
            break;
        case SCENE_RESULT:  // Initialisation de la scène des résultats (points des pilotes à l'instant t)
            init_result();
            break;
        case SCENE_PRACTICE_CLASSIC: // Initialisation de la scène de practice
            init_practice_classic();
            break;
        case SCENE_PRACTICE_SPRINT:
            init_practice_sprint();
            break;
        case SCENE_QUALIF: // Initialisation de la scène de qualification (course normal)
            init_qualif();
            break;
        case SCENE_QUALIF_SPRINT: // Initialisation de la scène de qualification (sprint)
            init_qualif_sprint();
            break;
        case SCENE_SPRINT: // Initialisation de la scène sprint
            init_sprint();
            break;
        case SCENE_RACE: // Initialisation de la scène race
            init_race();
            break;
        case SCENE_CONTINUE_TO_QUALIF:
            init_continue();
            break;
        case SCENE_QUIT: // Initialisation de la scène quit
            init_quit();
            break;
        */
        default:
            printf("Initialisation de la scène non prise en charge\n");
            break;
    }
}

// Fonction pour mettre à jour la scène actuelle
SceneType update_scene(SceneType current_scene, SDL_Event* event) {
    switch (current_scene) {
        case SCENE_MENU: {
            int clicked_button = handle_menu_events(event);
            if (clicked_button == 0) {
                return SCENE_INIT;  // Passer à la scène d'initialisation d'un nouveau championnat
            } else if (clicked_button == 1) {
                return SCENE_LOAD_SAVE;  // Passer à la scène de chargement des sauvegardes
            }
            break;
        }
        case SCENE_LOAD_SAVE: {
            int clicked_save = handle_load_save_events(event);
            if (clicked_save == -2) {
                return SCENE_MENU; // Passer à la scène du menu principal
            } else if (clicked_save >= 0) {
                return SCENE_INIT;  // Passer à la simulation après chargement de la sauvegarde
            }
            break;
        }

        case SCENE_INIT: {
            int clicked_init = handle_init_events(event);
            if (clicked_init == -2) {
            return SCENE_MENU; // Passer à l'interface des choix (résultats / run a race / save)
            }
            break;
        }
    /*
        case SCENE_CHOICE: {
            int clicked_choice = handle_choice_events(event);
            if (clicked_choice == 1) {
                return SCENE_RESULT; // Passer à l'interface du classement actuel
            } else if (clicked_choice == 2) {
                return SCENE_RACE_CHOICE; // Passer à l'interface de choix de la course
            } else if (clicked_choice == -1) {
                return SCENE_MENU; // Passer à l'interface du Menu principal
            }
            break;
        }

        case  SCENE_RESULT: {
            int clicked_result = handle_result_events(event);
            if (clicked_result == 1) {
                return SCENE_CHOICE; // Passer à l'interface des choix (résultats / run a race / save)
            }
            break;
        }
        case SCENE_RACE_CHOICE: {
            int clicked_race_choice = handle_race_choice(event);
            int is_sprint = check_for_sprint(clicked_race_choice);
            if (clicked_race_choice >= 0 && is_sprint == 1) {
                return SCENE_PRACTICE_SPRINT; // Passer à l'interface de la practice sprint
            } else if (clicked_race_choice >= 0 && is_sprint == 0) {
                return SCENE_PRACTICE_CLASSIC;
            } if (clicked_race_choice == -1) {
                return SCENE_CHOICE; // Passer à l'interface des choix (résultats / run a race / save)
            }
            break;
        }
        case SCENE_PRACTICE_CLASSIC: {
            return SCENE_CONTINUE_TO_QUALIF; // Passer à l'interface de demande de continuation (we classic)
            break;
        }
        case SCENE_PRACTICE_SPRINT: {
            return SCENE_CONTINUE_TO_QUALIF_SPRINT; // Passer à l'interface de demande de continuation (we sprint)
            break;
        }

        case SCENE_CONTINUE_TO_QUALIF: {
            int clicked_qualif_classic = handle_continue_to_qualif_event(event);
            if (clicked_qualif_classic == 0) {
                return SCENE_QUALIF;
            } else if (clicked_qualif_classic == 1) {
                return SCENE_RACE_CHOICE;
            }
            break;
        }
        
        case SCENE_CONTINUE_TO_QUALIF_SPRINT: {
            int clicked_qualif_sprint = handle_contine_to_qualif_sprint_event(event);
             if (clicked_qualif_sprint == 0) {
                return SCENE_QUALIF_SPRINT;
            } else if (clicked_qualif_sprint == 1) {
                return SCENE_RACE_CHOICE;
            }
            break;
        }

        case SCENE_QUALIF: {
            return SCENE_CONTNUE_TO_RACE;
            break;
        }
        case SCENE_QUALIF_SPRINT: {
            return SCENE_CONTINUE_TO_SPRINT;
            break;
        }

        case SCENE_CONTNUE_TO_RACE: {
            int clicked_continue_to_race = handle_continue_to_race_event(event);
            if (clicked_continue_to_race == 0) {
                return SCENE_RACE;
            } else if (clicked_continue_to_race == 1) {
                return SCENE_RACE_CHOICE;
            }
            break;
        }

        case SCENE_CONTINUE_TO_SPRINT: {
            int clicked_continue_to_sprint = handle_continue_to_sprint_event(event);
            if (clicked_continue_to_sprint == 0) {
                return SCENE_SPRINT;
            } else if (clicked_continue_to_sprint == 1) {
                return SCENE_RACE_CHOICE;
            }
            break;
        }

        case SCENE_RACE: {
            return SCENE_RESULT;
            break;
        }

        case SCENE_SPRINT: {
            return SCENE_CONTINUE_TO_QUALIF;
            break;
        }
        */

        default:
            break;
    }
    return current_scene;  // Rester dans la même scène si aucun changement n'est requis
}

// Fonction pour rendre la scène actuelle
void render_scene(SceneType scene, SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* button_font, TTF_Font* text_font) {
    switch (scene) {
        case SCENE_MENU:
            render_menu(renderer, title_font, button_font);  // Rendre le menu
            break;
        case SCENE_LOAD_SAVE:
            render_load_save(renderer, title_font, button_font);  // Rendre l'écran de chargement des sauvegardes
            break;
        case SCENE_INIT:
            render_init(renderer, text_font, button_font);
            break;
        /***
        case SCENE_CHOICE:
            render_choice(renderer, title_font, button_font);
            break;
        case SCENE_RESULT:
            render_result(renderer, title_font, button_font, text_font);
            break;
        case SCENE_RACE_CHOICE:
            render_race_choice(renderer, title_font, button_font);
            break;
        case SCENE_PRACTICE_CLASSIC:
            render_practice_classic(renderer, title_font, button_font, text_font);
            break;
        case SCENE_PRACTICE_SPRINT:
            render_practice_sprint(renderer, title_font, button_font, text_font);
            break;
        case SCENE_CONTINUE_TO_QUALIF:
            render_continue_to_qualif(renderer, title_font, button_font, text_font);
            break;
        case SCENE_CONTINUE_TO_QUALIF_SPRINT:
            render_continue_to_qualif_sprint(renderer, title_font, button_font, text_font);
            break;
        case SCENE_CONTINUE_TO_SPRINT:
            render_continue_to_sprint(renderer, title_font, button_font, text_font);
            break;
        case SCENE_CONTNUE_TO_RACE:
            render_continue_to_race(renderer, title_font, button_font, text_font);
            break;
        case SCENE_QUALIF:
            render_race(renderer, title_font, button_font, text_font);
            break;
        case SCENE_QUALIF_SPRINT:
            render_qualif_sprint(renderer, title_font, button_font, text_font);
            break;
        case SCENE_SPRINT:
            render_sprint(renderer, title_font, button_font, text_font);
            break;
        case SCENE_RACE:
            render_race(renderer, title_font, button_font, text_font);
            break;
        case SCENE_QUIT:
            render_quit(renderer, title_font, button_font, text_font);
            break;
        ***/
        default:
            break;
    }
}
