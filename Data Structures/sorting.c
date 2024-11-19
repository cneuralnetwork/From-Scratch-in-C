#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int k = *a;
    *a = *b;
    *b = k;
}

int* bbl(int* a, int n){
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j < i; j++){
            if(a[j] > a[j + 1]) swap(&a[j], &a[j + 1]);
        }
    }
    return a;
}

int* ins(int* a, int n){
    for(int j = 1; j < n; j++){
        int key = a[j], ind = j - 1;
        while(ind >= 0 && a[ind] > key){
            a[ind + 1] = a[ind];
            ind--;
        }
        a[ind + 1] = key;
    }
    return a;
}

int* sel(int* a, int n){
    for(int i = 0; i < n - 1; i++){
        int min = a[i], loc = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < min){
                min = a[j];
                loc = j;
            }
        }
        if(loc != i){
            a[loc] = a[i];
            a[i] = min;
        }
    }
    return a;
}

void merge(int* a, int l, int m, int r){
    int* b = (int*)malloc((r - l + 1) * sizeof(int));
    int i = l, j = m + 1, k = 0;
    while(i <= m && j <= r){
        if(a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while(i <= m) b[k++] = a[i++];
    while(j <= r) b[k++] = a[j++];
    for(int i = 0; i < k; i++) a[l + i] = b[i];
    free(b);
}

void mergeSort(int* a, int l, int h){
    if(l < h){
        int m = (l + h) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, h);
        merge(a, l, m, h);
    } else return;
}

int partition(int* a, int l, int h, int t){
    int i = l, j = l;
    while(i <= h){
        if(a[i] <= a[t]){
            swap(&a[i], &a[j]);
            j++;
        }
        i++;
    }
    return j - 1;
}

void QSort(int* a, int l, int h){
    if(l >= h) return;
    int p = h;
    int m = partition(a, l, h, p);
    QSort(a, l, m - 1);
    QSort(a, m + 1, h);
}
