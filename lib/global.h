#ifndef GLOBAL_H
#define GLOBAL_H



extern char chemin_sauvegarde[256];
extern char save_name[256];
extern int course_selected;

void sanitize_filename(char* filename);
#endif