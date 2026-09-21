//The program creates two threads (`vow` and `cons`) that print words starting with vowels and consonants, respectively, while maintaining the original sequence. It uses the syscall `sched_yield()` to allow threads to take turns.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sched.h>

// Shared data
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char **words;
int word_count = 0;
int current_index = 0;
int turn = 0; // 0 for vow thread, 1 for cons thread

// Function to check if a character is a vowel
int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

// Thread function for printing words starting with vowels
void *print_vowels(void *arg) {
    //while (current_index < word_count) {           // no longer needed
        //pthread_mutex_lock(&mutex);                // no longer needed
        //if (turn == 0) {                          // Check if it's the vowel thread's turn
        for(int i = 0; i < word_count;i++){        //iterate through all words this time
            if (is_vowel(words[i][0])) {
                printf("Vowel: %s\n", words[i]);
                //current_index++;
                // turn = 1; // Pass control to the consonant thread **only if a vowel was printed**          // not needed anymore
            }
        }
        //pthread_mutex_unlock(&mutex);           //no longer needed
        /*else {
            sched_yield(); // Yield CPU control to the other thread
        }*/
    //}
    return NULL;
}

// Thread function for printing words starting with consonants
void *print_consonants(void *arg) {    
    //while (current_index < word_count) {       // no longer needed
        // pthread_mutex_lock(&mutex);           // Lock before checking turn not needed
        //if (turn == 1) { // Check if it's the consonant thread's turn
        for(int i =0; i< word_count;i++){        //iterate through all the words
            if (!is_vowel(words[i][0])) {
                printf("Consonant: %s\n", words[i]);
                //current_index++;
                //turn = 0; // Pass control back to vowel thread **only if a consonant was printed**     not needed
            }
        }
        //pthread_mutex_unlock(&mutex);          //not needed
        /*else {
            sched_yield(); // Yield CPU control to the other thread
        }*/
    //}
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word1> <word2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize shared data
    word_count = argc - 1;
    words = &argv[1];

    /*// Create threads
    pthread_t vow_thread, cons_thread;
    pthread_create(&vow_thread, NULL, print_vowels, NULL);
    pthread_create(&cons_thread, NULL, print_consonants, NULL);

    // Wait for threads to finish
    pthread_join(vow_thread, NULL);
    pthread_join(cons_thread, NULL);*/

    pthread_t vow_thread, cons_thread;
    pthread_create(&vow_thread, NULL, print_vowels, NULL);
    pthread_create(&cons_thread, NULL, print_consonants, NULL);
    pthread_join(vow_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    return EXIT_SUCCESS;
}