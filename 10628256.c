#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 3000
#define AGGIUNGIGRAFO "AggiungiGrafo"
#define TOPK "TopK"

int counter = 0;
int d, len;
int* pesi;
char str[MAX];
char *end;
char* f;

typedef struct{
    int peso;
    int index;
}grafo;

int cammino_minimo(int[][0]);
void max_heapify(grafo [], int);
void build_max_heap(grafo []);

int main() {
    grafo x;

    f = fgets(str, MAX, stdin);
    if(f){
        d = strtol(str, &end, 10);
        len = strtol(end, &end, 10);
    }

    int mat[d][d];
    grafo res[len];

    for(int i=0; i<=len; i++){
        res[i].peso = -1;
        res[i].index = -1;
    }

    f = fgets(str, MAX, stdin);
    str[strlen(str)-1] = '\0';

    if(f){
        if(strcmp(str, TOPK)==0){
            printf("\n");
            f = fgets(str, MAX, stdin);
            str[strlen(str)-1] = '\0';
        }
        while(strcmp(str, AGGIUNGIGRAFO)==0){
            counter++;
            x.index = counter-1;

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

            x.peso = cammino_minimo(mat);

            if(counter<=len){
                res[counter-1] = x;
                if(counter==len)
                    build_max_heap(res);
            }

            if(res[0].peso>x.peso && counter>len){
                res[0] = x;
                max_heapify(res, 0);
            }

            f = fgets(str, MAX, stdin);
            str[strlen(str)-1] = '\0';
            if(f){
                if(strcmp(str, TOPK)==0){
                    for(int i=0; i<len && res[i].index!=-1; i++){
                        if(counter<len && i==counter-1){
                            printf("%d", res[i].index);
                        }else{
                            printf("%d ", res[i].index);
                        }
                    }
                    printf("\n");
                    f = fgets(str, MAX, stdin);
                    str[strlen(str)-1] = '\0';

                }else
                    continue;
            }
        }
    }

    return 0;
}

int cammino_minimo(int mat[][d]){
    int cm=0, tmp=0, min, min_index=0, count, tmp_min, tmp_min_index;
    int da_etichettare[d];
    int all_zeros=0;

    pesi = malloc(sizeof(int)*d);
    pesi[0] = -1;
    da_etichettare[0] = -1;
    for(int i=1; i<d; i++){
        pesi[i] = -1;
        da_etichettare[i] = i;
        if(mat[0][i]==0){
            all_zeros++;
            if(all_zeros==d)
                return 0;
        }
    }


    count=0;
    while(1){
        min = 0;
        count++;

        for(int j=0; j<d; j++){
            if(mat[tmp][j]!=0 && tmp!=j && da_etichettare[j]!=-1){
                if(tmp==0){
                    pesi[j] = mat[tmp][j];
                }
                else if(pesi[j]>(pesi[tmp] + mat[tmp][j]) || pesi[j]==-1)
                    pesi[j] = pesi[tmp] + mat[tmp][j];
            }
        }

        for (int i = 0; i < d; i++) {
            if (da_etichettare[i]!=-1 && pesi[i]!=-1) {
                tmp_min = pesi[i];
                tmp_min_index = i;
                if(min==0){
                    min = tmp_min;
                    min_index = tmp_min_index;
                }else{
                    if(tmp_min<min){
                        min = tmp_min;
                        min_index = tmp_min_index;
                    }
                }
            }
        }

        da_etichettare[min_index] = -1;

        if(count == d)
            break;
        else
            tmp = min_index;
    }

    for(int i=0; i<d; i++){
        if(pesi[i]!=-1)
            cm += pesi[i];
    }

    return cm;
}

void max_heapify(grafo res[len], int num){
    int l = 2*num + 1;
    int r = 2*num + 2;
    int max;
    grafo tmp;

    if(l<len && res[l].peso>res[num].peso)
        max = l;
    else
        max = num;

    if(r<len && res[r].peso>res[max].peso)
        max = r;

    if(max != num){
        tmp = res[num];
        res[num] = res[max];
        res[max] = tmp;
        max_heapify(res, max);
    }
}
void build_max_heap(grafo res[len]){
    for(int i=len-1; i>=0; i--){
        max_heapify(res, i);
    }
}