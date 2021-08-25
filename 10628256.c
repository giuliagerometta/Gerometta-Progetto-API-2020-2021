#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 1000
#define AGGIUNGIGRAFO "AggiungiGrafo"
#define TOPK "TopK"

int counter = 0;
int d, len;
int* pesi;

int cammino_minimo(int mat[][d]);
void max_heapify(int res[len], int n);

int main(int argc, char* argv[]) {
    char str[MAX];
    char *end;
    char* f;
    int x;

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

                x = cammino_minimo(mat);
                //debuggato fino a qui (il cammino sembra venire corretto)
                max_heapify(res, x);

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
    int cm=0, tmp=0, min, min_index, count;
    int da_etichettare[d];

    pesi = malloc(sizeof(int)*d);
    pesi[0] = -1;
    da_etichettare[0] = -1;
    for(int i=1; i<d; i++){
        pesi[i] = -1;
        da_etichettare[i] = i;
    }

    while(1){
        count=0;
        for(int j=0; j<d; j++){
            if(mat[tmp][j]!=0 && tmp!=j && da_etichettare[j]!=-1){
                min = mat[tmp][j];
                min_index = j;
                if(mat[tmp][j]<min){
                    min = mat[tmp][j];
                    min_index = j;
                }
            }
        }

        if(pesi[min_index]<min || pesi[min_index]==-1){
            pesi[min_index] = min;
            if(tmp!=0){
                pesi[min_index] += pesi[tmp];
            }
        }

        da_etichettare[tmp] = -1;

        for(int i=0; i<d; i++){
            if(pesi[i]!=-1)
                count++;
        }
        count++;
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
