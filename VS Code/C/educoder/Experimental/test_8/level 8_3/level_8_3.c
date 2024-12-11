#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Usage: %s <input_file> <search_str> <replace_str>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *search_str = argv[2];
    char *replace_str = argv[3];

    FILE *fp_in = fopen(input_file, "r");
    if (fp_in == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *fp_out = fopen("out.txt", "w");
    if (fp_out == NULL)
    {
        perror("Error opening output file");
        fclose(fp_in);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        char *pos = strstr(line, search_str);
        while (pos != NULL)
        {
            *pos = '\0';
            fprintf(fp_out, "%s%s", line, replace_str);
            strcpy(line, pos + strlen(search_str));
            pos = strstr(line, search_str);
        }
        fprintf(fp_out, "%s", line);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
