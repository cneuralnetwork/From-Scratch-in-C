#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char* generateKey(){
    char* key = malloc(sizeof(char) * 52);
    char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    srand(time(NULL));
    for(int i=0; i<26; i++){
        int j = rand() % (26 - i);
        key[i] = uppercase[j];
        key[i + 26] = lowercase[j];
        uppercase[j] = uppercase[25 - i];
        lowercase[j] = lowercase[25 - i];
    }
    key[52] = '\0';
    return key;
}

char* encrypt(char* inp, char* key){
    char* out = malloc(strlen(inp) + 1);
    strcpy(out, inp);
    for(int i=0; out[i]; i++){
        if(isupper(out[i])){
            out[i] = key[out[i] - 'A'];
        }else if(islower(out[i])){
            out[i] = key[out[i] - 'a' + 26];
        }
    }
    return out;
}

char* decrypt(char* inp, char* key){
    char* out = malloc(strlen(inp) + 1);
    strcpy(out, inp);
    for(int i=0; out[i]; i++){
        if(isupper(out[i])){
            for(int j=0; j<26; j++){
                if(key[j] == out[i]){
                    out[i] = 'A' + j;
                    break;
                }
            }
        }else if(islower(out[i])){
            for(int j=26; j<52; j++){
                if(key[j] == out[i]){
                    out[i] = 'a' + (j - 26);
                    break;
                }
            }
        }
    }
    return out;
}

int main(){
    char inp[] = "HellO, World!";
    char* key = generateKey();
    printf("Random key: %s\n", key);
    char* out = encrypt(inp, key);
    printf("Encrpyted : %s\n", out);
    char* out = decrypt(out, key);
    printf("Decrypted : %s\n", out);
    free(key);
    free(out);
    free(out);
    return 0;
}