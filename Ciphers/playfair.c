#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool isvisited(char* arr, int size, char c){
    for (int i = 0; i < size; i++){
        if (arr[i] == c)
            return true;
    }
    return false;
}

char** keymatrix(char *text, int size){
    char *set = (char*) malloc(sizeof(char) * 25);
    char **key = (char**)malloc(sizeof(char) * 5);

    for (int i = 0; i < 5; i++)
        key[i] = (char*)malloc(sizeof(char) * 5);

    int visited = 0;
    for (int i = 0; i < size && visited < 25; i++){
        if (!isvisited(set, i, text[i])){
            set[visited] = text[i];
            visited++;
        }
    }

    for (char c = 'a'; visited < 25; c++){
        if (c == 'j'){
            continue;
        }
        if(!isvisited(set, visited, c)){
            set[visited] = c;
            visited ++;
        }
    }

    int k = 0;
    for (int i=0; i < 5; i++){
        for (int j=0; j < 5; j++){
            key[i][j] = set[k++];
        }
    }

    free(set);
    return key;  
}

void get_coord(char a, char b, int *i1, int *j1, int *i2, int *j2, char** key){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if (a == key[i][j]){
                *i1 = i;
                *j1 = j;
            }
            if (b == key[i][j]){
                *i2 = i;
                *j2 = j;
            }
        }
    }
}

char* encode(char* plain, char **key, int size){
    for(int i = 0; i < size; i++){
        if (plain[i] == 'j'){
            plain[i] = 'i';
        }
    }
    char* ans = (char*)malloc(sizeof(char) * size);
    int i = 0, j = 0;
    while (i < size){
        char a = plain[i];
        char b;
        if ((i + 1) < size){
            b = plain[i+1];
        }else{
            b = 'x';
        }
        if (a == b){
            ans[j++] = a;
            ans[j++] = 'x';
            i++;
        }
        else{
            ans[j++] = a;
            ans[j++] = b;
            i+=2;
        }
    }
    ans[j] = '\0';
    int ans_size = (int)strlen(ans);
    char* encript_text = (char*)malloc(sizeof(char) * (ans_size + 1));

    for(int k = 0; k < ans_size; k+=2){
        int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
        get_coord(ans[k], ans[k+1], &i1, &j1, &i2, &j2, key);
        if (i1 == i2){
            encript_text[k] = key[i1][(j1 + 1) % 5];
            encript_text[k+1]  = key[i2][(j2 + 1) % 5];
        }
        else if (j1 == j2){
            encript_text[k] = key[(i1 + 1) % 5][j1];
            encript_text[k+1] = key[(i2 + 1) % 5][j2];
        }
        else{
            encript_text[k] = key[i1][j2];
            encript_text[k+1] = key[i2][j1];
        }
    }

    encript_text[ans_size] = '\0';
    free(ans);
    return encript_text;
}

char *decode(char* enc, char** key, int size){

    char* decript_text = (char*)malloc(sizeof(char) * size + 1);
    for(int i = 0; i < size; i+=2){
        int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
        get_coord(enc[i], enc[i+1], &i1, &j1, &i2, &j2, key);
        if(i1 == i2){
            decript_text[i] = key[i1][(j1 + 4) % 5];
            decript_text[i+1] = key[i2][(j2 + 4) % 5];
        }
        else if (j1 == j2){
            decript_text[i] = key[(i1 + 4) % 5][j1];
            decript_text[i+1] = key[(i2 + 4) % 5][j2];
        }
        else{
            decript_text[i] = key[i1][j2];
            decript_text[i+1] = key[i2][j1];
        }
    }
    decript_text[size] = '\0';
    
    char* ans = (char*)malloc(sizeof(char) * (size + 1));
    int j = 0;
    for (int i = 0; i < size; i++){
        if (decript_text[i] != 'x'){
            ans[j++] = decript_text[i];
        }
    }
    ans[j] = '\0';

    return ans;
}

int main(){
    char mess[] = "hihowareyou";
    char k[] = "neuralnets";
    char **key = keymatrix(k, strlen(k));
    printf("Key:\n");
    
    for (int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    char *enc = encode(mess, key, strlen(mess));
    printf("Encode: %s\n", enc);

    char *dec = decode(enc, key, strlen(enc));
    printf("Decode: %s\n", dec);
}