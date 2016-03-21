#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_STACKS 20

int stacks[MAX_STACKS] = {0};
int target[MAX_STACKS] = {0};

int pos = 0;
int operation_count = 0;

int score;
int stack_count;
bool holding = false;
int i;
char c;
 
char str[] = "Your score is: ";

FILE *f;

int main(int argc, char *argv[]) {

    /*
     * Read in the data file
     */
    f = fopen(argv[1], "r");
    if(!f) {
        printf("YIKES!!! opening %s. Errno %d: %s\n", argv[1], errno, strerror(errno));
        return 1;
    }

    fscanf(f, "%d", &stack_count);

    for(i = 0; i < stack_count; i++) {
        fscanf(f, "%d", &(stacks[i]));
    }

    for(i = 0; i < stack_count; i++) {
        fscanf(f, "%d", &(target[i]));
    }

    fclose(f);

    do {
        operation_count++;
        scanf("%c", &c);
        switch(c) {
        case 'L':
            pos--;
            break;
        case 'R':
            pos++;
            break;
        case 'P':
            if(!holding) {
                stacks[pos]--;
                holding = true;
            }
            break;
        case 'D':
            if(holding) {
                stacks[pos]++;
                holding = false;
            }
            break;
        default:
            operation_count--;
            break;
        }

    } while(c != 'X');

    for(i = 0; i < 200; i++) {
        printf("\n");
    }
    printf("stacks:");
    for(i = 0; i < stack_count; i++) {
        printf("\t%d", stacks[i]);
    }
    printf("\n");

    printf("target:");
    for(i = 0; i < stack_count; i++) {
        printf("\t%d", target[i]);
    }
    printf("\n");

    printf("robot :");
    for(i = 0; i < stack_count; i++) {
        printf("\t");
        if(pos == i) {
            printf("^");
        }
    }
    printf("\n\n");

    score = operation_count;
    for(i = 0; i < stack_count; i++) {
        int dif = stacks[i] - target[i];
        dif = dif >= 0 ? dif : -dif; // absolute value
        score += dif * dif * dif * dif;
    }

    printf("%s%d\n", str, score);
    return 0;
}

