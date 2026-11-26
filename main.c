//Name : M.Rupa mani latha
//Batch : 26022_290
#include<stdio.h>
#include "contact.h"
int main()
{
    int choice;
    AddressBook addressBook;
    // initialize(&addressBook);
    //Load the previously saved contacts from the file
    load(&addressBook);
    do
    {
        printf("\n1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter choice : ");
        // Repeat the menu until the user selects Save and Exit
        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid input\n");
            return 1;
        }
        switch(choice)
        {
            case 1:
            {
                createContact(&addressBook);
                break;
            }
            case 2:
            {
                searchcontact(&addressBook);
                break;
            }
            case 3:
            {
                editContact(&addressBook);
                break;
            }
            case 4:
            {
                deleteContact(&addressBook);
                break;
            }
            case 5:
            {
                listContacts(&addressBook);
                break;
            }
            case 6:
            {
                saveandexit(&addressBook);
                break;
            }
            default:
            {
                printf("Invalid choice\n");
            }
        }
    }while(choice!=6);//Continue displaying the menu until choice is 6
    return 0;
}