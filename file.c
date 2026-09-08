#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.txt", "w");
    if (fptr == NULL) {
        printf("\033[1;31mError opening file for writing!\033[0m\n");
        return;
    }

    // Step 1: Write contact count
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Step 2: Write each contact as comma-separated values
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].gender,
                addressBook->contacts[i].email,
                addressBook->contacts[i].location);
    }

    fclose(fptr);
    printf("\033[1;32mContacts saved successfully to file!\033[0m\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL) 
    {
        printf("\033[1;33mNo saved contacts found. Starting fresh.\033[0m\n");
        return;
    }

    // Step 1: Read contact count
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    // Step 2: Read each contact line
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].gender,
               addressBook->contacts[i].email,
               addressBook->contacts[i].location);
    }

    fclose(fptr);
    printf("\033[1;32mContacts loaded successfully from file!\033[0m\n");
}
