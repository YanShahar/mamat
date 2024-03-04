#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define grade range
#define MAX_GRADE 100
#define MIN_GRADE 0

static FILE *f;

int median(char *argv, int size);
int compare(const void *a, const void *b);

int main(int argc, char **argv) {
    // Decide input method
    if (argc == 1 || !strcmp("-", argv[1])) {
        f = stdin;
    } else {
        f = fopen(argv[1], "r");
    }

    // Check for errors
    if (!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    int result = median(argv[1], argc - 2); // Pass the correct size to median function
    printf("%d\n", result); // Print median

    fclose(f);
    return 0;
}

int median(char *argv, int size) {
    int *arr = (int *)calloc(size, sizeof(int)); // Use calloc to initialize to zero
    int grade;
    int retval;
    int line = 0;

    while (line < size) {
        retval = fscanf(f, "%d", &grade);
        if (retval != 1) { // Error
            fprintf(stderr, "Error: not a number\n");
            free(arr);
            exit(1);
        } else if (grade < MIN_GRADE || grade > MAX_GRADE) { // Check in range
            fprintf(stderr, "Error at line %d: grade %d invalid\n", (line + 1), grade);
            free(arr);
            exit(1);
        } else {
            arr[line] = grade; // Add grade to array
            line++;
        }
    }

    int median;
    qsort(arr, size, sizeof(int), compare); // Sort array to easily find median
    median = arr[size / 2]; // Choose median from the sorted array
    free(arr);
    return median;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
} // Compare function for qsort
