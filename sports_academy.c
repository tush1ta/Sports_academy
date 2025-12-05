/*
=======================================================
   SPORTS ACADEMY MANAGEMENT SYSTEM
-------------------------------------------------------
   Developed By:
      Vandana Yadav   | SAP ID: 590029262
      Tushita Sharma  | SAP ID: 590029121
=======================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define SPORTS 8
#define SEAT_LIMIT 5

char sports[SPORTS][25] = {
    "Badminton",
    "Cricket",
    "Basketball",
    "Hockey",
    "Golf",
    "Swimming",
    "Table Tennis",
    "Football"
};

struct Student {
    char name[50];
    long long sap_id;
    int roll;
    char address[80];
    float height;
    float weight;
    char sport[25];
};

int countSeats(char *sport);
void addStudent(struct Student *s);
void displayStudents();
void searchStudent(int roll);

int main() {

    int choice;
    struct Student s;

    /* AUTHOR DISPLAY AT START */
    printf("=============================================\n");
    printf("Program Developed By:\n");
    printf("Vandana Yadav   (SAP ID: 590029262)\n");
    printf("Tushita Sharma  (SAP ID: 590029121)\n");
    printf("=============================================\n\n");

    do {
        printf("===== SPORTS ACADEMY MANAGEMENT SYSTEM =====\n");
        printf("1. Enroll Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll ID\n");
        printf("4. Exit\n\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addStudent(&s);
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                printf("Enter Roll ID: ");
                scanf("%d", &choice);
                searchStudent(choice);
                break;

            case 4:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid selection.\n");
        }

    } while(1);
}


/* ADD STUDENT (CALL BY REFERENCE) */
void addStudent(struct Student *s) {

    FILE *fp = fopen(FILE_NAME, "ab");
    int option;

    if (!fp) {
        printf("File error.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", s->name);

    printf("Enter SAP ID: ");
    scanf("%lld", &s->sap_id);

    printf("Enter Roll ID: ");
    scanf("%d", &s->roll);

    printf("Enter Address: ");
    scanf(" %[^\n]", s->address);

    printf("Enter Height (cm): ");
    scanf("%f", &s->height);

    printf("Enter Weight (kg): ");
    scanf("%f", &s->weight);

    printf("\nChoose Sport:\n");
    for(int i = 0; i < SPORTS; i++)
        printf("%d. %s\n", i + 1, sports[i]);

    printf("Select option: ");
    scanf("%d", &option);

    if(option < 1 || option > SPORTS) {
        printf("Invalid sport selection.\n");
        fclose(fp);
        return;
    }

    strcpy(s->sport, sports[option - 1]);

    if(countSeats(s->sport) >= SEAT_LIMIT) {
        printf("No seats available in %s.\n", s->sport);
        fclose(fp);
        return;
    }

    fwrite(s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Student enrolled successfully.\n");
}


/* COUNT SEATS (CALL BY VALUE) */
int countSeats(char *sport) {

    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student temp;
    int count = 0;

    if(!fp) return 0;

    while(fread(&temp, sizeof(struct Student), 1, fp)) {
        if(strcmp(temp.sport, sport) == 0)
            count++;
    }
    fclose(fp);
    return count;
}


/* DISPLAY STUDENTS */
void displayStudents() {

    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student s;

    if(!fp) {
        printf("No records available.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-20s %-8s %-8s %-15s\n",
            "Roll ID", "Name", "SAP ID", "Address", "Height", "Weight", "Sport");

    printf("--------------------------------------------------------------------------\n");

    while(fread(&s, sizeof(struct Student), 1, fp)) {

        printf("%-10d %-20s %-15lld %-20s %-8.2f %-8.2f %-15s\n",
                s.roll, s.name, s.sap_id, s.address,
                s.height, s.weight, s.sport);
    }

    fclose(fp);
}


/* SEARCH STUDENT */
void searchStudent(int roll) {

    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student s;
    int found = 0;

    if(!fp) {
        printf("No records available.\n");
        return;
    }

    while(fread(&s, sizeof(struct Student), 1, fp)) {

        if(s.roll == roll) {
            printf("\nStudent Found\n");
            printf("Name   : %s\n", s.name);
            printf("SAP ID : %lld\n", s.sap_id);
            printf("Address: %s\n", s.address);
            printf("Height : %.2f\n", s.height);
            printf("Weight : %.2f\n", s.weight);
            printf("Sport  : %s\n", s.sport);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");

    fclose(fp);
}
