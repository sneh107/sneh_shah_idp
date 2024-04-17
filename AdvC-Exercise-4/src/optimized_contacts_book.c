#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    char phone[15];
} Contact_t;

Contact_t *contacts = NULL;
int num_contacts = 0;

void AddContact()
{
    Contact_t new_contact;
    printf("Enter name: ");
    scanf("%s", new_contact.name);

    printf("Enter phone number: ");
    scanf("%s", new_contact.phone);

    contacts = realloc(contacts, (num_contacts + 1) * sizeof(Contact_t));
    if (contacts == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    contacts[num_contacts] = new_contact;
    num_contacts++;
    printf("Contact added successfully.\n");
}

void DeleteContact()
{
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < num_contacts; i++)
    {
        if (strcasecmp(contacts[i].name, name) == 0)
        {
            for (int j = i; j < num_contacts - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            found = 1;
            break;
        }
    }

    if (found)
    {
        num_contacts--;
        contacts = realloc(contacts, num_contacts * sizeof(Contact_t));
        if (num_contacts > 0 && contacts == NULL)
        {
            printf("Error: Memory reallocation failed.\n");
        }
        else
        {
            printf("Contact deleted successfully.\n");
        }
    }
    else
    {
        printf("Error: Contact not found.\n");
    }
}

void DisplayContacts()
{
    if (num_contacts == 0)
    {
        printf("No contacts found.\n");
    }
    else
    {
        printf("Contacts:\n");
        for (int i = 0; i < num_contacts; i++)
        {
            printf("%s: %s\n", contacts[i].name, contacts[i].phone);
        }
    }
}

int main()
{
    int choice;
    do
    {
        printf("\nContacts Book Menu:\n");
        printf("1. Add contact\n");
        printf("2. Delete contact\n");
        printf("3. Display contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            AddContact();
            break;
        case 2:
            DeleteContact();
            break;
        case 3:
            DisplayContacts();
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Error: Invalid choice.\n");
        }
    } while (choice != 4);

    free(contacts);

    return 0;
}
