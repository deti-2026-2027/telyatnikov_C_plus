#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 676767

typedef struct Node {
    char *word;
    unsigned long cnt;
    struct Node *next;
} Node;

typedef struct {
    char *word;
    unsigned long cnt;
} Wordcnt;


unsigned long hash(const char *str) {
    unsigned long h = 6742;
    int c;
    while ((c = (unsigned char)*str++)) {
        h = ((h << 5) + h) + c;
    }
    return h;
}

void hash_insert(Node **table, const char *word, unsigned long *unique_cnt) {
    unsigned long t = hash(word) % TABLE_SIZE;
    Node *curr = table[t];

    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0) {
            curr->cnt++;
            return;
        }
        curr = curr->next;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    node->word = (char *)malloc(strlen(word) + 1);

    strcpy(node->word, word);
    node->cnt = 1;
    node->next = table[t];
    table[t] = node;

    (*unique_cnt)++;
}

int comparator(const void *a, const void *b) {
    return ((Wordcnt *)b)->cnt - ((Wordcnt *)a)->cnt;
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");

    Node **table = (Node **)calloc(TABLE_SIZE, sizeof(Node *));
    unsigned long total_words = 0;
    unsigned long unique_words = 0;

    char str[256];
    unsigned long i = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isalnum((unsigned char)c)) {
            if (i < 256 - 1) {
                str[i++] = (char)tolower((unsigned char)c);
            }
        } 
        else {
            if (i > 0) {
                str[i] = '\0';
                hash_insert(table, str, &unique_words);
                total_words++;
                i = 0;
            }
        }
    }
    if (i > 0) {
        str[i] = '\0';
        hash_insert(table, str, &unique_words);
        total_words++;
    }

    fclose(file);

    if (total_words == 0) {
        free(table);
        return 0;
    }

    Wordcnt *m = (Wordcnt *)malloc(unique_words * sizeof(Wordcnt));

    unsigned long l = 0;
    for (unsigned long i = 0; i < TABLE_SIZE; i++) {
        Node *curr = table[i];
        while (curr != NULL) {
            m[l].word = curr->word;
            m[l].cnt = curr->cnt;
            l++;
            curr = curr->next;
        }
    }

    qsort(m, unique_words, sizeof(Wordcnt), comparator);

    for (unsigned long i = 0; i < unique_words; i++) {
        double procent = ((double)m[i].cnt / (double)total_words) * 100.0;
        printf("%s %lu %.2f%%\n", m[i].word, m[i].cnt, procent);
    }

    for (unsigned long i = 0; i < TABLE_SIZE; i++) {
        Node *curr = table[i];
        while (curr != NULL) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp->word);
            free(tmp);
        }
    }
    free(table);
    free(m);

    return 0;
}
