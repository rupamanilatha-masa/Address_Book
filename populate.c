#include<stdio.h>
#include "contact.h"
static Contact dummyContacts[] = {
    {"Prafulla", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
};//Dummy contacts used for initial testing
//Function to load previously saved contacts from the CSV file
void load(AddressBook *addressBook)
{
    addressBook->contactCount=0; //Initially set the contact count to zero
    int numDummyContacts=sizeof(dummyContacts)/sizeof(dummyContacts[0]); //Calculate the number of dummy contacts
    //Copy dummy contacts into the address book
    for(int i=0;i<numDummyContacts && addressBook->contactCount<100;i++)
    {
        addressBook->contacts[addressBook->contactCount++]=dummyContacts[i];
    }
    FILE *fp1;
    fp1=fopen("contact.csv","r");
    if(fp1==NULL)
    {
        printf("File opening failed\n");
        return;
    }
    //Read the total number of saved contacts from the first line
    fscanf(fp1,"%d\n",&addressBook->contactCount);
    //Read the saved contact details from the file
    for (int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp1,"%39[^,],%39[^,],%39s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp1);
}