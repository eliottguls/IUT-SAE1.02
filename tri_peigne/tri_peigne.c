#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 10
typedef int tableau[N];

void tri_peigne_croissant(tableau tab){
    int compteur, i;
    bool trouver;
    compteur = N;
    trouver = false;
    while (( trouver) || (compteur>1)){ // strcmp pour les caratctères
        trouver = false;
        compteur = compteur / 1.3;
        if (compteur<1) compteur=1;
        for (i=0; i<N-compteur; i++) {
            if (tab[i]>tab[i+compteur]){ // strcmp pour les caratctères
                trouver = true;
                int temp = tab[i];
                tab[i] = tab[i+compteur];   // strcopy pour les caractèes
                tab[i+compteur] = temp;
            }
        }
    }
}

void tri_peigne_decroissant(tableau tab){
    int compteur, i;
    bool trouver;
    compteur = N;
    trouver = false;
    while (( trouver) || (compteur>1)){ // strcmp pour les caratctères
        trouver = false;
        compteur = compteur / 1.3;
        if (compteur<1) compteur=1;
        for (i=0; i<N-compteur; i++) {
            if (tab[i]<tab[i+compteur]){ // strcmp pour les caratctères
                trouver = true;
                int temp = tab[i];
                tab[i] = tab[i+compteur];   // strcopy pour les caractèes
                tab[i+compteur] = temp;
            }
        }
    }
}

void affiche_tab(tableau tab){
    int i;
    for (i=0; i<N; i++){
        printf("%d, ", tab[i]);
    }
}

int main(){
    char choix[10];
    system("clear");
    tableau tab = {99, 47, 54, 12, 25, 39, 18, 26, 81, 39};
    //tableau tab_fav = {12, 18, 25, 26, 39, 39, 47, 54, 81, 99}; 
    //tableau tab_defav = {99, 81, 54, 47, 39, 39, 26, 25, 18, 12};
    printf("\t\t TRI A PEIGNE\n");
    printf("\n");
    printf("tableau avant le tri :\n");
    affiche_tab(tab);
    printf("\n\n");
    printf("Quel tri voulez vous faire : croissant / decroissant\n");
    scanf("%s", choix);
    printf("\n");
    while (((strcmp(choix, "croissant") != 0) && (strcmp(choix, "decroissant") != 0))){
            printf("ressaisissez entre croissant et decroissant\n");
            scanf("%s", choix);
        }
    if (strcmp(choix, "croissant") == 0){
            printf("tableau après le tri :\n");
            tri_peigne_croissant(tab);
        }
        else if (strcmp(choix, "decroissant") == 0){
            printf("tableau après le tri :\n");
            tri_peigne_decroissant(tab);
        }
    affiche_tab(tab);
    printf("\n");
    return EXIT_SUCCESS;
}