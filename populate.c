#include "contact.h"

// S E R V E R
// Dummy contact data , ARRAY OF STRUCTURES
static Contact dummyContacts[] = {
    {"John Doe", "1234567890","Male","john@example.com" , "Bangalore"},
    {"Alice Smith", "0987654321", "Female" ,"alice@example.com" , "Chennai"},
    {"Bob Johnson", "1112223333", "Male","bob@company.com" , "Tanjore"},
    {"Carol White", "4445556666", "Female", "carol@company.com" , "UK"},
    {"David Brown", "7778889999", "Male","david@example.com" , "Italy"},
    {"Eve Davis", "6665554444", "Female", "eve@example.com" , "Mumbai"},
    {"Frank Miller", "3334445555","Male", "frank@example.com", "Bangalore"},
    {"Grace Wilson", "2223334444","Female", "grace@example.com" , "Erode"},
    {"Hannah Clark", "5556667777","Male", "hannah@example.com" , "Velur"},
    {"Ian Lewis", "8889990000", "Male","ian@example.com", "Attur"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]); // Calculates the size of dummy contact

    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i)  // MAX_CONTACT = 100, checks contactcount < 100
    {
        addressBook->contacts[i] = dummyContacts[i]; // Copying dummycontact into our contacts array
        addressBook->contactCount++; // Increments the contact count for each copying
    }
}