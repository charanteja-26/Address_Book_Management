#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include <ctype.h>

void initialize(AddressBook *addressBook) 
{
	// Load contacts from file during initialization (After files)
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}
 
int name_validate(char name[])
{
	//STEP1: Fetch one by one character till null character
	int i = 0;
	while(name[i] != '\0')
	{
		if(!(isalpha(name[i]) || name[i]==' '))
		{
				return 1;
				//STEP2: Check the character is alpahebet or not
				//Yes-> Move to next character, NO -> Stop the process
		}
		i++;
	} 
	return 0;
}

int num_validate(char num[],AddressBook *addressBook)
{
	for(int j=0;j<addressBook->contactCount;j++)
	{
		if(strcmp(num,addressBook->contacts[j].phone)==0)
		{
			return 1;
		}
	}
	for(int j=0;num[j]!='\0';j++)
	{
		if(!(isdigit(num[j])))
			return 2;
	}
	if(strlen(num)!=10)
	 	return 3;
	
	return 0;

}

int email_validate(char *email,AddressBook *addressBook)
{
	char email_cmp[100];
	//printf("email id -> %s\n",email);
	if((strstr(email,"@gmail.com")!=NULL) || (strstr(email,"@outlook.com")!=NULL)|| (strstr(email,"@yaahoo.com")!=NULL) || (strstr(email,"@google.com")!=NULL))
	{
		 
		for(int i=0;i<addressBook->contactCount;i++)
		{
			if(strcmp(email,addressBook->contacts[i].email)==0)
			{
					return 0;
			}
		}
		// validate characters
		return 1;
	}
	//printf("hello\n");
	return 0;
}
void createContact(AddressBook *addressBook)
{
    char name[20];

    //STEP1: Read a name from user
	printf("Enter the name: ");
	//__fpurge(STDIN);
	//getchar();
	scanf(" %[^\n]", name);
	//printf("%s",name);


    //STEP2: Validate the name -> Alphabets
	while(name_validate(name)== 1)
	{
		printf("INFO: Name is invalid, Please enter valid name...\n");
		printf("Enter the name: ");
		scanf(" %[^\n]", name);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	//printf("...........%s",name);
	//STEP3: Read a mobile number from user
	char num[11];
	int validation_result= 0;
	printf("Enter number : ");
	scanf(" %[^\n]",num);
	 
	//STEP4: Validate the mobile number -> Digit & 10 Digits & unique
	validation_result = num_validate(num,addressBook);
	while(validation_result != 0)
	{
		if(validation_result == 1)
			printf("INFO: Number is already found, Please enter a new number...\n");
		else if(validation_result == 3)
			printf("INFO: Number should be 10 digits, Please enter valid number...\n");
		else if(validation_result == 2)
			printf("INFO: Number must be integer value, Please enter valid number...\n");
		printf("Enter the number: ");
		scanf(" %[^\n]", num);
		validation_result = num_validate(num,addressBook);
	//True -> Goto STEP5, False -> print error, Goto STEP3
	}

	//STEP5: Read a email_id from user
	char email[50];
	printf("Enter email : ");
	scanf(" %[^\n]",email);
	//STEP6: Validate the email_ID -> @gmail.com & unique
	while(email_validate (email,addressBook)==0)
	{
		printf("INFO: Email is invalid, Please enter valid email...\n");
		printf("Enter the email: ");
		scanf(" %[^\n]", email);
	}
	//True -> Goto STEP7, False -> print error, Goto STEP5

	//STEP7: store into structure[contact_count]
	
	int index = addressBook->contactCount;
	addressBook->contactCount++;
	 
    //  char dup_name[20];
	//  strcpy(dup_name,name);
   	//  printf("name           -> %s\n",name);
	strcpy(addressBook->contacts[index].name,name);
	strcpy(addressBook->contacts[index].phone,num);
	strcpy(addressBook->contacts[index].email,email);

	/* Define the logic to create a Contacts */
}

void searchContact(AddressBook *addressBook) 
{
	/* Define the logic for search */
	//STEP1: Print the menu Based on what searching
	label1:
	printf("Enter the choice search by : \n");
	printf("1.Name\n");
	printf("2.Mobile_no\n");
	printf("3.Email_id\n");
	//STEP2: Choose the menu
	int choice;

	 
	printf("Enter choice : ");
	scanf("%d",&choice);
		switch(choice)
		{
			//1 -> Name
		//Read the name
		//Search the extered name is present in the database or not
		//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
			case 1:
			char name[50];
			int flag = 0,i;
			printf("Enter name:");
			scanf(" %[^\n]",name);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].name,name)==0)
				 {
					 flag = 1;
					break;
				 }
			}
			if(flag == 1)
			{
				printf("%s\t %s\t %s\t",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			}
			else
			{
				printf("No contacts matched with name\n");
			}
			break;

			case 2:
			//2 -> Mobile_no
			//Read the mobile_no
			//Search the extered mobile_no is present in the database or not
			//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
			char phone[50];
			flag = 0;
			printf("Enter phone:");
			scanf(" %[^\n]",phone);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,phone)==0)
				 {
					 flag = 1;
					break;
				 }
			}
			if(flag == 1)
			{
				printf("%s\t %s\t %s\t",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			}
			else
			{
				printf("No contacts matched with name\n");
			}
			break;

			//3 -> Email_id
			//Read the mail_id
			//Search the extered mail_id is present in the database or not
			//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
			case 3:
			char email[50];
			flag = 0;
			printf("Enter email:");
			scanf(" %[^\n]",email);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].email,email)==0)
				 {
					flag = 1;
					break;
				 }
			}
			if(flag == 1)
			{
				printf("%s\t %s\t %s\t",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			}
			else
			{
				printf("No contacts matched with name\n");
			}
			break;

			default:
			printf("Invalid Choice.Please Try Again :\n");
			goto label1;

		}
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	label1:
	printf("Enter the choice to edit : \n");
	printf("1.Name\n");
	printf("2.Mobile_no\n");
	printf("3.Email_id\n");
	printf("4.All\n");
	//STEP2: Choose the menu
	int choice;
	int i,j;
	printf("Enter choice : ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		char name[50];
		char name1[50];
		printf("Enter name:");
		scanf(" %[^\n]",name);
		for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].name,name)==0)
				 {
					printf("Enter new name : ");
					scanf(" %[^\n]",name1);
						  strcpy(addressBook->contacts[i].name,name1);
				 }
			}
			break;
		
		case 2:
		char phone[50];
		char phone1[50];
		printf("Enter number:");
		scanf(" %[^\n]",phone);
		for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,phone)==0)
				 {
					printf("Enter new number : ");
					scanf(" %[^\n]",phone1);
						  strcpy(addressBook->contacts[i].phone,phone1);
				 }
			}
			break;

		case 3:
		char email[50];
		char email1[50];
			printf("Enter email:");
			scanf(" %[^\n]",email);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].email,email)==0)
				 {
					printf("Enter new email : ");
					scanf(" %[^\n]",email1);
						  strcpy(addressBook->contacts[i].email,email1);
				 }
			}
			break;	
		
		case 4:
			printf("Enter the choice to edit by : \n");
			printf("1.Name\n");
			printf("2.Mobile_no\n");
			printf("3.Email_id\n");
			//printf("4.All\n");
			//STEP2: Choose the menu
			// int choice;
			// int i,j;
			printf("Enter choice : ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
				char name2[50];
				char name3[50];
				char phone2[50];
				char email2[50];
				printf("Enter name:");
				scanf(" %[^\n]",name2);
				for(i=0;i<addressBook->contactCount;i++)
					{
						if(strcmp(addressBook->contacts[i].name,name2)==0)
						{
							printf("Enter new name : ");
							scanf(" %[^\n]",name3);
							printf("Enter new number : ");
							scanf(" %[^\n]",phone2);
							printf("Enter new email : ");
							scanf(" %[^\n]",email2);
								strcpy(addressBook->contacts[i].name,name3);
								strcpy(addressBook->contacts[i].phone,phone2);
								strcpy(addressBook->contacts[i].email,email2);
						}
					}
					break;
				
				case 2:
				char phone3[50];
				char phone4[50];
				char name4[50];
				char email3[50];
				printf("Enter number:");
				scanf(" %[^\n]",phone3);
				for(i=0;i<addressBook->contactCount;i++)
					{
						if(strcmp(addressBook->contacts[i].phone,phone3)==0)
						{
							printf("Enter new name : ");
							scanf(" %[^\n]",name4);
							printf("Enter new number : ");
							scanf(" %[^\n]",phone4);
							printf("Enter new email : ");
							scanf(" %[^\n]",email3);
								strcpy(addressBook->contacts[i].name,name4);
								strcpy(addressBook->contacts[i].phone,phone4);
								strcpy(addressBook->contacts[i].email,email3);
						}
					}
					break;

				case 3:
				char email4[50];
				char email5[50];
				char phone5[50];
				char name5[50];
					printf("Enter email:");
					scanf(" %[^\n]",email4);
					for(i=0;i<addressBook->contactCount;i++)
					{
						if(strcmp(addressBook->contacts[i].email,email4)==0)
						{
							printf("Enter new name : ");
							scanf(" %[^\n]",name5);
							printf("Enter new number : ");
							scanf(" %[^\n]",phone5);
							printf("Enter new email : ");
							scanf(" %[^\n]",email5);
								strcpy(addressBook->contacts[i].name,name5);
								strcpy(addressBook->contacts[i].phone,phone5);
								strcpy(addressBook->contacts[i].email,email5);
						}
					}
					break;
					 	
	 		}
			break;

	default:
		printf("Invalid Choice.Please Try Again :\n");
		goto label1; 
	}

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	label1:
	printf("Enter the choice to delete by : \n");
	printf("1.Name\n");
	printf("2.Mobile_no\n");
	printf("3.Email_id\n");
	//STEP2: Choose the menu
	int choice;
	int i,j;
	printf("Enter choice : ");
	scanf("%d",&choice);
	switch(choice)
		{
			 
			case 1:
			char name[50];
			int i,j;
			printf("Enter name:");
			scanf(" %[^\n]",name);
			//AddressBook->contatactCount = AddressBook->contatactCount--
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].name,name)==0)
				 {
					  for(j=i;j<addressBook->contactCount-1;j++)
					  {
						addressBook->contacts[j] = addressBook->contacts[j+1];
					  }
				 }
			}
			break;

			case 2: 
			char phone[50];
			printf("Enter phone:");
			scanf(" %[^\n]",phone);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,phone)==0)
				 {
					  for(j=i;j<addressBook->contactCount-1;j++)
					  {
						addressBook->contacts[i] = addressBook->contacts[i+1];
					  }
				 }
			}
			break;

			case 3:
			char email[50];
			//flag = 0;
			printf("Enter email:");
			scanf(" %[^\n]",email);
			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].email,email)==0)
				{
					  for(j=i;j<addressBook->contactCount-1;j++)
					  {
						addressBook->contacts[i] = addressBook->contacts[i+1];
					  }
				 }
			}
			break;

			default:
			printf("Invalid Choice.Please Try Again :\n");
			goto label1;
		}
	addressBook->contactCount--;

}

void listContacts(AddressBook *addressBook) 
{
	// Sort contacts based on the chosen criteria
	printf("count -> %d\n",addressBook->contactCount);
	for(int i = 0; i < addressBook->contactCount;i++)
	{
		printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
}
