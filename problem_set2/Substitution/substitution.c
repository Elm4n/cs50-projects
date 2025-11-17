#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int cypher(string text, string key);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution ");
        return 1;
    }
    else if (strlen (argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        char ichar = argv[1][i];
        if (!isalpha(ichar))
        {
            printf("Usage: ./substitution");
            return 1;
        }
        for (int j = 0; j < n; j++)
        {
            char jchar = argv[1][j];
            if (toupper(ichar) == toupper(jchar) && i != j)
            {
            printf("Usage: ./substitution");
            return 1;
            }
        }
    }
    string key = argv[1];
    string text = get_string("plaintext: ");
    return cypher(text, key);
}
    int cypher(string text, string key)
    {
        int value;
        char c2;
        int n1 = strlen(text);
        printf("ciphertext: ");
        for (int k = 0; k < n1; k++)
        {
            char c = text[k];
            if (isalpha(c) && isupper(c))
            {
                value = c - 65;
                c2 = toupper(key[value]);
            }
            else if (isalpha(c) && islower(c))
            {
                value = c - 97;
                 c2 = tolower(key[value]);
            }
            else
            {
            c2 = c;
            }
            printf("%c", c2);
        }
        printf("\n");
        return 0;
}
