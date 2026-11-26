#ifndef CONTACT_H
#define CONTACT_H
#define MAX_CONTACTS 100 //Maximum number of contacts that can be stored
//Structure to store the details of a single contact
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
//Structure to store all contacts and their count
typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
//Function declarations for contact operations
void createContact(AddressBook *addressBook);
int searchcontact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveandexit(AddressBook *addressBook);
void load(AddressBook *addressBook);
void validname(AddressBook *addressBook,int ind);
void validphonenum(AddressBook *addressBook,int ind);
void validemail(AddressBook *addressBook,int ind);
#endif