// 319046504 laviel@campus.technion.ac.il lavie lederman
// 206159527 shahary@campus.technion.ac.il shahar yankelovich

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRADE 100
#define MIN_GRADE 0

void min(FILE *f);

int main(int argc, char **argv) {
    FILE *f;
    //decide input method
    if(argc == 1 || !strcmp("-", argv[1])){
        f = stdin;
    }
    else{
        f = fopen(argv[1], "r");
    }
    //check for errors
    if(!f){
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }
    min(f);
    return 0;
}
void min(FILE *f){
    int grade;
    int retval;
    int min = 101;
    int line = 1;
    while(1){
        retval = fscanf(f, "%d", &grade);//read number from file
        if(retval == EOF){
            break;//finished
        }
        else if(retval != 1){
            //error
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }//check grade in range
        else if (grade < MIN_GRADE || grade > MAX_GRADE) {
            fprintf(stderr, "Error at line %d: grade %d invalid\n", line, grade);
            exit(1);
        }//update min grade
        else if(grade < min){
            min = grade;
        }
        line++;

    }//output minimal grade
    printf("%d\t", min);
}
