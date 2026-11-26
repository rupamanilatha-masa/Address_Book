#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"
int edit_ind[100];
//create the contact
void createContact(AddressBook *addressBook)
{
    //Get the index where the new contact should be stored
    int i=addressBook->contactCount;
    if(i>=100)
    {
        printf("Contact list is full\n");
            return;
    }
    printf("\nContact %d\n",i+1);
    validname(addressBook,i);
    validphonenum(addressBook,i);
    validemail(addressBook,i);
    //Increase the total number of contacts
    addressBook->contactCount++;
}
//validating the name
void validname(AddressBook *addressBook,int ind)
{
    char name[40];
    int flag,i;
    printf("Enter the Name : ");
    /*If the name is not valid ,enter the name again.For this condidtion i use do-while loop
    if the name is not valid then the flag returns 1 i.e, the user has to enter the valid name till the flag =0(valid)*/
    do
    {
        if(scanf(" %39[^\n]",name)!=1) return;
        int len=strlen(name);
        flag=0;
        for(i=0;i<len;i++)
        {
            //Allow only alphabets and spaces
            if(!isalpha(name[i]) && name[i]!=' ')
            {
                flag=1;
                break;
            }
            flag=0;
        }
        if(flag==1)
            printf("Enter valid name : ");
    }while(flag==1);
    strcpy(addressBook->contacts[ind].name,name);//copy the valid entered name in to array of structures(addressbook)
    printf("valid name: %s\n",addressBook->contacts[ind].name);
}
//validating phone number
void validphonenum(AddressBook *addressBook,int ind)
{
    char num[35];
    int i,flag=0;
    printf("Enter the phone number: ");
    do
    {
        flag=0;
        if(scanf("%34s",num)!=1) return;
        int len=strlen(num);
        for(i=0;i<len;i++)
        {
            if(len!=10 || num[0]<'6' || !isdigit(num[i]))/*if the len not equal to 10 , if the num isnot digit &
            if the starting num is less than 6 returns flag=1 i.e, enter  the num again*/
            {
                flag=1;
                break;
            }
        }
        for(i=0;i<addressBook->contactCount;i++)
        {
            //Skip the current contact while editing
            if(i!=ind && strcmp(addressBook->contacts[i].phone,num)==0)//compare the entered num with previous contacts if it is pressent enter the name again
            {
                printf("Num already exists\n");
                flag=1;
                break;
            }
        }
        if(flag==1)
            printf("Enter valid number : ");
    }while(flag==1);
    strcpy(addressBook->contacts[ind].phone,num);//copy the valid entered num int o the array of structures
    printf("valid number: %s\n",addressBook->contacts[ind].phone);
}
//validating emailid
void validemail(AddressBook *addressBook,int ind)
{
    char emailid[40];
    int i,flag=0,j=0;
    printf("Enter the Emailid: ");
    do
    {
        flag=0,j=0;
        if(scanf("%39s",emailid)!=1) return;
        int len=strlen(emailid);
        for(i=0;i<len;i++)
        {
            emailid[i]=tolower(emailid[i]);//Convert uppercase letters into lowercase
        }
        for(i=0;i<len;i++)
        {
            if(emailid[i]=='@')// 
            {
                j++;//Count the number of '@''s
                for(int k=i+1;k<len-4;k++)
                {
                    //Allow only alphabets between @ and .com
                    if(!isalpha(emailid[k]))
                    {
                        flag=1;
                    }
                }
            }
        }
        for(i=0;emailid[i]!='@' && emailid[i]!='\0';i++)
        {
            if(!isalnum(emailid[i]))
            {
                flag=1;
            }
        }
        //Email must contain exactly one @ and should not start with @ or a digit
        if(j!=1||emailid[0]=='@'||isdigit(emailid[0])||len<6)
            flag=1;
        //Check whether the email ends with .com
        if(len<4||strcmp(emailid+len-4,".com")!=0)
        {
            flag=1;
        }
        //Make sure that @ is not too close to the end of the email
        for(i=0;i<len;i++)
        {
            if(emailid[i]=='@'&&i>=len-5)
            {
                flag=1;
            }
        }
        //Check whether the email already exists
        for(i=0;i<addressBook->contactCount;i++)
        {
            //Skip the current contact while editing
            if(i!=ind && strcmp(addressBook->contacts[i].email,emailid)==0)
            {
                printf("Email already exists\n");
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            printf("Enter valid email : ");
        }
    }while(flag==1);
    strcpy(addressBook->contacts[ind].email,emailid);//Store the valid email in the contact structure
    printf("valid email: %s\n",addressBook->contacts[ind].email);
}
//list of all contacts
void listContacts(AddressBook *addressBook)
{
    int i;
    printf("\n-------------------------Contact List---------------------------\n");
    printf("----------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %s\n","SNO","Name","Phone_num","Email");
    printf("----------------------------------------------------------------\n");
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("%-5d %-20s %-15s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("----------------------------------------------------------------\n");
}
//searching the contact
int searchcontact(AddressBook *addressBook)
{
    int choice,i,found=0;
    char search[30];
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("Enter the choice : ");
    if(scanf("%d",&choice)!=1) return -1;
    switch(choice)
    {
        case 1:
        {
            printf("Enter the name which to be searched : ");
            scanf(" %29[^\n]",search);
            printf("----------------------------------------------------------------\n");
            printf("%-5s %-20s %-15s %s\n","SNO","Name","Phone_num","Email");
            printf("----------------------------------------------------------------\n");
            //Compare the entered name with all saved contact names
            for(i=0;i<addressBook->contactCount;i++)
            { 
                if(strcmp(addressBook->contacts[i].name,search)==0)
                {
                    edit_ind[found]=i;//Store the index of the matching contact
                    found++;//Increase the number of matching contacts
                    printf("%-5d %-20s %-15s %s\n",found,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        case 2:
        {
            printf("Enter the phone number which to be searched : ");
            scanf("%29s",search);
            printf("----------------------------------------------------------------\n");
            printf("%-5s %-20s %-15s %s\n","SNO","Name","Phone_num","Email");
            printf("----------------------------------------------------------------\n");
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,search)==0)
                {
                    edit_ind[found]=i;
                    found++;
                    //Display the matching contact with a serial number
                    printf("%-5d %-20s %-15s %s\n",found,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        case 3:
        {
            printf("Enter the emailid which to be searched : ");
            scanf("%29s",search);
            printf("----------------------------------------------------------------\n");
            printf("%-5s %-20s %-15s %s\n","SNO","Name","Phone_num","Email");
            printf("----------------------------------------------------------------\n");
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].email,search)==0)
                {
                    edit_ind[found]=i;
                    found++;
                    printf("%-5d %-20s %-15s %s\n",found,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        }
        default:
        {
            printf("Enter valid choice\n");
            return -1;
        }
    }
    printf("----------------------------------------------------------------\n");
    if(found==0)
    {
        printf("Contact not found\n");
        return 0;
    }
    return found; //Return the total number of matching contacts
}
//editing the contact
void editContact(AddressBook *addressBook)
{
    int serial_num,ind,choice;
    //Search the contact that needs to be edited
    int count=searchcontact(addressBook);
    if(count<=0)//Stop if no matching contact is found
    {
        return;
    }
    printf("Enter serial number : ");
    scanf("%d",&serial_num); //Select the required contact from the search results
    if(serial_num<1 || serial_num>count)//Check whether the entered serial number is valid
    {
        printf("Invalid serial number\n");
        return;
    }
    ind=edit_ind[serial_num-1];//Get the index of the selected contact
    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email\n");
    printf("Enter choice : ");
    if(scanf("%d",&choice)!=1) return;
    switch(choice)
    {
        case 1:
        {
            validname(addressBook,ind);
            break;
        }
        case 2:
        {
            validphonenum(addressBook,ind);
            break;
        }
        case 3:
        {
            validemail(addressBook,ind);
            break;
        }
        default:
        {
            printf("Invalid choice\n");
            return;
        }
    }
    // Display the updated contact details
    printf("\nEdited Contact %d\n",ind+1);
    printf("Name : %s\n",addressBook->contacts[ind].name);
    printf("Phone Number : %s\n",addressBook->contacts[ind].phone);
    printf("Email : %s\n",addressBook->contacts[ind].email);
}
//Delete the existing contact
void deleteContact(AddressBook *addressBook)
{
    int serial_num,ind,i;
    int count=searchcontact(addressBook); //Search the contact that needs to be deleted
    if(count<=0)
        return;
    printf("Enter serial number : ");
    scanf("%d",&serial_num);//Select the contact from the search results
    if(serial_num<1 || serial_num>count)
    {
        printf("Invalid serial number\n");
        return;
    }
    ind=edit_ind[serial_num-1];//Get the actual index of the contact to be deleted
    /*Shift the remaining contacts one position to the left
    This removes the selected contact from the array*/
    for(i=ind;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--; //Decrease the total contact count
    printf("Required contact deleted\n");
    listContacts(addressBook);//Display the updated contact list
}
//Function to save all contacts into a CSV file
void saveandexit(AddressBook *addressBook)
{
    FILE *fp;
    fp=fopen("contact.csv","w");
    if(fp==NULL)
    {
        printf("File opening failed\n");
        return;
    }
    //Store the total number of contacts in the first line
    fprintf(fp,"%d\n",addressBook->contactCount);
    for (int i=0;i<addressBook->contactCount;i++)
    {
        // Write each contact's name, phone number and email into the file, Values are separated by commas
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}