#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define colonne 80
#define ligne 24

int main(void) {
    // declaration des variables
    double theta = 0;
    double phi = 0;
    double R = 2;
    double r = 1;


    // delcaration des tableaux
    char screen[ligne][colonne];

    //initialisation du tableau avec des espaces
    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            screen[x][y] = ' ';
        }
    }

    for (double a = 0; a <= (2 * M_PI); a+=0.5) {
        theta = a;

        for (double b = 0; b <= (2 * M_PI); b+=0.5){
            phi = b;
        }
    }

    double x = (R + r * cos(theta)) * cos(phi);
    double y = (R + r * cos(theta)) * sin(phi);
    double z = r * sin(theta);

    // affichage du tableau
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}