#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 16
#define MAX_STUD 26
#define MAX_CLASS 3
#define EMPTY '~'
#define DELETED '!'

typedef struct{
    char block;
    bool paid;
    char lName[MAX_LEN];
    char key;
}Student;

typedef struct{
    Student students[MAX_STUD];
}studList;

typedef studList ClassList[MAX_CLASS];

void initialize(ClassList A);
int hash(char letter);
void insertStud(Student arr[], int count, ClassList A);
void removeWithdrawnStudents(ClassList A);
void updateStudentsWhoPaid(ClassList A);
Student* reportToTeacher(ClassList A, char block, int* count);
Student* askYza(ClassList A);
Student* messageFromMiss(ClassList A);
void display(Student* paidList, int count, char block);
// void displayDict(ClassList A){
//     printf("\n================ STUDENT LIST ================\n");
//     for(int c = 0; c < MAX_CLASS; c++){
//         char block = 'A' + c;
//         printf("\n--- BLOCK %c ---\n", block);
//         bool hasStudents = false;

//         for(int i = 0; i < MAX_STUD; i++){
//             Student s = A[c].students[i];
//             if(s.key != EMPTY && s.key != DELETED){
//                 printf("%-10s | %-5s | Paid: %s\n",
//                        s.lName,
//                        (s.block == block) ? "OK" : "?",
//                        s.paid ? "Yes" : "No");
//                 hasStudents = true;
//             }
//         }

//         if(!hasStudents){
//             printf("[No students in this block]\n");
//         }
//     }
//     printf("==============================================\n");
// }

// void displayClassList(ClassList A) {
//     printf("\n=================== HASH TABLE CONTENTS ===================\n");
//     for (int classIdx = 0; classIdx < MAX_CLASS; classIdx++) {
//         printf("\n>>> BLOCK %c <<<\n", 'A' + classIdx);
//         printf("Idx | Key |   Last Name   | Paid\n");
//         printf("------------------------------------\n");
//         for (int studIdx = 0; studIdx < MAX_STUD; studIdx++) {
//             Student s = A[classIdx].students[studIdx];
//             if (s.key == EMPTY) {
//                 printf("%3d |  %c  | %-13s | %s\n", studIdx, s.key, "(EMPTY)", "-");
//             } else if (s.key == DELETED) {
//                 printf("%3d |  %c  | %-13s | %s\n", studIdx, s.key, "(DELETED)", "-");
//             } else {
//                 printf("%3d |  %c  | %-13s | %s\n",
//                        studIdx, s.key, s.lName,
//                        s.paid ? "Yes" : "No");
//             }
//         }
//     }
//     printf("===========================================================\n");
// }

