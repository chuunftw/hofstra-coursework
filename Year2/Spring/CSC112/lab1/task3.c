#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>   // For fork()
#include <sys/wait.h> // For waitpid()

// Shared data
char **words;
int word_count = 0;

// Function to check if a character is a vowel
int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

// Process function for printing words starting with vowels
void *print_vowels(void *arg) {
    for (int i = 0; i < word_count; i++) {
        if (is_vowel(words[i][0])) {
            printf("Vowel: %s\n", words[i]);
        }
    }
    exit(0);
}

// Process function for printing words starting with consonants
void *print_consonants(void *arg) {
    for (int i = 0; i < word_count; i++) {
        if (!is_vowel(words[i][0])) {
            printf("Consonant: %s\n", words[i]);
        }
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word1> <word2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize shared data
    word_count = argc - 1;
    words = &argv[1];

    // Create threads (now processes)
    pid_t vow_pid, cons_pid;
    
    vow_pid = fork();
    if (vow_pid == 0) {
        // Child process for vowels
        print_vowels(NULL);
    }
    
    cons_pid = fork();
    if (cons_pid == 0) {
        // Child process for consonants
        print_consonants(NULL);
    }

    // Wait for threads (now processes) to finish
    waitpid(vow_pid, NULL, 0);
    waitpid(cons_pid, NULL, 0);

    return EXIT_SUCCESS;
}