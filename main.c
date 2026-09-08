#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n");
        printf("=================================================\n");
        printf("        \033[1;33mAddress Book - THARIS SELVARAJ\033[0m\n");
        printf("                \033[1;33m*** MENU ***\033[0m\n");
        printf("=================================================\n");
        printf("\n");
        printf("    1. Create contact\n");
        printf("    2. Search contact\n");
        printf("    3. Edit contact\n");
        printf("    4. Delete contact\n");
        printf("    5. List all contacts\n");
        printf("    6. Exit\n");
        printf("\n");
        printf("=================================================\n");

        printf("    Enter your choice: ");
        scanf("%d", &choice);
        int d;
        while ((d = getchar()) != '\n' && d != EOF); 
        printf("\n");
        
        switch (choice) 
        {
            case 1:
                printf("\n\033[1;2;34m[CREATING] Contact\033[0m\n");
                createContact(&addressBook);
                break;
            case 2:
                printf("\n\033[1;2;34m[SEARCHING] Contact\033[0m\n");
                int foundFlag = 0;
                searchContact(&addressBook, &foundFlag);
                break;
            case 3:
                printf("\n\033[1;2;34m[EDITING] Contact\033[0m\n");
                editContact(&addressBook);
                break;
            case 4:
                printf("\n\033[1;2;34m[DELETING] Contact\033[0m\n");
                deleteContact(&addressBook);
                break;
            case 5:
                /*
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice); */
                printf("\n\033[1;2;34m[LISTING] Contact\033[0m\n");
                listContacts(&addressBook);
                break;
            case 6:
                printf("\n\033[1;2;34m[EXITING] Contact list! \033[0m\n");
                printf("\n\033[1;2;33mSaving and Exiting...\033[0m\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
