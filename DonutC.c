#include <stdio.h>
#define colonne 80
#define ligne 24
#define colonne_centre colonne/2
#define ligne_centre ligne/2

int main(void) {
    // delcaration du tableau screen
    char screen[ligne][colonne];

    //initialisation du tableau avec des espaces
    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            screen[x][y] = ' ';
        }
    }

    // ajout d'un caractère au milieu du tableau
    screen[ligne_centre][colonne_centre] = 'X';

    // affichage du tableau
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}