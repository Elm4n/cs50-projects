#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }
    unsigned char *temp = malloc(512);
    char *filename = malloc(3 * sizeof(int));
    if (temp == NULL || filename == NULL)
    {
        fclose(card);
        if (temp != NULL)
            free(temp);
        if (filename != NULL)
            free(filename);
        return 1;
    }
    int image = 0;
    FILE *imgf = NULL;
    while (fread(temp, sizeof(unsigned char), 512, card) == 512)
    {
        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && (temp[3] & 0xf0) == 0xe0)
        {
            if (imgf != NULL)
            {
                fclose(imgf);
            }
            sprintf(filename, "%03i.jpg", image);
            imgf = fopen(filename, "w");
            if (imgf == NULL)
            {
                free(temp);
                free(filename);
                fclose(card);
                return 1;
            }
            fwrite(temp, 1, 512, imgf);
            image++;
        }
        else if (image != 0)
        {
            if (imgf != NULL)
            {
                fwrite(temp, 1, 512, imgf);
            }
        }
    }
    if (imgf != NULL)
    {
        fclose(imgf);
    }
    free(temp);
    free(filename);
    fclose(card);
    return 0;
}
