# 📒 Address Book in C

A simple **Address Book application** is a C based application designed to manage contact information efficiently.
The application allows users to add, list, search, edit, and delete contacts.  
This project demonstrates structured programming, file handling, and input validation in C.

---

##  Features
- Add new contacts (Name, Phone, Email, Gender, Location)
- List all saved contacts in a formatted table
- Search contacts by name, phone, email, or location
- Edit existing contact details
- Delete contacts (with duplicate handling)
- Save and load contacts from file for persistence
- Input validation for phone numbers, email IDs, and gender

---

##  Project Structure
AddressBook/
│── src/
│   ├── contact.c        # Core contact functions (list, search, edit, delete)
│   ├── file.c           # File save/load logic 
│   ├── populate.c       # Populate sample contacts
│── include/
│   ├── contact.h        # Contact structure & prototypes
│   ├── file.h           # File handling prototypes
│── docs/
│   ├── handwritten_notes/   # Algorithm design notes (validation, edit, delete)
│   ├── screenshots/         # Program output & terminal logs
│── README.md
│── Makefile (optional for easy compilation)

---

##  Sample Output
====================================================
No   Name        Phone        Email       Location
----------------------------------------------------
1    Alice       9876543210   alice@mail  Chennai
2    Bob         9123456789   bob@mail    Trichy
====================================================