int main(){
    Student arr[39] = {
    {'A', false, "Anderson"},  
    {'A', false, "Benson"},    
    {'A', false, "Clarkson"},  
    {'A', true,  "Baker"},
    {'A', false, "Brooks"},
    {'A', true,  "Brown"},
    {'A', false, "Carter"},
    {'A', true,  "Collins"},
    {'A', false, "Cook"},
    {'A', true,  "Cooper"},
    {'A', false, "Nguyen"},
    {'A', true,  "Perez"},
    {'A', false, "Ramos"},

    // --- BLOCK B (13 students) ---
    {'B', false, "Allen"},     
    {'B', false, "Bates"},     
    {'B', false, "Cruz"},      
    {'B', true,  "Davis"},
    {'B', false, "Diaz"},
    {'B', true,  "Edwards"},
    {'B', false, "Evans"},
    {'B', true,  "Flores"},
    {'B', false, "Garcia"},
    {'B', true,  "Green"},
    {'B', false, "Hall"},
    {'B', true,  "Hughes"},
    {'B', true,  "Smith"},

    // --- BLOCK C (13 students) ---
    {'C', false, "Arnold"},   
    {'C', false, "Barker"},    
    {'C', false, "Carson"},    
    {'C', true,  "Cagayan"},
    {'C', false, "Johnson"},
    {'C', true,  "Jones"},
    {'C', false, "King"},
    {'C', true,  "Kelly"},
    {'C', false, "Lewis"},
    {'C', true,  "Lopez"},
    {'C', false, "Miller"},
    {'C', true,  "Moore"},
    {'C', false, "Nelson"}
    };

    ClassList A;
    initialize(A);
    insertStud(arr, 39, A);

    int inp;
    printf("Enter the testCase: ");
    scanf("%d", &inp);
    int aCount = 0, bCount = 0, cCount = 0;
    Student* paidListA;
    Student* paidListB;
    Student* paidListC;
    switch(inp){
    case 1: 
        paidListA = reportToTeacher(A, 'A', &aCount);
        paidListB = reportToTeacher(A, 'B', &bCount);
        paidListC = reportToTeacher(A, 'C', &cCount);

        // displayClassList(A);
        display(paidListA, aCount, 'A');
        display(paidListB, bCount, 'B');
        display(paidListC, cCount, 'C');
        
        free(paidListA);
        free(paidListB);
        free(paidListC);
        break;
        
    case 2:
        //report
        paidListA = reportToTeacher(A, 'A', &aCount);
        paidListB = reportToTeacher(A, 'B', &bCount);
        paidListC = reportToTeacher(A, 'C', &cCount);
        display(paidListA, aCount, 'A');
        display(paidListB, bCount, 'B');
        display(paidListC, cCount, 'C');

        free(paidListA);
        free(paidListB);
        free(paidListC);

        //yza messages
        printf("Yza: Hala Jose naay bagong namayad I apil silas lista\n");   
        printf("Jose: HUH, KAPOYA\n");
        
        updateStudentsWhoPaid(A);

        aCount = 0;  
        bCount = 0;  
        cCount = 0;  

        paidListA = reportToTeacher(A, 'A', &aCount);
        paidListB = reportToTeacher(A, 'B', &bCount);
        paidListC = reportToTeacher(A, 'C', &cCount);

        display(paidListA, aCount, 'A');
        display(paidListB, bCount, 'B');
        display(paidListC, cCount, 'C');
        
        free(paidListA);
        free(paidListB);
        free(paidListC);
        break;
        
    case 3:
        //report
        paidListA = reportToTeacher(A, 'A', &aCount);
        paidListB = reportToTeacher(A, 'B', &bCount);
        paidListC = reportToTeacher(A, 'C', &cCount);
        display(paidListA, aCount, 'A');
        display(paidListB, bCount, 'B');
        display(paidListC, cCount, 'C');
        
        free(paidListA);
        free(paidListB);
        free(paidListC);

        //missMessages
        printf("Jose: Hold on I got a text from miss....\n");   
        printf("Jose: ""These students withdrew? Please make another list for them and send them to me? **CRASHES OUT**""\n");

        removeWithdrawnStudents(A);

        aCount = 0;  
        bCount = 0;  
        cCount = 0;  
        //report
        paidListA = reportToTeacher(A, 'A', &aCount);
        paidListB = reportToTeacher(A, 'B', &bCount);
        paidListC = reportToTeacher(A, 'C', &cCount);
        display(paidListA, aCount, 'A');
        display(paidListB, bCount, 'B');
        display(paidListC, cCount, 'C');
        
        free(paidListA);
        free(paidListB);
        free(paidListC);
        break;
        
        default:
        break;
    }
}

void display(Student* paidList, int count, char block){
    printf("\n================ PAID STUDENTS (BLOCK %c) ================\n", block);
    if(count == 0){
        printf("[No paid students in this block]\n");
    } else {
        for(int i = 0; i < count; i++){
            printf("%-10s | Paid: %s\n", 
                   paidList[i].lName,
                   paidList[i].paid ? "Yes" : "No");
        }
    }
    printf("==========================================================\n");
}

void initialize(ClassList A){
    int ndx;
    for(ndx = 0; ndx < MAX_CLASS; ndx++){
        int idx;
        for(idx = 0; idx < MAX_STUD; idx++){
            A[ndx].students[idx].key = EMPTY;
        }
    }
}

int hash(char letter){
    return letter - 'A';
}

