#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count(string text);

int main(void)
{
    string text = get_string("Text: ");

    int index = count(text);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n" , index);
    }
}
int count(string text)
{
    int n = strlen(text);
    float l = 0;
    float w = 1;
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        if ((text [i] >= 65 && text [i] <= 90) || ( text [i] >= 97 && text [i] <= 122 ))
        {
            l++;
        }
        if (text [i] == 32)
        {
            w++;
        }
        if (text [i] == 63 || text [i] == 46 || text [i] == 33)
        {
            s++;
        }
    }
    float L = 100 * (l / w);
    float S = 100 * (s / w);
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
