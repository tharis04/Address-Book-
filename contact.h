#ifndef CONTACT_H
#define CONTACT_H


#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char gender[10];
    char email[50];
    char location[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS]; // Array of structures, storing MAX_CONTACTS = 100
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook,int *foundFlag);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

// SEARCH CONTACT
int searchbyname (AddressBook *addressBook);
int searchbyphonenumber(AddressBook *addressBook);
int searchbyemail (AddressBook *addressBook);
int searchbylocation(AddressBook *addressBook);
int searchbygender(AddressBook *addressBook);

// Validation function prototypes
void getValidName(char *name);
void getValidPhone(char *phone, AddressBook *addressBook);
void getValidEmail(char *email, AddressBook *addressBook);
void getValidGender(char *gender);
void getValidLocation(char *location);


#endif
