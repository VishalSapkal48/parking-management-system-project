#include<stdio.h>
   
#include <string.h>
#include <stdlib.h>

// Structure to represent an owner
struct Owner {
    char name[50];
    int flatNumber;
    char birthdate[20];
    int parkingSpot;
};

// Function to initialize the number of flats in the society
int initializeFlatCount() {
    return 4;
}

// Function to allocate a flat to an owner
void allocateFlat(struct Owner owners[], int flatNumber, char name[], char birthdate[]) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].flatNumber == 0) {
            owners[i].flatNumber = flatNumber;
            strcpy(owners[i].name, name);
            strcpy(owners[i].birthdate, birthdate);
            printf("Flat %d allocated to %s\n", flatNumber, name);
            return;
        }
    }
    printf("All flats are occupied.\n");
}

// Function to check if a flat is available
int isFlatAvailable(struct Owner owners[], int flatNumber) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].flatNumber == flatNumber) {
            return 0; // Flat is not available
        }
    }
    return 1; // Flat is available
}

// Function to allocate parking spots for the society (between 100 and 500)
void allocateParking(struct Owner owners[], int parkingStart, int parkingEnd) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].parkingSpot == 0) {
            owners[i].parkingSpot = parkingStart;
            printf("Parking spot %d allocated to flat owner\n", parkingStart);
            parkingStart++;
        }
    }
}

// Function to allocate a parking spot to a flat owner
void allocateParkingToOwner(struct Owner owners[], int flatNumber, int parkingSpot) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].flatNumber == flatNumber) {
            owners[i].parkingSpot = parkingSpot;
            printf("Parking spot %d allocated to %s\n", parkingSpot, owners[i].name);
            return;
        }
    }
    printf("Flat not found.\n");
}

// Function to check if there's an open parking spot
int checkOpenParking(struct Owner owners[], int parkingStart, int parkingEnd) {
    for (int i = parkingStart; i <= parkingEnd; i++) {
        int isOccupied = 0;
        for (int j = 0; j < 4; j++) {
            if (owners[j].parkingSpot == i) {
                isOccupied = 1;
                break;
            }
        }
        if (!isOccupied) {
            return i;
        }
    }
    return 0; // No open parking spots
}

// Function to search for an owner by name or flat number
void searchOwner(struct Owner owners[], char query[]) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(owners[i].name, query) == 0 || owners[i].flatNumber == atoi(query)) {
            printf("Owner found: %s (Flat: %d)\n", owners[i].name, owners[i].flatNumber);
            return;
        }
    }
    printf("Owner not found.\n");
}

// Function to view all owners
void viewAllOwners(struct Owner owners[], int flatCount) {
    printf("List of Owners:\n");
    for (int i = 0; i < flatCount; i++) {
        if (owners[i].flatNumber != 0) {
            printf("Name: %s, Flat: %d, Parking Spot: %d\n", owners[i].name, owners[i].flatNumber, owners[i].parkingSpot);
        }
    }
}

// Function to delete an owner by flat number
void deleteOwner(struct Owner owners[], int flatNumber) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].flatNumber == flatNumber) {
            owners[i].flatNumber = 0;
            owners[i].parkingSpot = 0;
            printf("Owner of flat %d has been deleted.\n", flatNumber);
            return;
        }
    }
    printf("Flat not found.\n");
}

// Function to update owner information by flat number
void updateOwner(struct Owner owners[], int flatNumber, char newName[], char newBirthdate[]) {
    for (int i = 0; i < 4; i++) {
        if (owners[i].flatNumber == flatNumber) {
            strcpy(owners[i].name, newName);
            strcpy(owners[i].birthdate, newBirthdate);
            printf("Owner info for flat %d has been updated.\n", flatNumber);
            return;
        }
    }
    printf("Flat not found.\n");
}

// Function to count owners with the same name
int countSameNameOwners(struct Owner owners[], char name[], int flatCount) {
    int count = 0;
    for (int i = 0; i < flatCount; i++) {
        if (strcmp(owners[i].name, name) == 0) {
            count++;
        }
    }
    return count;
}

// Function to count owners with the same birthday date
int countSameBirthdateOwners(struct Owner owners[], char birthdate[], int flatCount) {
    int count = 0;
    for (int i = 0; i < flatCount; i++) {
        if (strcmp(owners[i].birthdate, birthdate) == 0) {
            count++;
        }
    }
    return count;
}

// Function to calculate the age of an owner based on birthdate
int calculateOwnerAge(struct Owner owner) {
    // Assuming birthdate is in the format "DD-MM-YYYY"
    int birthYear, birthMonth, birthDay;
    sscanf(owner.birthdate, "%d-%d-%d", &birthDay, &birthMonth, &birthYear);

    // Assuming the current year is 2023
    int currentYear = 2023;
    int currentMonth = 9; // Assuming the current month is September

    int age = currentYear - birthYear;

    // Adjust age if the birth month has not occurred yet this year
    if (birthMonth > currentMonth) {
        age--;
    }

    return age;
}

