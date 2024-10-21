#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *encrypt(char *inp, int shift)
{
    char *out = malloc(strlen(inp) + 1);
    strcpy(out, inp);
    for (int i = 0; out[i]; i++)
    {
        if (isupper(out[i]))
        {
            out[i] = ((out[i] - 'A' + shift) % 26) + 'A';
        }
        else if (islower(out[i]))
        {
            out[i] = ((out[i] - 'a' + shift) % 26) + 'a';
        }
    }
    return out;
}

char *decrypt(char *inp, int shift)
{
    return encrypt(inp, 26 - shift);
}

int main()
{
    char inp[] = "Yo, it's neuralnets!";
    int shift = 3;
    char *out = encrypt(inp, shift);
    printf("Encrypted : %s\n", out);
    char *decrypted = decrypt(out, shift);
    printf("Decrypted : %s\n", decrypted);
    free(out);
    free(decrypted);
    return 0;
}