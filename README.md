# Projet OS II 2024-2025 Vervaeren Lucien
T2052 - Systèmes d'exploitation II (Pratique)
Projet de création d'un "Simulateur de championnat de F1"

## Dependances : 
1. SDL2 :
Description : Bibliothèque principale pour la gestion des fenêtres, du rendu graphique et des événements dans le projet
Utilisation : Création de la fenêtre, rendu des graphiques, gestion des événements (clavier, souris)
2. SDL2_ttf :
Description : Extension de SDL pour gérer le rendu des polices TrueType
Utilisation : Pour afficher du texte avec différentes polices dans le projet
3. SDL2_mixer :
Description : Extension de SDL pour la gestion de la musique et des sons
Utilisation : Chargement et lecture de fichiers audio (musique et effets sonores).
4. SDL2_image :
Description : Extension de SDL pour charger des images dans différents formats (JPG, PNG, etc.)
Utilisation : Chargement et affichage d'images comme le fond d'écran dans le projet


Ces dépendances doivent être installées pour que le projet puisse être compilé et exécuté correctement


# commande de compilation actuelle : 
gcc -o simulateur_f1 main.c button.c sdl_utils.c menu.c load_save.c event_handler.c scene.c init.c choice.c -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
