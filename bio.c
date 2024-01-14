#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Node structure to store attendance information
struct Node
{
    char name[20];
    int id;
    char intime[80];
    char outtime[80];
    struct Node *next;
};

// Function to display the total number of attendance records
void length(struct Node *head)
{
    if (head == NULL)
    {
        printf("no attendance registered");
    }
    else
    {
        int count = 0;
        while (head != NULL)
        {
            count++;
            head = head->next;
        }
        printf("total %d attendance have been registered\n", count);
    }
}

// Function to add a new attendance record
struct Node *add(struct Node *head, char name[30], int id)
{
    if (head == NULL)
    {
        // Creating a new node for the first attendance record
        struct Node *head = (struct Node *)malloc(sizeof(struct Node));
        strcpy(head->name, name);
        head->id = id;
        head->next = NULL;
        head->outtime[0] = '\0';

        // Get the current time in UTC
        time_t rawtime;
        struct tm *info;
        char buffer[80];
        time(&rawtime);
        info = gmtime(&rawtime);

        // Adjust the time to Indian Standard Time (IST)
        info->tm_hour += 5; // Add 5 hours for IST
        info->tm_min += 30; // Add 30 minutes for IST

        // Handle overflow in case adding hours/minutes exceeds 24 hours/60 minutes
        if (info->tm_min >= 60)
        {
            info->tm_min -= 60;
            info->tm_hour += 1;
        }
        if (info->tm_hour >= 24)
        {
            info->tm_hour -= 24;
        }

        // Format and print the current time in IST
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S IST", info);
        strcpy(head->intime, buffer);

        printf("\n*** WELCOME ***\n");
        printf("Name : %s\n", head->name);
        printf("ID no. : %d\n", head->id);
        printf("Registered time is  : %s\n", buffer);

        return head;
    }
    else
    {
        // Creating a new node for subsequent attendance records
        struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
        strcpy(ptr->name, name);
        ptr->id = id;
        ptr->next = head;

        // Get the current time in UTC
        time_t rawtime;
        struct tm *info;
        char buffer[80];
        time(&rawtime);
        info = gmtime(&rawtime);

        // Adjust the time to Indian Standard Time (IST)
        info->tm_hour += 5; // Add 5 hours for IST
        info->tm_min += 30; // Add 30 minutes for IST

        // Handle overflow in case adding hours/minutes exceeds 24 hours/60 minutes
        if (info->tm_min >= 60)
        {
            info->tm_min -= 60;
            info->tm_hour += 1;
        }
        if (info->tm_hour >= 24)
        {
            info->tm_hour -= 24;
        }

        // Format and print the current time in IST
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S IST", info);
        strcpy(ptr->intime, buffer);

        printf("\n*** WELCOME ***\n");
        printf("Name : %s\n", ptr->name);
        printf("ID no. : %d\n", ptr->id);
        printf("Registered time is  : %s\n", buffer);

        ptr->outtime[0] = '\0';

        return ptr;
    }
}

// Function to display details about a specific attendance record
void display(struct Node *head, int id)
{
    if (head == NULL)
    {
        printf("no one had registered yet\n");
    }
    else
    {
        int flag = 0;
        while (head != NULL)
        {
            if (head->id == id)
            {
                printf("Name : %s\n", head->name);
                printf("ID no. : %d\n", head->id);
                printf("Registered time is  : %s\n", head->intime);

                if (strcmp(head->outtime, "") == 0)
                {
                    printf("Didn't logout yet\n");
                }
                else
                {
                    printf("Logout time is : %s\n", head->outtime);
                }

                flag = 1;
            }
            head = head->next;
        }

        if (flag == 0)
        {
            printf("Enter correct employee id \n");
        }
    }
}

