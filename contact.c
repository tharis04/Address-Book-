#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep()
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void listContacts(AddressBook *addressBook) 
{
    // Printing the populated contacts
    printf("=========================================================================================\n");
    printf("                                \033[1;33m*** CONTACT LIST ***\033[0m\n");
    printf("=========================================================================================\n");
    printf("S No   %-15s %-12s %-8s %-25s %-15s\n", "Name", "Phone No", "Gender", "Email ID", "Location");
    printf("=========================================================================================\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].gender,addressBook->contacts[i].email,addressBook->contacts[i].location);
    }

    printf("=========================================================================================\n"); 
    sleep(1); // adds delay for 1 seconds
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook); // Function call
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// CREATE CONTACT -------------------------------------------------------------------------------------------------------------------------------

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    Contact newContact;

    // Step 1: Name
    getValidName(newContact.name);

    // Step 2: Phone
    getValidPhone(newContact.phone, addressBook);

    // Step 3: Email
    getValidEmail(newContact.email, addressBook);

    // Step 4: Gender
    getValidGender(newContact.gender);

    // Step 5: Location
    getValidLocation(newContact.location);

    // Step 6: Add to address book
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("\n\033[1;32m*** Contact added successfully! ***\033[0m\n");
    sleep(1);
}

void getValidName(char *name) 
{
    int valid;
    do {
        printf("Enter name: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';
        valid = 1;

        for (int i = 0; name[i] != '\0'; i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                valid = 0;
                printf("\033[1;31mInvalid name! Only alphabets allowed.\033[0m\n");
                break;
            }
        }
    } while (!valid);
}

void getValidPhone(char *phone, AddressBook *addressBook) 
{
    int valid;
    do {
        printf("Enter phone number: ");
        fgets(phone, 15, stdin);
        phone[strcspn(phone, "\n")] = '\0';
        valid = 1;

        if (strlen(phone) != 10) valid = 0;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (!isdigit(phone[i])) valid = 0;
        }

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
                valid = 0;
                printf("\033[1;31mPhone number already exists! Duplicates not allowed.\033[0m\n");
                break;
            }
        }

        if (!valid)
            printf("\033[1;31mInvalid phone number! Must be 10 digits and unique.\033[0m\n");

    } while (!valid);
}

void getValidEmail(char *email, AddressBook *addressBook) {
    int valid;
    do {
        printf("Enter email ID: ");
        fgets(email, 50, stdin);
        email[strcspn(email, "\n")] = '\0';
        valid = 1;

        if (!(strchr(email, '@') && strchr(email, '.'))) {
            valid = 0;
            printf("\033[1;31mInvalid email! Must contain '@' and '.'\033[0m\n");
        }

        for (int i = 0; email[i] != '\0'; i++) {
            if (isalpha(email[i]) && !islower(email[i])) {
                valid = 0;
                printf("\033[1;31mInvalid email! Use lowercase letters only.\033[0m\n");
                break;
            }
        }

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email, email) == 0) {
                valid = 0;
                printf("\033[1;31mEmail already exists! Duplicates not allowed.\033[0m\n");
                break;
            }
        }
    } while (!valid);
}

void getValidGender(char *gender) {
    int valid;
    do {
        printf("Enter gender: ");
        fgets(gender, 10, stdin);
        gender[strcspn(gender, "\n")] = '\0';
        valid = 1;

        for (int i = 0; gender[i] != '\0'; i++) {
            if (!isalpha(gender[i])) {
                valid = 0;
                printf("\033[1;31mInvalid gender! Only alphabets allowed.\033[0m\n");
                break;
            }
        }
    } while (!valid);
}

void getValidLocation(char *location) {
    int valid;
    do {
        printf("Enter location: ");
        fgets(location, 50, stdin);
        location[strcspn(location, "\n")] = '\0';
        valid = 1;

        for (int i = 0; location[i] != '\0'; i++) {
            if (!isalpha(location[i]) && location[i] != ' ') {
                valid = 0;
                printf("\033[1;31mInvalid location! Only alphabets and spaces allowed.\033[0m\n");
                break;
            }
        }
    } while (!valid);
}


    
// SEARCH CONTACT ---------------------------------------------------------------------------------------------------------------------------------------

