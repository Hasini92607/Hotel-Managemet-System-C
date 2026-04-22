#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
Room rooms[6] = {
    {101, "Single Room", 3000.0},
    {102, "Double Room", 5000.0},
    {103, "Suite", 8000.0},
    {104, "Deluxe Suite", 10000.0},
    {105, "Family Room", 12000.0},
    {106, "Presidential Suite", 18000.0}};

int checkifclash(Date d1, Date d2, Date d3, Date d4)
{
    if (d4.year < d1.year)
    {
        return 0;
    }
    if (d4.year == d1.year && d4.month < d1.month)
    {
        return 0;
    }
    if (d4.year == d1.year && d4.month == d1.month && d4.day < d1.day)
    {
        return 0;
    }
    if (d2.year < d3.year)
    {
        return 0;
    }
    if (d2.year == d3.year && d2.month < d3.month)
    {
        return 0;
    }
    if (d2.year == d3.year && d2.month == d3.month && d2.day < d3.day)
    {
        return 0;
    }
    return 1;
}
int checkifvalidDate(Date date)
{
    if (date.year <= 0)
    {
        return 1;
    }
    if (date.month > 12 || date.month <= 0)
    {
        return 1;
    }
    if (date.day > 31 || date.day <= 0)
    {
        return 1;
    }
    if (date.day == 31 && (date.month == 2 || date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11))
    {
        return 1;
    }
    if (date.month == 2)
    {
        if (date.year % 4 && date.day > 28)
            return 1;
        if (!(date.year % 4) && date.day > 29)
            return 1;
    }
    return 0;
}

void save_guests_to_file(Guest **head)
{
    FILE *file = fopen("guests.txt", "w");
    if (file == NULL)
    {
        printf("\n--Error opening file--\n");
        return;
    }

    fprintf(file, "%-4s %-27s %-9s %-13s %-15s %-14s %-15s\n\n",
            "ID", "Name", "RoomNo.", "No.ofPeople", "PaymentStatus", "Check-inDate", "Check-outDate");

    for (Guest *temp = *head; temp != NULL; temp = temp->next)
    {
        fprintf(file, "%-4d %-27s %-9d %-13d %-15d %02d.%02d.%-8d %02d.%02d.%-9d\n",
                temp->ID,
                temp->name,
                temp->room_no,
                temp->people,
                temp->bill_status,
                temp->check_in.day,
                temp->check_in.month,
                temp->check_in.year,
                temp->check_out.day,
                temp->check_out.month,
                temp->check_out.year);
    }
    Guest *temp = *head;
    while (*head)
    {
        temp = temp->next;
        free(*head);
        *head = temp;
    }
    fclose(file);
}

void load_guests_from_file(Guest **head, int *gc)
{
    FILE *fl = fopen("guests.txt", "r");
    if (fl == NULL)
    {
        return;
    }
    char line[256];
    fgets(line, sizeof(line), fl);
    fgets(line, sizeof(line), fl);
    Guest *temp = *head;
    while (fgets(line, sizeof(line), fl))
    {
        Guest *new = malloc(sizeof(Guest));

        char dot;
        if (sscanf(line, "%d %s %d %d %d %d %c %d %c %d %d %c %d %c %d",
                   &new->ID,
                   new->name,
                   &new->room_no,
                   &new->people,
                   &new->bill_status,
                   &new->check_in.day, &dot, &new->check_in.month, &dot, &new->check_in.year,
                   &new->check_out.day, &dot, &new->check_out.month, &dot, &new->check_out.year) == 15)
        {
            new->next = NULL;
            if (*head == NULL)
            {
                *head = new;
                temp = new;
            }
            else
            {
                temp->next = new;
                temp = new;
            }

            (*gc) = new->ID;
        }
        else
        {
            free(new);
        }
    }

    fclose(fl);
    return;
}

