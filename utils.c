#include <stdlib.h>

char *generate_random_word(size_t word_len) {
    char *word = malloc((word_len + 1) * sizeof(char));

    for (size_t i = 0; i < word_len; i++)
        word[i] = (char)(26 * (rand() / (RAND_MAX + 1.0)) + 97);

    word[word_len] = '\0';
    return word;
}