void insertStud(Student arr[], int count, ClassList A){
    int studHash, classHash;
    for(int ndx = 0; ndx < count; ndx++){
        classHash = hash(arr[ndx].block), studHash = hash(arr[ndx].lName[0]);
        int stop = (studHash - 1 + MAX_STUD) % MAX_STUD;
        for( ;studHash != stop && A[classHash].students[studHash].key != EMPTY; studHash = (studHash + 1) % MAX_STUD){}
        if(A[classHash].students[studHash].key == EMPTY){
            A[classHash].students[studHash] = arr[ndx];
            A[classHash].students[studHash].key = arr[ndx].lName[0];
        }
    }
}


//TO DO
void removeWithdrawnStudents(ClassList A){

    //call message from miss
    Student* withdrawn = messageFromMiss(A);
    int studHash, classHash;
    for(int ndx = 0; withdrawn[ndx].block != 'X'; ndx++){
        studHash = hash(withdrawn[ndx].lName[0]), classHash = hash(withdrawn[ndx].block);
        int stop = (studHash - 1 + MAX_STUD) % MAX_STUD;
        while(studHash != stop && strcmp(A[classHash].students[studHash].lName, withdrawn[ndx].lName) != 0){
            studHash = (studHash + 1) % MAX_STUD; 
        }

        if(strcmp(A[classHash].students[studHash].lName, withdrawn[ndx].lName) == 0){
            A[classHash].students[studHash].key = DELETED;
            A[classHash].students[studHash].paid = false;
        }
    }


    free(withdrawn);
}


//TO DO
void updateStudentsWhoPaid(ClassList A){
    Student* paid = askYza(A);
    int studHash, classHash;
    for(int ndx = 0; paid[ndx].block != 'X'; ndx++){
        studHash = hash(paid[ndx].lName[0]), classHash = hash(paid[ndx].block);
        int stop = (studHash - 1 + MAX_STUD) % MAX_STUD;
        while(studHash != stop && strcmp(A[classHash].students[studHash].lName, paid[ndx].lName) != 0){
            studHash = (studHash + 1) % MAX_STUD; 
        }

        if(strcmp(A[classHash].students[studHash].lName, paid[ndx].lName) == 0){
            A[classHash].students[studHash].paid = true;
        }
    }

    free(paid);
}

//TO DO
Student* reportToTeacher(ClassList A, char block, int* count){
    Student* paidList = (Student*)malloc(sizeof(Student)*MAX_STUD);
    int hashClass = hash(block);
    for(int ndx = 0; ndx < MAX_STUD; ndx++){
        if(A[hashClass].students[ndx].key != DELETED && A[hashClass].students[ndx].key != EMPTY && A[hashClass].students[ndx].paid == true){
            paidList[*count] = A[hashClass].students[ndx];
            (*count)++;
        }
    }

    return paidList;
}


Student* askYza(ClassList A){
    Student* newPaid = (Student*)malloc(sizeof(Student)*MAX_STUD);
    int count = 0;
    //1st 3 students from each block
    for(int ndx = 0; ndx < 3; ndx++){
        for(int idx = 0; idx < 3; idx++){
            strcpy(newPaid[count].lName , A[ndx].students[idx].lName);
            newPaid[count].block = A[ndx].students[idx].block;
            newPaid[count].key = A[ndx].students[idx].key;
            newPaid[count].paid = true;
            count++;
        }
    }
    //sentinel value
    strcpy(newPaid[count].lName , "xxx");
    newPaid[count].block = 'X';
    newPaid[count].key = 'X';
    newPaid[count].paid = false;

    return newPaid;
}

Student* messageFromMiss(ClassList A){
    //1st three students from each block
    Student* withdrawn = (Student*)malloc(sizeof(Student)*MAX_STUD);
    int ndx;
    for(ndx = 0; ndx < 3; ndx++){
        strcpy(withdrawn[ndx].lName , A[ndx].students[3].lName);
        withdrawn[ndx].block = A[ndx].students[3].block;
        withdrawn[ndx].key = A[ndx].students[3].key;
        withdrawn[ndx].paid = A[ndx].students[3].paid;
    }
    //sentinel value
    strcpy(withdrawn[ndx].lName , "xxx");
    withdrawn[ndx].block = 'X';
    withdrawn[ndx].key = 'X';
    withdrawn[ndx].paid = false;
    
    return withdrawn;
}