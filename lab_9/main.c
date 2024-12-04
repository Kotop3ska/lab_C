#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
 
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
 
int main(int argc, char **argv) { 
    if (argc < 3) { 
        printf("Usage: program \"text\" -command [arguments]\n"); 
        return 1; 
    } 
 
    char *text = argv[1]; 
    char *command = argv[2]; 
    printf("Your text:\n%s\n", text); 
 
    if (strcmp(command, "-info") == 0) { 
        float mid_len = info(text); 
        printf("Middle word length: %.2f\n", mid_len); 
    }  
    else if (strcmp(command, "-create") == 0) { 
        char **vowel_words = create(text); 
        printf("Words ending with a vowel:\n"); 
        int i; 
        for (i = 0; vowel_words[i] != NULL; i++) { 
            printf("%s\n", vowel_words[i]); 
            free(vowel_words[i]); 
        } 
        free(vowel_words); 
    } 
     
    else if (strcmp(command, "-delete") == 0) { 
        if (argc != 4) { 
            printf("Error: -delete requires an additional argument K (number of the digit group to delete)\n"); 
            return 1; 
        } 
        int k = atoi(argv[3]); 
        if (k <= 0) { 
            printf("Error: K must be a positive number\n"); 
            return 1; 
        } 
        char *result = delete(text, k); 
        printf("Text after deletion:\n%s\n", result); 
        free(result); 
    }  
    else { 
        printf("Error: Unknown command %s\n", command); 
        return 1;  
    } 
    return 0; 
}