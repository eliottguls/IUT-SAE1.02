#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


#define MAX 17776
typedef char chaine10[11];

int dep;            // n° du département (22, 29, 35 ou 56)chaine date;

char date[11];      // date sous la forme aaaa-mm-jj
                    // exemple : 2020-05-23


int pos;            // nombre de cas enregistrés ce jour-là 
                    // dans cette classe d’âge et dans ce
                    // département 

int classe;         // tranche d’âge. La valeur 9 représente la 
                    // tranche d’âge [0 - 9 ans], la valeur 19 
                    // représente la tranche d’âge [10 – 19 ans], 
                    // etc. jusqu’à la valeur 90 qui représente les
                    // 90 ans ou plus.
                    // Attention, la tranche d’âge 0 est un 
                    // récapitulatif qui représente toutes les
                    // classes d’âge
                    
int pop;            // nombre d’habitants de cette tranche d’âge 
                    // dans ce département



typedef struct{
    int dep;
    chaine10 date;
    int pos;
    int classe;
    int pop;
} donn_cov;

typedef donn_cov t_cov[MAX];

void Lirefichier(t_cov tc, int *nb_cas){
    FILE * fic;

    donn_cov tmp;
    fic = fopen("DonneesCovid.data", "rb");

    fread(&tmp, sizeof(tmp), 1, fic);

    while(!(feof(fic)) && *nb_cas<MAX){
        tc[*nb_cas] = tmp;
        (*nb_cas)++;
        fread(&tmp, sizeof(tmp), 1, fic);
    }
}

void afficher_tab_cov(t_cov tc, int nb_cas){
    for (int i =0;i<nb_cas;i++){
        printf("dep : %d \t", tc[i].dep);
        printf("date : %s\t", tc[i].date);
        printf("pos : %d\t", tc[i].pos);
        printf("classe : %d\t", tc[i].classe);
        printf("pop : %d\t \n", tc[i].pop);
        sleep(0.5);

    }
}

void echange(donn_cov *a, donn_cov *b) {
  donn_cov t = *a;
  *a = *b;
  *b = t;
}


int partition_cr(t_cov tab, int deb, int fin) {
  
  int pivot = tab[fin].dep;
  
  int i = (deb - 1);

  //on compare avec le pivot tous les elements du tab
  for (int j = deb; j < fin; j++){
    if (tab[j].dep <= pivot){
        
      // si un element plus petit que le pivot
      // on l'échange avec avec l'élément le plsu grand
      i++;
      echange(&tab[i], &tab[j]);
    }
  }

  // on échange le pivot avec l'element plus grand d'indice i
  echange(&tab[i + 1], &tab[fin]);
  
  // on délivre l'indice du "point de partition_dec"
  return (i + 1);
}

void quickSort(t_cov tab, int deb, int fin) {
  if (deb < fin){
      int pi = partition_cr(tab, deb, fin);
      // appel récursif sur la partie à gauche du pivot
      quickSort(tab, deb, pi - 1);
      // appel récursif sur la partie à droite du pivot
      quickSort(tab, pi + 1, fin);
  }
}






void triDepartement(t_cov tc, int nb_cas){
    quickSort(tc, 0, nb_cas-1);
}



int main(){
    t_cov tab;
    int nb_cas;

    Lirefichier(tab, &nb_cas);

    afficher_tab_cov(tab, nb_cas);

    triDepartement(tab, nb_cas);
    afficher_tab_cov(tab, nb_cas);

    return EXIT_SUCCESS;
}