void searchContact(AddressBook *addressBook, int *foundFlag) 
{
    /* Define the logic for search */
    char ch;
    *foundFlag = 0; // its default, Not found

    printf("=================================================\n");
    printf("        \033[1;33m*** SEARCH CONTACT BY ***\033[0m\n");
    printf("=================================================\n");
    printf("    1. Name\n");
    printf("    2. Phone number\n");
    printf("    3. Email ID\n");
    printf("    4. Location\n");
    printf("    5. Gender\n");
    printf("=================================================\n");
    printf("                    ***\n");
    printf("\n");
    printf("Enter your choice of search (1-5): ");
    scanf(" %c", &ch);
    // ch = getchar();
    int c;

    while ((c = getchar()) != '\n' && c != EOF);    

    switch(ch)
    {
        case '1':
        printf("\n\033[1;32m[SEARCHING] by name\033[0m\n");
        *foundFlag = searchbyname (addressBook);
        break;

        case '2':
        printf("\n\033[1;32m[SEARCHING] by phone number\033[0m\n");
        *foundFlag = searchbyphonenumber (addressBook);
        break;

        case '3':
        printf("\n\033[1;32m[SEARCHING] by Email ID\033[0m\n");
        *foundFlag = searchbyemail (addressBook);
        break;

        case '4':
        printf("\n\033[1;32m[SEARCHING] by Location\033[0m\n");
        *foundFlag = searchbylocation (addressBook);
        break;

        case '5':
        printf("\n\033[1;32m[SEARCHING] by Gender\033[0m\n");
        *foundFlag = searchbygender (addressBook);
        break;

        default:
        printf("\033[1;31mInvalid search choice\033[0m\n");
    }
    if ( *foundFlag == 0 )
    {
        printf("\033[1;31mNo Contact found! \033[0m\n");
    }
}

    // PRINT STATEMENT--------------------------------------------------------------------------------------------------------

void printHeader() 
{
    printf("=========================================================================================\n");
    printf("                                \033[1;33m*** CONTACT LOOKUP ***\033[0m\n");
    printf("=========================================================================================\n");
    printf("S No   %-15s %-12s %-8s %-25s %-15s\n", "Name", "Phone No", "Gender", "Email ID", "Location");
    printf("=========================================================================================\n");
}

    // SEARCH BY NAME-------------------------------------------------------------------------------------------------------------


int searchbyname (AddressBook *addressBook)
{
    char searchName[50];
    int found = 0;

    printf("Enter name: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    printf("\n");
    printHeader();

    for (int i = 0; i < addressBook->contactCount; i++) {   
        if (strcmp(addressBook->contacts[i].name, searchName) == 0) {
            printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].gender,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }

    if (!found)
        printf("No contacts found with name %s.\n", searchName);

    printf("=========================================================================================\n");
    return found;
}

    // SEARCH BY PHONE NUMBER--------------------------------------------------------------------------------------------------

int searchbyphonenumber(AddressBook *addressBook)
{
    char searchPhone[15];
    int found = 0;

    printf("Enter phone number: ");
    fgets(searchPhone, sizeof(searchPhone), stdin);
    searchPhone[strcspn(searchPhone, "\n")] = '\0';
    printf("\n");
    printHeader();

    
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, searchPhone) == 0) 
        {
            printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].gender,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("No contact found with phone '%s'.\n", searchPhone);
    } 
    printf("=========================================================================================\n");
    return found;
}

    // SEARCH BY EMAIL ID ---------------------------------------------------------------------------------------------------------

int searchbyemail (AddressBook *addressBook)
{
    char searchEmail[50];
    int found = 0;

    printf("Enter email ID: ");
    fgets(searchEmail, sizeof(searchEmail), stdin);
    searchEmail[strcspn(searchEmail, "\n")] = '\0';
    printf("\n");
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, searchEmail) == 0) 
        {
            
            printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].gender,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }
    if (found == 0) 
    {
        printf("No contact found with email '%s'.\n", searchEmail);
    }
    printf("=========================================================================================\n");
    return found;
}

    // SEARCH BY LOCATION------------------------------------------------------------------------------------------------

