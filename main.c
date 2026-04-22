#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
Guest *head;
int gc = 0;
int main()
{
    load_guests_from_file(&head, &gc);
    int choice;

    while (1)
    {
        printf("\n=========Welcome to Hotel services =========\n\n");
        printf(" 1. View Admin menu : PRESS 1\n");
        printf(" 2. View Guest menu : PRESS 2\n");
        printf(" 3. Exit : PRESS 3\n\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\n--INVALID CHOICE--\n");
            return 0;
        }

        switch (choice)
        {
        case 1:
            admin_menu(&head, &gc);
            break;
        case 2:
            guest_menu(&head, &gc);
            break;
        case 3:
            save_guests_to_file(&head);
            printf("\nExiting...\n");
            exit(0);
            break;
        default:
            printf("\n--Invalid choice--\n");
        }
    }

    return 0;
}