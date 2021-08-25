#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 1000
#define AGGIUNGIGRAFO "AggiungiGrafo"
#define TOPK "TopK"

typedef struct nodo{
    int num;
    struct nodo* next;
}lista; //nodi da etichettare

int counter = 0;
int d, len;
int* pesi;

int cammino_minimo(int mat[][d]);
void inserisci_in_ordine(lista*, int);
lista* rimuovi_nodo(lista*, int);
//void build_max_heap(int res[len]);
void max_heapify(int res[len], int n);

int main(int argc, char* argv[]) {
    char str[MAX];
    char *end;
    char* f;

    f = fgets(str, MAX, stdin);
    if(f){
        d = strtol(str, &end, 10);
        len = strtol(end, &end, 10);
    }

    int mat[d][d];
    int res[len];

    f = fgets(str, MAX, stdin);
    str[strlen(str)-1] = '\0';

    if(f){
        while(strcmp(str, TOPK)!=0){
            while(strcmp(str, AGGIUNGIGRAFO)==0){
                counter++;

                //f = fgets(str, MAX, stdin);
                if(f){
                    for(int i=0; i<d; i++){
                        f = fgets(str, MAX, stdin);
                        if(f){
                            for(int j=0; j<d; j++) {
                                if(j==0)
                                    mat[i][j] = strtol(str, &end, 10);
                                else
                                    mat[i][j] = strtol(end+1, &end, 10);
                            }
                        }
                    }
                }

                max_heapify(res, cammino_minimo(mat));

                f = fgets(str, MAX, stdin);
                str[strlen(str)-1] = '\0';
                if(f)
                    continue;
            }
        }
    }

    for(int i=0; i<len; i++){
        printf("%d ", res[i]);
    }

    return 0;
}

int cammino_minimo(int mat[][d]){
    int cm=0, tmp=0, min, min_index, c;
    lista* da_etichettare = NULL;
    lista* etichettati = NULL;

    pesi = malloc(sizeof(int)*d);

    inserisci_in_ordine(etichettati, 0);

    for(int i=1; i<d; i++){
        inserisci_in_ordine(da_etichettare, i);
    }

    for(int i=0; i<d; i++){
        pesi[i] = -1;
    }

    while(1){
        min = mat[tmp][0];
        for(int j=0; j<d; j++){
            if(mat[tmp][j] < min){
                min = mat[tmp][j];
                min_index = j;
            }
        }

        if(pesi[min_index]>min || pesi[min_index]==-1){
            pesi[min_index] = min;
            if(tmp!=0){
                pesi[min_index] += pesi[tmp];
            }
        }


        min = pesi[0];
        for(int k=0; k<d; k++){
            if(pesi[k]<min){
                min = pesi[k];
                min_index = k;
            }
        }
        inserisci_in_ordine(etichettati, min_index);

        tmp = min_index;

        for(int k=0; k<d; k++){
            c = 0;
            if(mat[tmp][k] == 0)
                c++;
        }

        if(c == d){
            break;
        }
    }
    for(int i=0; i<d; i++){
        cm += pesi[i];
    }

    return cm;
}

void inserisci_in_ordine(lista* l, int n){
    lista *tmp;

    if(!l){
        l = malloc(sizeof(lista));
        l->num=n;
        l->next=NULL;
        return;
    }
    if(l->num > n){
        tmp = malloc(sizeof(lista));
        tmp->num = n;
        tmp->next = l;
        l = tmp;
        return;
    }

    inserisci_in_ordine(l->next, n);
}

lista* rimuovi_nodo(lista* l, int n){
    if(l==NULL){
        return l;
    }
    if(l->num == n){
        lista* tmp = l;
        l = l->next;
        free(tmp);
    }else{
        l->next = rimuovi_nodo(l->next, n);
        return l;
    }
}


void max_heapify(int res[len], int num){
    int l = 2*num;
    int r = (2*num)+1;
    int max;
    int tmp;

    if(l<=len && res[l]>res[num])
        max = l;
    else max = num;

    if(r<=len && res[r]>res[max])
        max = r;
    if(max != num){
        tmp = res[num];
        res[num] = res[max];
        res[max] = tmp;
        max_heapify(res, max);
    }
}
