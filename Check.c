#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Declare Structure
struct person {
    char name [50];
    int age;
    double weight, income;
};
// Declare Function
int count_line(FILE *open);
int strindex (struct person *pointer, char const *string[]);
void store_in_structure(struct person *pointer, char *string, FILE *open);
void cmp(struct person *pointer, char const *string[], FILE *open);

int main(int argc, char const *argv[]) {
    char c = 0;
    int cnt_line = 0;
    char number [3][6]; // array containing age,weigh,salary
    if (argc == 8) {
        FILE *p = fopen("bigdata.txt","r");
        FILE *p1 = fopen("out1.txt","w");
// CHECK HOW MANY LINE IN A FILE
        cnt_line = count_line(p);
        rewind(p);
// Create Dynamic Memory for big data
        struct person *ptr;
        ptr = (struct person *) malloc(cnt_line * sizeof(struct person));
// Create string to store data in a line
        char *str = (char *)malloc(1000*sizeof(char));
// Store big data in Dynamic Memory by function
        for (int i = 0; i <= cnt_line-1; i++) {
            store_in_structure(ptr+i,str,p);
            //printf("%s %d %.1f %.1f\n",(ptr+i)->name,(ptr+i)->age,(ptr+i)->weight,(ptr+i)->income);
        }
        for (int i = 0; i <= cnt_line - 1; i++) {
            cmp((ptr+i),argv,p1);
        }
        fclose(p);
        fclose(p1);
// Create structure to store argument
    }else {
        printf("ERROR in COMMAND LINE\n");
     }
    return 0;
}

// DEFINE Function
// Compare argument function
void cmp(struct person *pointer, char const *string[], FILE *open) {
    //int length = 0;
    //int j = 0;
    //length = strlen(string[1]);
    //char string_name [length + 1];
    // for (int i = strlen(pointer->name)-length; i <= strlen(pointer->name); i++) {
    //     string_name[j] = pointer->name[i];
    //     ++j;
    // }
    //printf("%s\n",string_name);
    if (strindex(pointer, string) == 1 || strcmp(string[1],"*") == 0) {
        if ((atoi(string[2]) <= pointer->age && pointer->age <= atoi(string[3]))
            ||(strcmp(string[2],"*") == 0 && pointer->age <= atoi(string[3]))
            ||(atoi(string[2]) <= pointer->age && strcmp(string[3],"*") == 0)) {
                //Check weight
                if ((atof(string[4]) <= pointer->weight && pointer->weight <= atof(string[5]))
                    ||(strcmp(string[4],"*") == 0 && pointer->weight <= atof(string[5]))
                    ||(atof(string[4]) <= pointer->weight && strcmp(string[5],"*") == 0)) {
                        // Check income
                        if ((atof(string[6]) <= pointer->income && pointer->income <= atof(string[7]))
                            ||(strcmp(string[6],"*") == 0 && pointer->income <= atof(string[7]))
                            ||(atof(string[6]) <= pointer->income && strcmp(string[7],"*") == 0)) {
                                fprintf(open,"%s %d %.1f %.1f\n", pointer->name, pointer->age, pointer->weight, pointer->income);
                        }else printf("FAILED income\n");// CHECKING PURPOSE
                }else printf("FAILED weight\n");// CHECKING PURPOSE
        }else printf("FAILED age\n");// CHECKING PURPOSE
        //fputs(pointer->name,open);
    }else printf("FAILED name\n"); // CHECKING PURPOSE
}
// Count line function
int count_line(FILE *open){
    int count = 0;
    int c;
    c = fgetc(open);
    while (c != EOF) {
        if (c == '\n') {
            count += 1;
        }
        c = fgetc(open);
    }
    rewind(open);
    return count;
}
// store in structure function
void store_in_structure(struct person *pointer, char *string, FILE *open) {
    char number[3][6];
    int j = 0, z = 0, t = 0;
    fgets(string,1000,open); // Read each line
    for (int i = 0; i <= strlen(string)-1; i++) {
        if (*(string+i) == 32) {
            if (*(string+i+1) == 32) {
            }else if (*(string+i+1) >= 65 && *(string+i+1) <= 122){
                pointer->name[j] = 32;
                ++j;
            }else if (*(string+i+1) >= 48 && *(string+i+1) <= 57){
                continue;
            }
        }else if ((*(string+i) >= 65 && *(string+i) <= 122)) {
            pointer->name[j] = *(string+i); //Store name data from str to structure
            ++j;
        }else if((*(string+i) >= 48 && *(string+i) <= 57) || *(string+i) == 46) {
            number[z][t] = *(string+i);
            ++t;
            if (*(string+i+1) == ' ' || *(string+i+1) == '\n') {
                number[z][t] = '\0';
                ++z;
                t = 0;
            }
        }
    }
    pointer->age = atoi(number[0]);
    pointer->weight = atof(number[1]);
    pointer->income = atof(number[2]);
}

// Check name
int strindex (struct person *pointer, char const *string[]){
    int check = 0, boolean = 0;
    char temp[strlen(string[1])+1]; //Create string temp and then copy the argv[1] into it in order to check the space in name put in the command line
    strcpy(temp,string[1]);
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] == 32){
            check = 1; // When the console pass SPACE check will be 1
        }
    }
    // Check 2 options : 1) there is spaces in name 2) no space
    if (check == 0) {
        for (int i = 0; i <= strlen(pointer->name); i++) {
            for (int j = i, k = 0; temp[k] != '\0'; j++, k++) {
                temp[k] = pointer->name[j];
            }
            // Check whether the name from the big data contains the first command line or not
            if (strcmp(temp,string[1]) == 0){
                boolean = 1; // TRUE
            }
            // Check after the mutual character whether the name still has name or not
            for (int m = i; m <= strlen(pointer->name); m++) {
                if (pointer->name[m] == 32) boolean = 0;
            }
        }
    }else{
        for (int i = strlen(pointer->name)-strlen(string[1]), j = 0; i <= strlen(pointer->name); i++) {
            temp[j] = pointer->name[i];
            ++j;
        }
        if (strcmp(temp,string[1]) == 0) boolean = 1;

    }
    return boolean;
}