int searchbylocation(AddressBook *addressBook)
{
    char searchLocation[50];
    int found = 0;

    printf("Enter location: ");
    fgets(searchLocation, sizeof(searchLocation), stdin);
    searchLocation[strcspn(searchLocation, "\n")] = '\0'; printf("\n");
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].location, searchLocation) == 0) 
        {
            printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].gender,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }
    if (found == 0) 
    {
        printf("No contact found in location '%s'.\n", searchLocation);
    }
    printf("=========================================================================================\n");
    return found;
}

    // SEARCH BY GENDER--------------------------------------------------------------------------------------------------------------

int searchbygender(AddressBook *addressBook)
{
    char searchGender[50];
    int found = 0;

    printf("Enter Gender: ");
    fgets(searchGender, sizeof(searchGender), stdin);
    searchGender[strcspn(searchGender, "\n")] = '\0'; printf("\n");
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].gender, searchGender) == 0) 
        {
            printf("%-6d %-15s %-12s %-8s %-25s %-15s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].gender,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }
    if (found == 0) 
    {
        printf("Invalid data: '%s'.\n", searchGender);
    }
    printf("=========================================================================================\n");
    return found;
}



// EDIT CONTACT ----------------------------------------------------------------------------------------------------------------------------------

void editContact(AddressBook *addressBook)
{
	// Define the logic for Editcontact 
    int index = -1, choice, valid;

    // Step 1: Call searchContact() to display results
    int foundFlag = 0;
    searchContact(addressBook, &foundFlag); // Modify the search to return no of matches

    // Proceed only if the result of searchcontact() is existed
    if (!foundFlag)
    {
        printf("\033[1;31mReturning to main menu.\033[0m\n");
        sleep(1);
        return;
    }

    // Step 2: Ask user for S. No of contact to edit
    printf("\nEnter the S. No of the contact to edit: ");
    scanf("%d", &index);
    while (getchar() != '\n'); // clear buffer

    // Validate index
    if (index < 1 || index > addressBook->contactCount) {
        printf("\033[1;31mInvalid S. No! Contact not found.\033[0m\n");
        return;
    }
    index--; // convert to 0-based index

    // Step 3: Display edit menu
    printf("\n");
    printf("=================================================\n");
    printf("        \033[1;33m*** SELECT FIELD TO EDIT ***\033[0m\n");
    printf("=================================================\n");
    printf("    1. Edit name\n");
    printf("    2. Edit phone number\n");
    printf("    3. Edit gender\n");
    printf("    4. Edit email ID\n");
    printf("    5. Edit location\n");
    printf("=================================================\n");
    printf("                    ***\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // clear buffer

    switch (choice) 
    {
        case 1:
            getValidName(addressBook->contacts[index].name);
            break;

        case 2:
            getValidPhone(addressBook->contacts[index].phone, addressBook);
            break;

        case 3:
            getValidGender(addressBook->contacts[index].gender);
            break;

        case 4:
            getValidEmail(addressBook->contacts[index].email, addressBook);
            break;

        case 5:
            getValidLocation(addressBook->contacts[index].location);
            break;

        default:
            printf("\033[1;31mInvalid choice!\033[0m\n");
    }

    printf("\n\033[1;32m*** Contact updated successfully! ***\033[0m\n"); 
}

// DELETE CONTACT ---------------------------------------------------------------------------------------------------------------------  
void deleteContact(AddressBook *addressBook) 
{
    int foundFlag = 0;
    int index = -1;

    // Step 1: Search contact first
    searchContact(addressBook, &foundFlag);

    if (!foundFlag) {
        printf("\033[1;31mNo contact found. Deletion cancelled.\033[0m\n");
        return;
    }

    // Step 2: Ask user for S.No of contact to delete
    printf("\nEnter the S. No of the contact to delete: ");
    scanf("%d", &index);
    while (getchar() != '\n'); // clear buffer

    // Validate index
    if (index < 1 || index > addressBook->contactCount) {
        printf("\033[1;31mInvalid S. No! Contact not found.\033[0m\n");
        return;
    }

    // Convert to 0-based index
    index--;

    // Step 3: Delete by shifting array elements
    if (index == addressBook->contactCount - 1) {
        // Last contact — just decrement count
        addressBook->contactCount--;
    } else {
        for (int i = index; i < addressBook->contactCount - 1; i++) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
    }

    printf("\n\033[1;32m*** Contact deleted successfully! ***\033[0m\n");
}