#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  RMIT University Vietnam
  Course: EEET2448 Computing Engineering
  Semester: 2018A
  Assessment: Group Project
  Author & ID : Pham Nguyen Thanh Nhan (s356953), Dang Ba Minh (s3685119), Le Hoang Phong (s3634004), Luong Tan Huy (s3726121)
  Created date: 28 May 2018
  Acknowledgment: not applicable
*/

// Declare Structure
struct person {
    char name [50];
    int age;
    double weight, income;
};

// Declare Function
int count_line(FILE *open); // count number of line in bigdata, to identify the size of malloc
int strindex (struct person *pointer, char const *string[]); // check the name of person, a sub-function of cmp
void store_in_structure(struct person *pointer, char *string, FILE *open); // store bigdata value function
void cmp(struct person *pointer, char const *string[], FILE *open);// compare all parameters (age, weight, income etc)

// MAIN PROGRAMME
int main(int argc, char const *argv[]) {
    char c = 0;
    int cnt_line = 0;
    char number [3][6]; // declare array containing age,weigh,salary

    if (argc == 8) {
        FILE *p = fopen("bigdata.txt","r");
        FILE *p1 = fopen("out1.txt","w");
    // check number of line in the file
        cnt_line = count_line(p);
        rewind(p);
    // Create Dynamic Memory for big data
        struct person *ptr;
        ptr = (struct person *) malloc(cnt_line * sizeof(struct person));
    // Create string to store data in a line
        char *str = (char *)malloc(1000*sizeof(char));
    // Store big data in Dynamic Memory by "store_in_structure" function
        for (int i = 0; i <= cnt_line-1; i++) {
            store_in_structure(ptr+i,str,p);
        }
    // compare the command line with bigdata
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
/* Compare argument function
  Logic: compare the input in waterfall other: check name --> check age -> check weight --> check income
*/
void cmp(struct person *pointer, char const *string[], FILE *open) {
  // check name, by call function strindex
    if (strindex(pointer, string) == 0 || strcmp(string[1],"*") == 0) {
      //check age:
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
                        }else printf("FAILED income\n");// printf to testing purpose
                }else printf("FAILED weight\n");// printf to testing purpose
        }else printf("FAILED age\n");// printf to testing purpose
    }else printf("FAILED name\n"); // printf to testing purpose
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
/* logic: read each line of the bigdata and store all parameters in an array.
    Array is local variable.
*/
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

// Check name function: a function nested in "cmp" function (compare name function)
int strindex (struct person *pointer, char const *string[]){
    int check = 0,boolean = 0, cnt_space1 = 0, cnt_space2 = 0;
    for (int i = 0; i <= strlen(string[1])-1; i++) {
        if (string[1][i] == 32) {
            cnt_space1 += 1;
        }
    }
    // Create array to sperate command line
    char buff1[cnt_space1+1][7];
    for (int i = 0, z = 0, t = 0; i <= strlen(string[1]); i++) {
        buff1[z][t] = string[1][i];
        t++;
        if (string[1][i] == 32) {
            buff1[z][t-1] = '\0';
            ++z;
            t = 0;
        }
    }
    int count = 0;
    //printf("strlen %lu\n",strlen(buff1[0]));
    for (int i = 0; i <= cnt_space1; i++) {

        char temp[strlen(buff1[i]) + 1];
        temp[strlen(buff1[i])] = '\0';
        //printf("STRING%d\n",buff1[i][3] );
        //printf("SIZe %lu\n",sizeof(temp) );
        for (int t = 0; pointer->name[t] != '\0'; t++) {
            for (int j = 0; temp[j] != '\0'; j++) {
                temp[j] = pointer->name[j+t];
            }
            //printf("%s\n",temp);
            if (strcmp(temp,buff1[i]) == 0) {
                count += 1;
                break;
            }
        }
    }
    // printf("Count = %d\n",count );
    // printf("SPACE = %d\n",cnt_space1 );
    if (count >= cnt_space1+1) {
        boolean = 0;
        //printf("I'M HERE\n");
    }else boolean = 1;
    // char temp[strlen(buff1[cnt_space1]) + 1];
    // temp[strlen(buff1[cnt_space1])] = '\0';
    // for (int i = 0; temp[i] != '\0'; i++) {
    //         temp[i] = buff2[cnt_space2][i];
    //     }
    // if (strcmp(temp,buff1[cnt_space1]) == 0) {
    //     check = 1;
    // }
    // if (check == 1) {
    //     boolean = 0;
    //     int m = cnt_space2 - 1;
    //     for (int i = cnt_space1-1; i >= 0; i--) {
    //         while (m >= 0) {
    //             if (strcmp(buff1[i], buff2[m]) == 0) {
    //                 boolean = 0;
    //                 --m;
    //                 break;
    //             }else boolean = 1;
    //             --m;
    //         }
    //     }
    // }else boolean = 1;

return boolean;
}
