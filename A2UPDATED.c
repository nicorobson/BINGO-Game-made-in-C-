#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void printArray(int r1[], int r2[], int r3[], int r4[], int r5[], int *matchingNums, int size2);
int bingoCheck(int *numsArray, int size1, int *matchingNums, int size2);
int contains(int *arrayToSearch, int size, int elemToFind);
void printCallList(int *calledNums, int calledNumsSize);

int main(int argc, char *argv[]){

    FILE *myFile = fopen(argv[2], "r");
    int numsArray[25];
    int calledNums[75];   //will be our ADT 
    int matchingNums[75];
    const char *filename = argv[2];
    int dupeFlag = 0;
    int validIntsFlag = 0;
    int rangeFlag = 0;
    
    if (myFile == NULL){
        fprintf(stderr, "%s is nonexistent or unreadable\n",filename);
        exit(3);
    }

    for (int i = 0; i < 25; i++){
        fscanf(myFile, "%d,", &numsArray[i]);
    }

    for (int i = 0; i < 24; i++) {
        for (int j = i + 1; j < 25; j++) {
            if (numsArray[i] == numsArray[j]) {
                dupeFlag = 1;
            }
        }
    }

    for (int i = 0; i < 25; i++) {
        if (numsArray[i] > 75 || numsArray[i] < 0) {
            validIntsFlag = 1;
        }
    }

    for (int i = 0; i < 21; i += 5) {
        if (numsArray[i] > 15 || numsArray[i] < 1) {
            rangeFlag = 1;
            break;
        }
    }

    for (int i = 1; i < 22; i += 5) {
        if (numsArray[i] > 30 || numsArray[i] < 16) {
            rangeFlag = 1;
            break;
        }
    }

    for (int i = 2; i < 23; i += 5) {
        if (numsArray[i] > 45 || numsArray[i] < 31 && numsArray[i] != 0) {
            rangeFlag = 1;
            break;
        }
    }

    for (int i = 3; i < 24; i += 5) {
        if (numsArray[i] > 60 || numsArray[i] < 46) {
            rangeFlag = 1;
            break;
        }
    }

    for (int i = 4; i < 25; i += 5) {
        if (numsArray[i] > 75 || numsArray[i] < 61) {
            rangeFlag = 1;
            break;
        }
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s seed cardFile\n", argv[0]);
        exit(1);
    }

    if (!atoi(argv[1])) {
        fprintf(stderr, "Expected integer seed, but got %s\n", argv[1]);
        exit(2);
    } 

    if (numsArray[12] != 0) {
        fprintf(stderr, "%s has bad format\n", filename);
        exit(4);
    }
    else if (dupeFlag == 1 || validIntsFlag == 1 || rangeFlag == 1) {
        fprintf(stderr, "%s has bad format\n", filename);
        exit(4);
    }
    

    fclose(myFile);
    int row_one[5] = {numsArray[0], numsArray[1], numsArray[2], numsArray[3], numsArray[4]};
    int row_two[5] = {numsArray[5], numsArray[6], numsArray[7], numsArray[8], numsArray[9]};
    int row_three[5] = {numsArray[10], numsArray[11], numsArray[12], numsArray[13], numsArray[14]};
    int row_four[5] = {numsArray[15], numsArray[16], numsArray[17], numsArray[18], numsArray[19]};
    int row_five[5] = {numsArray[20], numsArray[21], numsArray[22], numsArray[23], numsArray[24]};
    
    int seed = atoi(argv[1]);
    srand(seed);
    int upper = 75;
    int lower = 1;
    int flag = 0;

    for (int i = 0; i <  75; i++) {
                calledNums[i] = 0;
            }

    while (flag == 0) {
        char *input;
        int call;
        
        printf("enter any non-enter key for Call (q to quit): ");
        input[0] = '\0';
        scanf("%[^\n]", input);
        scanf("%*c");

        if (strcmp("q", input)) {
            call = (rand() % (upper - lower + 1)) + lower;
            while (contains(calledNums, 75, call) == 1) {
                call = (rand() % (upper - lower + 1)) + lower;
            }

            for (int i = 0; i < 75; i++) {
                if (calledNums[i] == 0) {
                    calledNums[i] = call;
                    break;
                } 
            }
            printf("\n");
            printCallList(calledNums, 75);
            printf("\n");

            for (int i = 0; i < 25; i++) {
                if (numsArray[i] == call) {
                    for (int i = 0; i < 75; i++) {
                        if (matchingNums[i] == 0) {
                            matchingNums[i] = call;
                            break;
                        } 
                    }
                }
            }
            printArray(row_one, row_two, row_three, row_four, row_five, matchingNums, 75);
            printf("\n");
            flag = bingoCheck(numsArray, 25, matchingNums, 75);
        }
        else {
            break;
        }

    }
    printf("\n");
    if (flag == 1) {
        printf("WINNER");
        printf("\n");
    }
    return 0;
} 


