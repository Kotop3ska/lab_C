#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <locale.h>


#define MAX_SENTENCE_LEN 1024
#define MAX_WORD_LEN 256
#define MAX_COMMAND_LEN 64

typedef struct
{
    char text[MAX_SENTENCE_LEN];
    char command[MAX_COMMAND_LEN];
    char param[MAX_WORD_LEN];
} ParsedLine;

int parseLine(const char *line, ParsedLine *parsed)
{
    strcpy(parsed->param, "");
    int result = sscanf(line, "\"%[^\"]\" -%s %s", parsed->text, parsed->command, parsed->param);

    if (result < 2)
    {
        return -1;
    }

    return 0;
}

 
float info(const char* s) { 
    int len_words = 0; 
    int counter = 0;    
    int in_word = 0;   
  
 int i; 
    for (i = 0; i <= strlen(s); i++) { 
        if (isalpha(s[i])) { 
            len_words++; 
            in_word = 1;  
        } else if (in_word) { 
            counter++; 
            in_word = 0;   
        } 
    } 
 
    if (counter == 0) { 
        return 0.0f;  
    } 
 
    return (float)len_words / counter;  
} 
 
int is_vowel(char c) { 
    c = tolower(c); 
    return (c == 'a' || c == 'e' || c == 'i' || c == 'y' || c == 'o'); 
} 
 
char** create(const char* s) {
    char** result = (char**)malloc(sizeof(char*));
    if (!result) {
        printf("ERROR: Memory allocation failed\n");
        exit(1);
    }
    result[0] = NULL;

    int index = 0;
    int word_start = -1;

    for (int i = 0; i <= strlen(s); i++) {
        if (isalpha(s[i])) { 
            if (word_start == -1 && (i == 0 || s[i - 1] == ' ')) {
                word_start = i; 
            }
        } else if (word_start != -1) { 
            if (s[i] == '.' || s[i] == ',' || s[i] == ';' || s[i] == ' ' || s[i] == ':' || s[i] == '\0') { 
                int len = i - word_start; 
                char* word = (char*)malloc(len + 1);
                if (!word) {
                    printf("ERROR: Memory allocation failed\n");
                    exit(1);
                }
                strncpy(word, s + word_start, len); 
                word[len] = '\0';

                if (is_vowel(word[len - 1])) {
                    result[index] = word;
                    index++;
                    result = (char**)realloc(result, (index + 1) * sizeof(char*));
                    if (!result) {
                        printf("ERROR: Memory allocation failed\n");
                        exit(1);
                    }
                    result[index] = NULL;
                } else {
                    free(word); 
                }
            }
            word_start = -1;
        }
       
    }
    return result;
}
 
 
char* delete(const char* s, int k) { 
    char* result = (char*)malloc(strlen(s) + 1); 
    if (!result) { 
        printf("ERROR: Memory allocation failed\n"); 
        return NULL; 
    } 
 
    int current_block = 0; 
    int i = 0, j = 0; 
 
    while (s[i] != '\0') { 
        if (isdigit(s[i])) { 
            current_block++;  
            if (current_block % k == 0) { 
                while (isdigit(s[i])) { 
                    i++; 
                } 
            } else { 
                while (isdigit(s[i])) { 
                    result[j++] = s[i++]; 
                } 
            } 
        } else { 
            result[j++] = s[i++]; 
        } 
    } 
 
    result[j] = '\0';  
    return result; 
} 
 
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc < 3)
    {
        printf("Ошибка: недостаточно аргументов.\n");
        printf("Формат: main.exe \"входной файл\" \"выходной файл\"\n");
        return 1;
    }

    char *input = argv[1];
    char *output = argv[2];

    FILE *inputFile = fopen(input, "r");
    FILE *outputFile = fopen(output, "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Ошибка открытия файлов.\n");
        return 1;
    }

    char line[MAX_SENTENCE_LEN];
    ParsedLine parsed;

    while (fgets(line, sizeof(line), inputFile))
    {
        line[strcspn(line, "\n")] = 0;

        if (parseLine(line, &parsed) == 0)
        {
            if (strcmp(parsed.command, "info") == 0)
            {
                
                float middle = info(parsed.text);

                fprintf(outputFile, "%f\n", middle);
            }
            else if (strcmp(parsed.command, "create") == 0)
            {
                char **result = create(parsed.text);

                for (int i = 0; result[i] != NULL; i++)
                {
                    fprintf(outputFile, "%s ", result[i]);
                    free(result[i]);
                }

                fprintf(outputFile, "\n");

                free(result);
            }
            else if (strcmp(parsed.command, "delete") == 0)
            {
                if (parsed.param[0] == '\0')
                {
                    printf("Ошибка: для команды -delete необходимо передать 1 дополнительный аргумент (цифру).\n");
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                }

                int k = atoi(parsed.param); 
                if (k <= 0) { 
                    printf("Ошибка: К – положительное число.\n"); 
                    return 1; 
                } 
                char *result = delete(parsed.text, k); 
                fprintf(outputFile, "%s\n", result);

                fprintf(outputFile, "\n");

            
            }
            else
            {
                printf("Ошибка разбора строки: %s\n", line);
                fclose(inputFile);
                fclose(outputFile);
                return 1;
            }
        }
        else
        {
            printf("Ошибка разбора строки: %s\n", line);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
