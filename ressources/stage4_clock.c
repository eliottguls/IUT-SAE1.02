#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 150000
typedef int tableau[N];

int nb_cmp=0;
int nb_permut=0;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void tamiser(tableau t, int noeud, int n){
    int fils = 2*noeud + 1;

    if ((fils < n) && (t[fils+1] > t[fils])){
        fils++;
        nb_cmp++;
    }

    if (fils <= n && t[noeud] < t[fils]){
        nb_cmp++;
        swap(&t[noeud], &t[fils]);
        nb_permut++;
        tamiser(t,fils,n);
    }
}   

void triParTas(tableau t){
    for (int i=N/2 - 1;i>=0;i--){
        tamiser(t,i,N-1);
    }

    for (int i=N - 1;i>0;i--){
        swap(&t[0], &t[i]);
        nb_permut++;
        tamiser(t,0,i-1);
    }
}


void remplirTab(tableau t){
    srand(time(NULL));
    for (int i=0;i<N;i++){
        t[i] = rand() % RAND_MAX;
    }
}

void afficheTab(tableau t){
    for (int i=0;i<N;i++){
        printf("%d,\n", t[i]);
    }
    printf("\n");
}

int main(){
    tableau tab;


    remplirTab(tab);
    //afficheTab(tab);
    clock_t begin_all_c = clock();
    time_t begin_all = time(NULL);


    clock_t begin_sort_c = clock();
    time_t begin_sort = time(NULL);
    triParTas(tab);
    clock_t end_sort_c = clock();
    time_t end_sort = time(NULL);


    double tmpsCPU_sort = (end_sort_c-begin_sort_c)*1.0 / CLOCKS_PER_SEC;

    afficheTab(tab);

    clock_t end_all_c = clock();
    time_t end_all = time(NULL);



    double tmpsCPU_all = (end_all_c-begin_all_c)*1.0 / CLOCKS_PER_SEC;

    printf("permut : %d \ncomp : %d \n", nb_cmp, nb_permut);
    printf("Temps exe all = %.3f s\n", difftime(end_all,begin_all));
    printf("Temps exe sort = %.3f s\n", difftime(end_sort, begin_sort));
    printf("Temps CPU all = %g ms\n", tmpsCPU_all);
    printf("Temps CPU sort = %g ms\n", tmpsCPU_sort);


}