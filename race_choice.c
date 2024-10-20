#include "lib/race_choice.h"
Button races_button[26];

void init_course_selection(){
    
int button_width = 162;
    int button_height = 20;
    int padding_x = 45;
    int padding_y = 30;
    int start_x = 22;
    int start_y = 150;
    int screen_width = 800;  // Replace with actual screen width
    int screen_height = 600; // Replace with actual screen height

    for (int i = 0; i < 24; i++) {
        int row = i / 4;  // 6 rows
        int col = i % 4;  // 4 columns

        races_button[i] = (Button) {
            .rect = {
                    start_x + col * (button_width + padding_x),
                    start_y + row * (button_height + padding_y),
                    button_width,
                    button_height}, 
            .label = courses[i].nom_circuit
        };
    }

    
    int last_button_x = (screen_width - button_width) / 2;
    int last_button_y = screen_height - button_height - 125; 
    races_button[24] = (Button) {
        .rect = {
                last_button_x,
                last_button_y,
                button_width,
                button_height},
        .label = courses[24].nom_circuit
    };

    races_button[25] = (Button) {
        .rect = {
            600,
            500,
            100,
            40
        },
        .label = "Back"
    };
}


void render_course_selection(SDL_Renderer* renderer, TTF_Font* title_font, TTF_Font* course_text_font) {
    
    SDL_Color white = { 255, 255, 255};
    SDL_Color red = { 255, 0, 0};
    char buffer[128];
    for (int i = 0; i < 25; i++) {
        render_button(renderer, course_text_font, &races_button[i], white);
    }

    render_button(renderer, title_font, &races_button[25], white);
    render_text_fond_noir(renderer, title_font, "Select a Race", red, 250, 50, 300);
}


int handle_course_selection_events(SDL_Event* event) {

    int clicked_button = handle_event(event, races_button, 26);
    
    if (clicked_button == 25) {  
        return -1;  
    } else if (clicked_button >= 0 && clicked_button < 25) {  
        return clicked_button; 
    }
    
    return -2;  
}

int check_is_sprint(int button) {
    if (button >= 0 && button < compteur_course) {
        return courses[button].est_un_sprint;
    }
    return 0;  
}