void view_guests(Guest **head)
{
    if (*head == NULL)
    {
        printf("\n--No guests to display--\n");
        return;
    }
    else
    {
        printf("%-4s %-27s %-9s %-13s %-15s %-14s %-15s\n\n",
               "ID", "Name", "RoomNo.", "No. of People", "Paymentstatus", "Check-in Date", "Check-out Date");
        for (Guest *temp = *head; temp != NULL; temp = temp->next)
        {
            char status[10] = "Pending";
            if (temp->bill_status)
            {
                strcpy(status, "Paid");
            }
            printf("%-4d %-27s %-9d %-13d %-15s %02d.%02d.%-8d %02d.%02d.%-9d\n",
                   temp->ID,
                   temp->name,
                   temp->room_no,
                   temp->people,
                   status,
                   temp->check_in.day,
                   temp->check_in.month,
                   temp->check_in.year,
                   temp->check_out.day,
                   temp->check_out.month,
                   temp->check_out.year);
        }
    }
    return;
}
void search_guest(Guest **head)
{
    printf("\nEnter ID to search : ");
    int id;
    if (scanf("%d", &id) != 1)
    {
        printf("\n--INVALID ID--\n");
        return;
    }

    Guest *temp = *head;
    while (temp && temp->ID != id)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\nNo Guest Found\n");
        return;
    }
    char status[10] = "Pending";
    if (temp->bill_status)
    {
        strcpy(status, "Paid");
    }
    printf("ID                 : %d\nName               : %s\nRoom No            : %d\nTotal no of People : %d\nPayment Status     : %s\nCheck-in Date      : %02d.%02d.%d\nCheck-out Date     : %02d.%02d.%d\n",
           temp->ID,
           temp->name,
           temp->room_no,
           temp->people,
           status,
           temp->check_in.day,
           temp->check_in.month,
           temp->check_in.year,
           temp->check_out.day,
           temp->check_out.month,
           temp->check_out.year);
    return;
}
void clear_all_guests(Guest **head, int *gc)
{
    char confirm;
    Guest *temp = *head;
    printf("\n->ADMIN ALERT: Are you sure you want to wipe all guest data? (Y/N): ");
    if (scanf(" %c", &confirm) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (confirm == 'Y')
    {
        while (*head)
        {
            temp = temp->next;
            free(*head);
            *head = temp;
        }
        *gc = 0;
        printf("\n--SYSTEM RESET : ALL MEMORY IS CLEARED AND GUEST COUNTER IS RESET--\n");
        return;
    }
    return;
}

void admin_menu(Guest **head, int *gc)
{
    int choice;

    while (1)
    {
        printf("\n-----Admin Menu-----\n");
        printf(" 1. View All Guests : PRESS 1\n");
        printf(" 2. Search For Guest : PRESS 2\n");
        printf(" 3. Clear All : PRESS 3\n");
        printf(" 4. Exit to Main Menu : PRESS 4\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\n--INVALID CHOICE--\n");
            return;
        }

        switch (choice)
        {
        case 1:
            view_guests(head);
            break;
        case 2:
            search_guest(head);
            break;
        case 3:
            clear_all_guests(head, gc);
            break;
        case 4:
            return;
        default:
            printf("\n--Invalid choice--\n");
        }
    }
}
void book_room(Guest **head, int *gc)
{
    if (*gc >= 100)
    {
        printf("\n**************************************************\n");
        printf("!! SYSTEM ALERT: GUEST LIMIT EXCEEDED (Count: %d) !!\n", *gc);
        printf("!! ACTION REQUIRED: Notify Admin to clear past guests !!\n");
        printf("**************************************************\n");
        return;
    }
    int ppl;
    printf("\nEnter no of people to stay : ");
    if (scanf("%d", &ppl) != 1)
    {
        printf("--INVALID CHOICE--");
        return;
    }
    printf("\n--Choose one room from the following options for booking 1 room--\n");
    switch (ppl)
    {
    case 1:
        printf("1. Single Room        - 101\n2. Suite              - 103\n3. Deluxe Suite       - 104\n4. Presidential Suite - 106\n");
        break;
    case 2:
        printf("1. Double Room - 102\n2. Family Room - 105\n");
        break;
    case 3:
        printf("1. Family Room - 105\n");
        break;
    case 4:
        printf("1. Family Room - 105\n");
        break;
    default:
        printf("\n--Please try booking multiple rooms--\n");
        return;
    }
    int room_no;
    printf("Enter the room number of your choice : ");
    if (scanf("%d", &room_no) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }

    switch (ppl)
    {

    case 1:
        if (!(room_no == 101 || room_no == 104 || room_no == 103 || room_no == 106))
        {
            printf("\n--Invalid choice of room number--\n");
            return;
        }
        break;

    case 2:
        if (!(room_no == 102 || room_no == 105))
        {
            printf("\n--Invalid choice of room number--\n");
            return;
        }
        break;

    case 3:
        if (!(room_no == 105))
        {
            printf("\n--Invalid choice of room number--\n");
            return;
        }
        break;
    case 4:
        if (!(room_no == 105))
        {
            printf("\n--Invalid choice of room number--\n");
            return;
        }
        break;
    }
    Date ci, co;
    printf("\nEnter check-in date as (DD MM YYYY)\n");
    if (scanf("%d", &ci.day) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (scanf("%d", &ci.month) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (scanf("%d", &ci.year) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (checkifvalidDate(ci))
    {
        printf("\n--INVALID DATE--\n");
        return;
    }
    printf("\nEnter check-out date as (DD MM YYYY)\n");
    if (scanf("%d", &co.day) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (scanf("%d", &co.month) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (scanf("%d", &co.year) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (checkifvalidDate(co))
    {
        printf("\n--INVALID DATE--\n");
        return;
    }
    if (co.year < ci.year ||
        (co.year == ci.year && co.month < ci.month) ||
        (co.year == ci.year && co.month == ci.month && co.day < ci.day))
    {
        printf("\n--check-out date is earlier than check-in date --\n");
        return;
    }

    Guest *temp = *head;
    while (temp)
    {
        if (temp->room_no == room_no)
        {
            if (checkifclash(ci, co, temp->check_in, temp->check_out))
            {
                printf("\n--No rooms available for the selected period--\n");
                return;
            }
        }
        temp = temp->next;
    }
    Guest *new = malloc(sizeof(Guest));

    new->ID = (*gc) + 1;
    (*gc)++;
    new->people = ppl;
    new->room_no = room_no;
    printf("Please enter main contact name : ");
    scanf("%s", new->name);
    new->check_in = ci;
    new->check_out = co;
    new->bill_status = 0;
    new->next = NULL;
    printf("\nNote your Guest ID : %d\n", *gc);
    printf("\n-----Room Booked Successullyf-----\n");

    if (*head == NULL)
    {
        *head = new;
        return;
    }
    else
    {
        Guest *temp = *head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new;
    }

    return;
}

void check_out(Guest **head, int *gc)
{
    int ID;
    printf("Enter your ID : ");
    if (scanf("%d", &ID) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    Guest *cur = *head, *pre = NULL;
    while (cur && cur->ID != ID)
    {
        pre = cur;
        cur = cur->next;
    }
    if (cur == NULL)
    {
        printf("\n--Invalid ID--\n");
        return;
    }
    if (cur->bill_status)
    {
        printf("\n----Thank You Please Visit Again----\n");
        if (pre)
        {
            pre->next = cur->next;
        }
        else
        {
            (*head) = cur->next;
        }
        if (cur->next == NULL)
        {
            (*gc)--;
        }

        cur->next = NULL;
        free(cur);
        return;
    }
    else
    {
        printf("\n--Complete bill payment process to checkout--\n");
    }
    return;
}
void pay_bill(Guest **head)
{
    int ID;
    printf("\nEnter your ID : ");
    if (scanf("%d", &ID) != 1)
    {
        printf("\n--INVALID ID--\n");
        return;
    }
    Guest *cur = *head;
    while (cur && cur->ID != ID)
    {
        cur = cur->next;
    }
    if (cur == NULL)
    {
        printf("\n--Invalid ID--\n");
        return;
    }
    if (cur->bill_status)
    {
        printf("\n--Bill for ID %d has already been settled--\n", cur->ID);
        return;
    }
    float bill;
    int days;
    struct tm start = {0}, end = {0};
    start.tm_mday = cur->check_in.day;
    start.tm_mon = cur->check_in.month - 1;
    start.tm_year = cur->check_in.year - 1900;
    end.tm_mday = cur->check_out.day;
    end.tm_mon = cur->check_out.month - 1;
    end.tm_year = cur->check_out.year - 1900;
    time_t t1 = mktime(&start);
    time_t t2 = mktime(&end);
    days = difftime(t2, t1) / 86400;
    if (days == 0)
    {
        days = 1;
    }
    bill = (rooms[cur->room_no - 101].price) * days;
    printf("\nYour Bill : INR %.2f\n", bill);
    printf("\nDo Payment now ?(y/n) : ");
    char choice;
    if (scanf(" %c", &choice) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    };
    char receipt[20];
    if (choice == 'y')
    {
        FILE *fvr;

        sprintf(receipt, "Bill_ID_%02d.txt", cur->ID);
        fvr = fopen(receipt, "w");
        if (fvr == NULL)
        {
            printf("\nNo permission to write to a file\n");
            return;
        }
        fprintf(fvr, "===============================================\n");
        fprintf(fvr, "-------------------HOTEL BILL------------------\n");
        fprintf(fvr, "===============================================\n");
        fprintf(fvr, "Name           :%s\n", cur->name);
        fprintf(fvr, "Guest ID       :%d\n", cur->ID);
        fprintf(fvr, "Check-in Date  :%02d.%02d.%d\n", cur->check_in.day, cur->check_in.month, cur->check_in.year);
        fprintf(fvr, "Check-out Date :%02d.%02d.%d\n\n", cur->check_out.day, cur->check_out.month, cur->check_out.year);
        fprintf(fvr, "Cost per Day   :INR %.2f\n", rooms[cur->room_no - 101].price);
        fprintf(fvr, "----------------------------------------------\n");
        fprintf(fvr, "Total          :INR %.2f\n", bill);
        fprintf(fvr, "----------------------------------------------\n");
        fprintf(fvr, "                        Contact    : 990011223\n\n");
        fclose(fvr);
        printf("--Your receipt has been generated successfully as Bill_ID_%02d.txt--\n\n", cur->ID);

        cur->bill_status = 1;
    }
    printf("DO YOU WANT TO VIEW RECEIPT ?(y/n) : ");
    char cc;
    if (scanf(" %c", &cc) != 1)
    {
        printf("\n--INVALID CHOICE--\n");
        return;
    }
    if (cc == 'y')
    {
        FILE *fo;
        fo = fopen(receipt, "r");
        char tp[256];
        while (fgets(tp, 256, fo) != NULL)
        {
            printf("%s", tp);
        }
        fclose(fo);
    }
    return;
}
void guest_menu(Guest **head, int *gc)
{
    int choice;

    while (1)
    {
        printf("\n-----Guest Menu-----\n");
        printf("1. Book Room : PRESS 1\n");
        printf("2. Check Out : PRESS 2\n");
        printf("3. Pay Bill : PRESS 3\n");
        printf("4. Exit to Main Menu : PRESS 4\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\n--INVALID CHOICE--\n");
            return;
        }

        switch (choice)
        {
        case 1:
            book_room(head, gc);
            break;
        case 2:
            check_out(head, gc);
            break;
        case 3:
            pay_bill(head);
            break;
        case 4:
            return;
        default:
            printf("\n--Invalid choice--\n");
        }
    }
}