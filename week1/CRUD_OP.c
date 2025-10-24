#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    int id;
    char name[20];
    int age;
};

// add new user
void addUser() {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    struct User u;
    printf("Enter ID: ");
    scanf("%d", &u.id);
    printf("Enter Name: ");
    scanf("%s", u.name);
    printf("Enter Age: ");
    scanf("%d", &u.age);

    fprintf(fp, "%d %s %d\n", u.id, u.name, u.age);
    fclose(fp);

    printf("User added\n");
}

// display user
void displayUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    struct User u;
    printf("User Records\n");
    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        printf("ID: %d | Name: %s | Age: %d\n", u.id, u.name, u.age);
    }
    fclose(fp);
}

// update user
void updateUser() {
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    int id, found = 0;
    struct User u;
    printf("Enter ID to update ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        if (u.id == id) {
            printf("Enter Name: ");
            scanf("%s", u.name);
            printf("Enter Age: ");
            scanf("%d", &u.age);
            found = 1;
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }

    fclose(fp);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        printf("User updated !\n");
    else
        printf("User not found\n");
}

// delete a user
void deleteUser() {
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    int id, found = 0;
    struct User u;
    printf("Enter ID to delete: \n");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        if (u.id == id) {
            found = 1;
            continue; 
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }

    fclose(fp);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        printf("User deleted\n");
    else
        printf("User not found \n");
}

int main() {
    addUser();
    displayUsers();
    updateUser();
    deleteUser();
    displayUsers();
    

    return 0;
}