void printArray(int r1[], int r2[], int r3[], int r4[], int r5[], int *matchingNums, int size2){
    printf(" L   I   N   U   X\n");
    for (int i = 0; i < 5; i++){
        if (contains(matchingNums, size2, r1[i]) == 1) {
            printf("%02dm ", r1[i]);
        }
        else {
            printf("%02d  ", r1[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++){
        if (contains(matchingNums, size2, r2[i]) == 1) {
            printf("%02dm ", r2[i]);
        }
        else {
            printf("%02d  ", r2[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++){
        if (contains(matchingNums, size2, r3[i]) == 1) {
            printf("%02dm ", r3[i]);
        }
        else {
            printf("%02d  ", r3[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++){
        if (contains(matchingNums, size2, r4[i]) == 1) {
            printf("%02dm ", r4[i]);
        }
        else {
            printf("%02d  ", r4[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++){
        if (contains(matchingNums, size2, r5[i]) == 1) {
            printf("%02dm ", r5[i]);
        }
        else {
            printf("%02d  ", r5[i]);
        }
    }
}


int bingoCheck(int *numsArray, int size1, int *matchingNums, int size2) {
    if (contains(matchingNums, 75, numsArray[0]) == 1 && contains(matchingNums, 75, numsArray[1]) == 1 && contains(matchingNums, 75, numsArray[2]) == 1 && contains(matchingNums, 75, numsArray[3]) == 1 && contains(matchingNums, 75, numsArray[4]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[5]) == 1 && contains(matchingNums, 75, numsArray[6]) == 1 && contains(matchingNums, 75, numsArray[7]) == 1 && contains(matchingNums, 75, numsArray[8]) == 1 && contains(matchingNums, 75, numsArray[9]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[10]) == 1 && contains(matchingNums, 75, numsArray[11]) == 1 && contains(matchingNums, 75, numsArray[13]) == 1 && contains(matchingNums, 75, numsArray[14]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[15]) == 1 && contains(matchingNums, 75, numsArray[16]) == 1 && contains(matchingNums, 75, numsArray[17]) == 1 && contains(matchingNums, 75, numsArray[18]) == 1 && contains(matchingNums, 75, numsArray[19]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[20]) == 1 && contains(matchingNums, 75, numsArray[21]) == 1 && contains(matchingNums, 75, numsArray[22]) == 1 && contains(matchingNums, 75, numsArray[23]) == 1 && contains(matchingNums, 75, numsArray[24]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[0]) == 1 && contains(matchingNums, 75, numsArray[5]) == 1 && contains(matchingNums, 75, numsArray[10]) == 1 && contains(matchingNums, 75, numsArray[15]) == 1 && contains(matchingNums, 75, numsArray[20]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[1]) == 1 && contains(matchingNums, 75, numsArray[6]) == 1 && contains(matchingNums, 75, numsArray[11]) == 1 && contains(matchingNums, 75, numsArray[16]) == 1 && contains(matchingNums, 75, numsArray[21]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[2]) == 1 && contains(matchingNums, 75, numsArray[7]) == 1 && contains(matchingNums, 75, numsArray[17]) == 1 && contains(matchingNums, 75, numsArray[22]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[3]) == 1 && contains(matchingNums, 75, numsArray[8]) == 1 && contains(matchingNums, 75, numsArray[13]) == 1 && contains(matchingNums, 75, numsArray[18]) == 1 && contains(matchingNums, 75, numsArray[23]) == 1 ) {
        return 1;
    }
    else if (contains(matchingNums, 75, numsArray[4]) == 1 && contains(matchingNums, 75, numsArray[9]) == 1 && contains(matchingNums, 75, numsArray[14]) == 1 && contains(matchingNums, 75, numsArray[19]) == 1 && contains(matchingNums, 75, numsArray[24]) == 1 ) {
        return 1;
    }
    else {
        return 0;
    }
}

int contains(int *arrayToSearch, int size, int elemToFind) {
    for (int i = 0; i < size; i++) {
        if (arrayToSearch[i] == elemToFind) {
            return 1;
        }
    }
    return 0;
}


void printCallList(int *calledNums, int calledNumsSize) {
    printf("Call list: ");
    for (int i = 0; i < calledNumsSize; i++) {
        if (calledNums[i] >= 1 && calledNums[i] <= 15) {
            printf("L%02d, ", calledNums[i]);
        }
        else if (calledNums[i] >= 16 && calledNums[i] <= 30) {
            printf("I%02d, ", calledNums[i]);
        }
        else if (calledNums[i] >= 31 && calledNums[i] <= 45) {
            printf("N%02d, ", calledNums[i]);
        }
        else if (calledNums[i] >= 46 && calledNums[i] <= 60) {
            printf("U%02d, ", calledNums[i]);
        }
        else if (calledNums[i] >= 61 && calledNums[i] <= 75) {
            printf("X%02d, ", calledNums[i]);
        }
    }
}