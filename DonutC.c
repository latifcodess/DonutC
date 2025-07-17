#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define colonne 80
#define ligne 24
#define ligne_centre ligne/2
#define colonne_centre colonne/2

int main(void)
{
    // declaration des variables
    double theta = 0;
    double phi = 0;
    double R = 2;
    double r = 1;
    double x;
    double y;
    double z;
    int xp = 0;
    int yp = 0;
    double facteur_zoom = colonne_centre / (R + r);

    // delcaration des tableaux
    char screen[ligne][colonne];

    printf("\x1b[H");

    // initialisation du tableau avec des espaces
    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            screen[x][y] = ' ';
        }
    }

    // calcul des points theta et phi
    for (double a = 0; a <= (2 * M_PI); a += 0.07) {
        theta = a;

        for (double b = 0; b <= (2 * M_PI); b += 0.07) {
            phi = b;

            //clacule du petit cercle (r) qui tourne autours du grand cercle (R) forma[nt un tore (donut)
            x = (R + r * cos(theta)) * cos(phi);
            y = (R + r * cos(theta)) * sin(phi);
            z = r * sin(theta);

            // position du donut
            xp = (int)(x * facteur_zoom + colonne_centre);
            yp = (int)(y * facteur_zoom + ligne_centre);

            // condition pour que le donut reste dans le tableau screen et ajout d'un caractère
            if (xp >= 0 && xp < colonne && yp >= 0 && yp < ligne){
                screen[yp][xp] = '@';
            }
        }
    }

    // affichage du tableau
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}