int main() {
    int flatCount = initializeFlatCount();
    struct Owner *owners = (struct Owner *)malloc(flatCount * sizeof(struct Owner));

    // Initialize owner structures
    for (int i = 0; i < flatCount; i++) {
        owners[i].flatNumber = 0;
        owners[i].parkingSpot = 0;
    }

    int parkingStart = 100;
    int parkingEnd = 500;
    int choice;

    while (1) {
    	printf("===========================================================================================");
        printf("\nParking Allocation System Menu:\n");
        printf("1. Allocate Flat\n");
        printf("2. Check Flat Availability\n");
        printf("3. Allocate Parking for Society\n");
        printf("4. Allocate Parking to Flat Owner\n");
        printf("5. Check Open Parking\n");
        printf("6. Search Owner by Name or Flat No\n");
        printf("7. View All Owners\n");
        printf("8. Delete Owner by Flat\n");
        printf("9. Update Owner Info by Flat\n");
        printf("10. Count Same Name Owners\n");
        printf("11. Count Same Birthday Date Owners\n");
        printf("12. Calculate Owner Age\n");
        printf("0. Exit\n");
        printf("===========================================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                free(owners);
                exit(0);

            case 1: {
                int flatNumber;
                char name[50], birthdate[20];
                printf("Enter Flat Number: ");
                scanf("%d", &flatNumber);
                printf("Enter Owner Name: ");
                scanf("%s", name);
                printf("Enter Owner Birthdate (DD-MM-YYYY): ");
                scanf("%s", birthdate);
                allocateFlat(owners, flatNumber, name, birthdate);
                break;
            }

            case 2: {
                int flatNumber;
                printf("Enter Flat Number: ");
                scanf("%d", &flatNumber);
                int available = isFlatAvailable(owners, flatNumber);
                if (available) {
                    printf("Flat %d is available.\n", flatNumber);
                } else {
                    printf("Flat %d is not available.\n", flatNumber);
                }
                break;
            }

            case 3:
                allocateParking(owners, parkingStart, parkingEnd);
                break;

            case 4: {
                int flatNumber, parkingSpot;
                printf("Enter Flat Number: ");
                scanf("%d", &flatNumber);
                printf("Enter Parking Spot: ");
                scanf("%d", &parkingSpot);
                allocateParkingToOwner(owners, flatNumber, parkingSpot);
                break;
            }

            case 5: {
                int openSpot = checkOpenParking(owners, parkingStart, parkingEnd);
                if (openSpot != 0) {
                    printf("Open parking spot found: %d\n", openSpot);
                } else {
                    printf("No open parking spots available.\n");
                }
                break;
            }

            case 6: {
                char query[50];
                printf("Enter Owner Name or Flat Number: ");
                scanf("%s", query);
                searchOwner(owners, query);
                break;
            }

            case 7:
                viewAllOwners(owners, flatCount);
                break;

            case 8: {
                int flatNumber;
                printf("Enter Flat Number to Delete: ");
                scanf("%d", &flatNumber);
                deleteOwner(owners, flatNumber);
                break;
            }

            case 9: {
                int flatNumber;
                char newName[50], newBirthdate[20];
                printf("Enter Flat Number to Update: ");
                scanf("%d", &flatNumber);
                printf("Enter New Owner Name: ");
                scanf("%s", newName);
                printf("Enter New Owner Birthdate (DD-MM-YYYY): ");
                scanf("%s", newBirthdate);
                updateOwner(owners, flatNumber, newName, newBirthdate);
                break;
            }

            case 10: {
                char name[50];
                printf("Enter Owner Name to Count: ");
                scanf("%s", name);
                int count = countSameNameOwners(owners, name, flatCount);
                printf("Number of owners with the same name '%s': %d\n", name, count);
                break;
            }

            case 11: {
                char birthdate[20];
                printf("Enter Birthdate to Count: ");
                scanf("%s", birthdate);
                int count = countSameBirthdateOwners(owners, birthdate, flatCount);
                printf("Number of owners with the same birthdate '%s': %d\n", birthdate, count);
                break;
            }

            case 12: {
                int flatNumber;
                printf("Enter Flat Number to Calculate Age: ");
                scanf("%d", &flatNumber);
                for (int i = 0; i < flatCount; i++) {
                    if (owners[i].flatNumber == flatNumber) {
                        int age = calculateOwnerAge(owners[i]);
                        printf("Age of owner of flat %d is %d years.\n", flatNumber, age);
                        break;
                    }
                }
                break;
            }

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
