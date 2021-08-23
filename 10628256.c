#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 1000
#define AGGIUNGI 14
#define TOPK 5

typedef struct nodo{
    int num;
    struct nodo* next;
}lista; //nodi da etichettare

int counter = 0;
int d, len;
int* pesi;

int cammino_minimo(int** mat);
void inserisci_in_ordine(lista*, int);
lista* rimuovi_nodo(lista*, int);
void merge(int[], int, int, int, int);
void mergeSort(int[], int, int, int);

int main(int argc, char* argv[]) {
    FILE* fp;
    char aggiungi[] = "AggiungiGrafo";
    char final[] = "TopK";
    char str[MAX];
    char *read = NULL;
    char *end = ",";
    int *res = NULL;

    if(argc==2){
        fp = fopen(argv[1], "r");
        if(fp!=NULL){
            fgets(str, MAX, fp);
            read = str;
            d = strtol(read, &read, 10);
            len = strtol(read, &read, 10);

            fgets(str, AGGIUNGI, fp);

            int mat[d][d];

            while(strcmp(str, final)!=0){
                if(strcmp(str, aggiungi)==0){
                    counter++;
//debuggato fin qui

                    for(int i=0; i<=d; i++){
                        fgets(str, MAX, fp);
                        read = str;
                        printf("%s\n", read);
                        for(int j=0; j<d; j++) {
                            mat[i][j] = strtol(read, &end, 10);
                        }
                    }

                    for(int i=0; i<d; i++){
                        for(int j=0; j<d; j++){
                            printf("%7d", mat[i][j]);
                        }
                        printf("\n");
                    }

                }


                res = malloc(sizeof(int));
                res[counter-1]=cammino_minimo(mat);
            }

            mergeSort(res, 0, counter, d);

            for(int i=0; i<len; i++){
                printf("%d ", res[i]);
            }
        }else printf("errore apertura file\n");
    }else printf("errore numero parametri\n");

    fclose(fp);
    return 0;
}

int cammino_minimo(int** mat){
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

void merge(int vett[], int start, int mid, int end, int len){
    int i, j, k, tmp[len];
    i = start;
    j = mid+1;
    k = 0;

    while (i<=mid && j<=end) {
        if (vett[i]<vett[j]) {
            tmp[k] = vett[i];
            i++;
        } else {
            tmp[k] = vett[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        tmp[k] = vett[i];
        i++;
        k++;
    }
    while (j <= end) {
        tmp[k] = vett[j];
        j++;
        k++;
    }
    for (k=start; k<=end; k++)
        vett[k] = tmp[k-start];
}

void mergeSort(int ord[], int start, int end, int len){
    int mid;
    if (start < end) {
        mid = (start + end)/2;
        mergeSort(ord, start, mid, len);
        mergeSort(ord, mid+1, end, len);
        merge(ord, start, mid, end, len);
    }
}


