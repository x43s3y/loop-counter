#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int menu_options()
{
    int answer;
    printf("Press 1 for reading a file and saving the results to a file.\nPress 2 for reading a file and showing the results to the screen.\nPress 3 for typing a code and saving the results to a file\nPress 4 for typing a code and showing the results to the screen.\n");
    printf("Answer: ");
    scanf("%d", &answer);
    return answer;
}

int file_ends_with(const char *name, const char *extension)
{
    const char *ldot = strrchr(name, '.');
    if (ldot != NULL)
    {
        return strncmp(ldot + 1, extension, 3) == 0;
    }
    return 0;
}

int while_operators_count(FILE *fp)
{
    char line[100];
    int if_count = 0, while_count = 0;
    rewind(fp);
    if (fp == NULL)
    {
        printf("File can not be read...");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp))
    {
        int i = 0;
        while (line[i] != '\0')
        {
            if ('w' == line[i])
            {
                if ('h' == line[i + 1])
                {
                    if ('i' == line[i + 2])
                    {
                        if ('l' == line[i + 3])
                        {
                            if ('e' == line[i + 4])
                            {
                                if ('(' == line[i + 5] || ' ' == line[i + 5])
                                    if_count++;
                            }
                        }
                    }
                }
            }
            i++;
        }
    }
    return if_count;
}

int for_operators_count(FILE *fp)
{
    char line[100];
    int for_count = 0;
    rewind(fp);
    if (fp == NULL)
    {
        printf("File can not be read...");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp))
    {
        int i = 0;
        while (line[i] != '\0')
        {
            if ('f' == line[i])
            {
                if ('o' == line[i + 1])
                {
                    if ('r' == line[i + 2])
                    {
                        if ('(' == line[i + 3] || ' ' == line[i + 3])
                            for_count++;
                    }
                }
            }
            i++;
        }
    }
    return for_count;
}

int empty_spaces(FILE *fp)
{
    if (fp == NULL)
    {
        printf("File can not be read...");
        exit(1);
    }
    char line[100];
    int empty_lines = 0, i;

    while (fgets(line, sizeof(line), fp))
    {
        for (i = 0; i < strlen(line); i++)
        {
            if (strlen(line) == 1)
            {
                if (line[i] == '\n')
                    empty_lines++;
            }
        }
    }
    return (empty_lines);
}

void write_result_to_file(FILE *fp, int empty_lines, int for_count, int while_count)
{
    fputs("empty lines: ", fp);
    fprintf(fp, "%d", empty_lines);
    fputc('\n', fp);
    fputs("for count: ", fp);
    fprintf(fp, "%d", for_count);
    fputc('\n', fp);
    fputs("while count: ", fp);
    fprintf(fp, "%d", while_count);
}

int main()
{
    FILE *read_file, *written_file;
    char READ_FILENAME[_MAX_FNAME], WRITTEN_FILENAME[_MAX_FNAME], file_content[SHRT_MAX], emptying_buffer[1];
    int empty_space, for_count, while_count, answer;
    answer = menu_options();

    if (answer == 1 || answer == 2)
    {
        gets(emptying_buffer);
        do
        {
            printf("Enter file you want to  be read: ");
            gets(READ_FILENAME);
        } while (!file_ends_with(READ_FILENAME, "c"));

        read_file = fopen(READ_FILENAME, "r");
    }
    else if (answer == 3 || answer == 4)
    {
        printf("Write your code: ");
        gets(emptying_buffer);
        gets(file_content);
        read_file = fopen("abc.txt", "w+");
        fputs(file_content, read_file);
    }
    empty_space = empty_spaces(read_file);
    for_count = for_operators_count(read_file);
    while_count = while_operators_count(read_file);
    fclose(read_file);
    if (answer == 3 || answer == 4)
        remove("abc.txt");

    if (answer == 1 || answer == 3)
    {
        printf("Enter file you want to write results: ");
        gets(WRITTEN_FILENAME);
        written_file = fopen(WRITTEN_FILENAME, "w");

        write_result_to_file(written_file, empty_space, for_count, while_count);
        fclose(written_file);
    }
    else
    {
        printf("Empty lines: %d\n", empty_space);
        printf("FOR operator count: %d\n", for_count);
        printf("WHILE operator count: %d", while_count);
    }

    return 0;
}