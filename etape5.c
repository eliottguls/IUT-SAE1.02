#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 17776
#define N 11

typedef char chaine10[10];

typedef struct{
    int dep;
    chaine10 date;
    int pos;
    int classe;
    int pop;
} t_Stat;

typedef t_Stat tab_covid[MAX];  

typedef int tab_pop[N];

void exchange(tab_covid tab, int i, int j){
    t_Stat indice_tmp;
    indice_tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = indice_tmp;
}

void tri_date(tab_covid tab, int nb_cas){
    int i, j, imin;
    chaine10 min;
    for (i=0; i<nb_cas-1; i++){
        strcpy(min, tab[i].date);  
        imin = i; 
        for (j=i+1; j < nb_cas; j++){
            if (strcmp(tab[j].date, min) == -1){
                strcpy(min, tab[j].date);
                imin = j;
            }
        }
        exchange(tab, i, imin); 
    }
}

void tri_departement(tab_covid tab, int nb_cas){
    int compteur, i;
    bool trouver;
    compteur = nb_cas;
    trouver = false; // mise en place d'un booléen comme condition d'arrêt
    while (( trouver) || (compteur>1)){ // booléen pour arrêter la boucle si on a fini de trier avant  que le compteur n'atteigne 0
        trouver = false;
        compteur = compteur / 1.3;
        if (compteur<1) compteur=1;
        for (i=0; i<nb_cas-compteur; i++) {
            if (tab[i].dep>tab[i+compteur].dep){ 
                trouver = true;
                t_Stat temp = tab[i];
                tab[i] = tab[i+compteur];
                tab[i+compteur] = temp;
            }
        }
    }
}

void tri_classe(tab_covid tab, int nb_cas){
    int compteur, i;
    bool trouver;
    compteur = nb_cas;
    trouver = false; // mise en place d'un booléen comme condition d'arrêt
    while (( trouver) || (compteur>1)){ // booléen pour arrêter la boucle si on a fini de trier avant  que le compteur n'atteigne 0
        trouver = false;
        compteur = compteur / 1.3;
        if (compteur<1) compteur=1;
        for (i=0; i<nb_cas-compteur; i++) {
            if (tab[i].classe>tab[i+compteur].classe){ 
                trouver = true;
                t_Stat temp = tab[i];
                tab[i] = tab[i+compteur];
                tab[i+compteur] = temp;
            }
        }
    }
}

void Lirefichier(tab_covid tab, int * nb_cas){
    FILE * f;
    t_Stat t;
    *nb_cas = 0;
    f = fopen("DonneesCovid.data","rb");
        fread(&t, sizeof(t),1,f);
        while(!feof(f) && *nb_cas<MAX){
            tab[*nb_cas] = t;
            (*nb_cas)++;
            fread(&t, sizeof(t),1,f);
        }
    fclose(f);
}


void affiche_Stat(tab_covid tab, int nb_cas){
    int i;
    for(i=0; i<nb_cas; i++){
        printf("%d\t%s\t%d\t%d\t%d\n", tab[i].dep, tab[i].date, tab[i].pos, tab[i].classe, tab[i].pop);
        printf("\n");
    }
}

void affiche_Stat_ligne(tab_covid tab, int ligne){
    int i;
    i = ligne;
    printf("%d\t%s\t%d\t%d\t%d\n", tab[i].dep, tab[i].date, tab[i].pos, tab[i].classe, tab[i].pop);
    printf("\n");
}

int population22(tab_covid tab, int nb_cas){
    int i, pop;
    for(i=0; i<nb_cas; i++){
        if ((tab[i].dep == 22) && (tab[i].classe == 0)){
            pop = tab[i].pop;
        }
    }
    return pop;
}

void debut_Annee_35(tab_covid tab, int nb_cas, tab_pop tab2){

    tri_classe(tab, nb_cas);

    int i, j;
    j = 0;
    for(i=0; i<nb_cas; i++){
        if ((tab[i].dep == 35) && (strcmp(tab[i].date, "2021-01-01") == 0)){
            tab2[j] = tab[i].pos;
            j++;
        }
    }

    printf("Nombre de cas en Ille-et-Vilaine par classe d'age, le 1er janvier 2021\n\n");
    printf("[ 0 -  9] : %d\n", tab2[1]);
    printf("[10 - 19] : %d\n", tab2[2]);
    printf("[20 - 29] : %d\n", tab2[3]);
    printf("[30 - 39] : %d\n", tab2[4]);
    printf("[40 - 49] : %d\n", tab2[5]);
    printf("[50 - 59] : %d\n", tab2[6]);
    printf("[60 - 69] : %d\n", tab2[7]);
    printf("[70 - 79] : %d\n", tab2[8]);
    printf("[80 - 89] : %d\n", tab2[9]);
    printf("[90 - 99] : %d\n", tab2[10]);
    printf("\n");
    printf(" TOTAL : %d\n", tab2[0]);
}

int main(){
    system("clear");
    tab_covid tab;
    tab_pop tab_p;
    int pop22;
    int nb_cas;
    int choix;
    printf("A Quel Question voulez vous voir la réponse ? 2 / 3 / 4 / 5 ");
    scanf("%d", &choix);

    system("clear");

    Lirefichier(tab, &nb_cas);
    
    switch(choix){
        case 2:
            tri_departement(tab, nb_cas);
            affiche_Stat(tab, nb_cas);
            printf("Tabelau de données trié par departement");
            break;
        case 3:
            pop22 = population22(tab, nb_cas);
            printf("population du 22 : %d\n", pop22);
            break;
        case 4:
            tri_date(tab, nb_cas);
            affiche_Stat(tab, nb_cas);
            printf("Tabelau de données trié par date");
            break;
        case 5:
            debut_Annee_35(tab, nb_cas, tab_p);
            break;
    }

    return EXIT_SUCCESS;
}