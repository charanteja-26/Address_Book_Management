#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contact.csv","w");
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contact.csv","w+");
    if(fptr == NULL)
    {
        printf("Error : No file is found to load the contacts from.\n");
        exit(1);
    }
    fscanf(fptr,"%d\n",&addressBook->contactCount);
     
    for(int i=0;i < addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    // char contacts_list[100];
    // int i = 0;
    // for( i ;i < addressBook->contactCount;i++)
    // {
    //     fscanf(fptr,"%s",contacts_list);
    //     char *ptr;
    //     ptr = strtok(contacts_list,",");
    //     strcpy(addressBook->contacts[i].name,ptr);
    //     ptr = strtok(NULL,",");
    //     strcpy(addressBook->contacts[i].phone,ptr);
    //     ptr = strtok(NULL,"\n");
    //     strcpy(addressBook->contacts[i].email,ptr);
    // }
    // addressBook->contactCount = i;
    fclose(fptr);
}