// Function to re-register attendance for a specific employee
struct Node *re(struct Node *head, int id)
{
    if (head == NULL)
    {
        printf("no one had registered yet\n");
    }
    else
    {
        int flag = 0;
        struct Node *root = head;
        while (head != NULL)
        {
            if (head->id == id)
            {
                time_t rawtime;
                struct tm *info;
                char buffer[80];
                time(&rawtime);
                info = gmtime(&rawtime);

                // Adjust the time to Indian Standard Time (IST)
                info->tm_hour += 5; // Add 5 hours for IST
                info->tm_min += 30; // Add 30 minutes for IST

                // Handle overflow in case adding hours/minutes exceeds 24 hours/60 minutes
                if (info->tm_min >= 60)
                {
                    info->tm_min -= 60;
                    info->tm_hour += 1;
                }
                if (info->tm_hour >= 24)
                {
                    info->tm_hour -= 24;
                }

                // Format and print the current time in IST
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S IST", info);
                strcpy(head->outtime, buffer);

                printf("*** THANK YOU ***\n");
                printf("Name : %s\n", head->name);
                printf("ID no. : %d\n", head->id);
                printf("Registered time is  : %s\n", head->intime);
                printf("Logout time is : %s\n", head->outtime);

                flag = 1;
                return root;
            }
            head = head->next;
        }

        if (flag == 0)
        {
            printf("Please enter the correct employee id\n");
            return root;
        }
    }
}

// Function to save attendance details to a file
void quit(struct Node *head)
{
    if (head == NULL)
    {
        printf("No one had registered yet\n");
    }
    else
    {
        FILE *fptr;
        fptr = fopen("attendance.txt", "w");

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int i = 1;

        fprintf(fptr, "\n ***  Attendance Register *** ");
        fprintf(fptr, "\n Date : %02d-%02d-%d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        while (head != NULL)
        {
            fprintf(fptr, "\n%d) Name : %s", i, head->name);
            fprintf(fptr, "\n ID : %d", head->id);
            fprintf(fptr, "\n Login time : %s", head->intime);

            if (strcmp(head->outtime, "") == 0)
            {
                fprintf(fptr, "\n Didn't logout yet \n");
            }
            else
            {
                fprintf(fptr, "\n Logout time : %s \n", head->outtime);
            }

            i++;
            head = head->next;
        }

        fclose(fptr);
    }
}

// Function to display overall attendance information
void info(struct Node *head)
{
    if (head == NULL)
    {
        printf("No one had registered yet\n");
    }
    else
    {
        int count = 0;
        int flag = 0;

        while (head != NULL)
        {
            if (strcmp(head->outtime, "") == 0)
            {
                // Count only records where logout time is available
            }
            else
            {
                count++;
            }

            flag++;
            head = head->next;
        }

        printf("Total number of logins: %d\n", flag);
        printf("Total number of logouts: %d\n", count);
    }
}

// Function to display the names of employees who haven't logged out yet
void logout(struct Node *head)
{
    if (head == NULL)
    {
        printf("No one had registered yet\n");
    }
    else
    {
        int flag = 0;
        while (head != NULL)
        {
            if (strcmp(head->outtime, "") == 0)
            {
                // Display the names of employees who haven't logged out yet
            }
            else
            {
                // Display the names of employees who have logged out yet
                printf("Name : %s\n", head->name);
                flag = 1;
            }

            head = head->next;
        }
        if (flag == 0)
        {
            printf("no one had logged out yet\n");
        }
    }
}

// Main function to run the attendance system
int main()
{
    struct Node *head = NULL;
    int ch, id;

    while (1)
    {
        printf("\n***** Attendance Register *****\n");
        printf("1. Register your Attendance\n"); 
        printf("2. Information about Attendance\n");
        printf("3. Details about your attendance\n");
        printf("4. Total number of Attendance\n");
        printf("5. Re-Register your attendance\n");
        printf("6. Logout information\n");
        printf("7. Exit\n");

        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter your name\n");
            char name[20];
            scanf("%s", &name);
            printf("Enter your id\n");
            scanf("%d", &id);
            head = add(head, name, id);
            sleep(3);
            system("cls");
            break;

        case 2:
            info(head);
            sleep(3);
            system("cls");
            break;

        case 3:
            printf("Enter your id\n");
            scanf("%d", &id);
            display(head, id);
            sleep(3);
            system("cls");
            break;

        case 4:
            length(head);
            sleep(3);
            system("cls");
            break;

        case 5:
            printf("Enter your id\n");
            scanf("%d", &id);
            head = re(head, id);
            sleep(3);
            system("cls");
            break;

        case 6:
            logout(head);
            sleep(3);
            system("cls");
            break;

        case 7:
            quit(head);
            exit(0);

        default:
            printf("Invalid input\n");
        }
    }
}