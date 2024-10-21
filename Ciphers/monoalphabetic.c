#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char *generateKey()
{
    char *key = malloc(27);
    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(NULL));
    for (int i = 0; i < 26; i++)
    {
        int j = rand() % (26 - i);
        key[i] = a[j];
        a[j] = a[25 - i];
    }
    key[26] = '\0';
    return key;
}

char *encrypt(char *inp, char *key)
{
    char *out = malloc(strlen(inp) + 1);
    strcpy(out, inp);
    for (int i = 0; out[i]; i++)
    {
        if (isupper(out[i]))
        {
            out[i] = key[out[i] - 'A'];
        }
        else if (islower(out[i]))
        {
            out[i] = tolower(key[out[i] - 'a']);
        }
    }
    return out;
}

char *decrypt(char *inp, char *key)
{
    char *out = malloc(strlen(inp) + 1);
    strcpy(out, inp);
    for (int i = 0; out[i]; i++)
    {
        if (isupper(out[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (key[j] == out[i])
                {
                    out[i] = 'A' + j;
                    break;
                }
            }
        }
        else if (islower(out[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (tolower(key[j]) == out[i])
                {
                    out[i] = 'a' + j;
                    break;
                }
            }
        }
    }
    return out;
}

int main()
{
    char inp[] = "Yo, it's neuralnets!";
    char *key = generateKey();
    printf("Random key: %s\n", key);
    char *out = encrypt(inp, key);
    printf("Encrypted : %s\n", out);
    char *out1 = decrypt(out, key);
    printf("Decrypted : %s\n", out1);
    free(key);
    free(out);
    free(out1);
    return 0;
}