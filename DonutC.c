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
    double facteur_zoom = (colonne_centre / (R + r)) * 2.0;
    double A = 0; 
    double B = 0;

    for(;;) {
        // delcaration des tableaux
        char screen[ligne][colonne];
        double zbuffer[ligne][colonne];

        printf("\x1b[H");

        // initialisation du tableau avec des espaces
        for (int x = 0; x < ligne; x++) {
            for (int y = 0; y < colonne; y++) {
                screen[x][y] = ' ';
                zbuffer[x][y] = -INFINITY;
            }
        }

        // calcul des points theta et phi
        for (double a = 0; a <= (2 * M_PI); a += 0.07) {
            theta = a;

            for (double b = 0; b <= (2 * M_PI); b += 0.07) {
                phi = b;

                double cosa = cos(a), sina = sin(a);
                double cosb = cos(b), sinb = sin(b);
                double cosA = cos(A), sinA = sin(A);
                double cosB = cos(B), sinB = sin(B);

                double circlex = R + r * cosa;
                double circley = r * sina;

                x = circlex * (cosB * cosb + sinA * sinB * sinb) - circley * cosA * sinB;
                y = circlex * (sinB * cosb - sinA * cosB * sinb) + circley * cosA * cosB;
                z = cosA * circlex * sinb + circley * sinA;

                double by = y / 1.5;

                // position du donut
                double k = 7;
                double ooz = 1 / (z + k);
                xp = (int)(colonne_centre + facteur_zoom * ooz * x);
                yp = (int)(ligne_centre + facteur_zoom * ooz * by);

                // Calcul de la normale pour la lumière
                double nx = cosb * cosa;
                double ny = sinb * cosa;
                double nz = sina;

                // Direction de la lumière (fixe)
                double lx = 0;
                double ly = 1;
                double lz = -1;

                // Produit scalaire normalisé
                double norm = sqrt(nx*nx + ny*ny + nz*nz);
                nx /= norm;
                ny /= norm;
                nz /= norm;

                double light_norm = sqrt(lx*lx + ly*ly + lz*lz);
                lx /= light_norm;
                ly /= light_norm;
                lz /= light_norm;

                double L = nx*lx + ny*ly + nz*lz;
                if (L < 0) L = 0;
                const char luminance_chars[] = ".,-~:;=!*#$@";
                int luminance_index = (int)(L * 11);
                if (luminance_index > 11) luminance_index = 11;


                // condition pour que le donut reste dans le tableau screen et ajout d'un caractère
                if (xp >= 0 && xp < colonne && yp >= 0 && yp < ligne){
                        if (ooz > zbuffer[yp][xp]) {
                            zbuffer[yp][xp] = ooz;
                            screen[yp][xp] = luminance_chars[luminance_index];
                    }
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

        A += 0.04; 
        B += 0.02;

        usleep(30000);
    }
}