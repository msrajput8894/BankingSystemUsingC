#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a unique 16-digit account number
unsigned long long generateAccountNumber()
{
  // Use the current timestamp as a seed
  srand(time(NULL));

  // Generate the first digit (1-9)
  unsigned long long accNo = 0;
  for (int i = 0; i < 16; i++)
  {
    accNo = accNo * 10 + rand() % 10;
  }

  return accNo;
}

struct user
{
  unsigned long long accountNo;
  char aadharNo[20];
  char firstName[20];
  char lastName[20];
  char phoneNo[15];
  char password[30];
  float balance;
};

int main()
{
  struct user usr, usr1;
  FILE *fp;
  char filename[50], phone[15], pword[30];
  int opt, choice;
  char cont = 'y';
  float amount;

  printf("\nAlready a customer? please select login! if new to our bank please select Register!");
  printf("\n1. Register an account");
  printf("\n2. Login to your account");
  printf("\n3. Exit");

  printf("\nPlease select option: ");

  scanf("%d", &opt);

  if (opt == 1)
  {
    system("cls");
    printf("\nEnter your First Name:\t ");
    scanf("%s", usr.firstName);
    printf("\nEnter your Last Name:\t ");
    scanf("%s", usr.lastName);
    printf("\nEnter you Aadhar No:\t ");
    scanf("%s", usr.aadharNo);
    printf("\nPlease enter your phone number:\t");
    scanf("%s", usr.phoneNo);
    printf("\nPlease enter you password:\t");
    scanf("%s", usr.password);
    usr.balance = 0;
    strcpy(filename, usr.phoneNo);
    fp = fopen(strcat(filename, ".dat"), "w");
    fwrite(&usr, sizeof(struct user), 1, fp);
    usr.accountNo = generateAccountNumber();
    if (fwrite != 0)
    {

      printf("\n\nAccount registered successfully!");
      printf("\nYour account number is %llu ", usr.accountNo);
    }
    else
    {
      printf("Something went wrong :( Please try again later...");
    }
    fclose(fp);
  }
  if (opt == 2)
  {
    system("cls");
    printf("Please Enter you Phone number:\t");
    scanf("%s", &phone);
    printf("\nPlease Enter you password:\t");
    scanf("%s", &pword);
    strcpy(filename, phone);
    fp = fopen(strcat(filename, ".dat"), "r");
    if (fp == NULL)
    {
      printf("\nAccount number not registered!");
    }
    else
    {

      fread(&usr, sizeof(struct user), 1, fp);
      fclose(fp);
      if (!strcmp(pword, usr.password))
      {
        system("cls");
        printf("\n\n-----------------------------------------------------------------------------------------------------\n");
        printf("\n\t-------------------------Welcome to Bank of Mohadi-------------------------");
        printf("\n\n-----------------------------------------------------------------------------------------------------\n");
        printf("\nAccount Holder Name:%s %s ", usr.firstName, usr.lastName);
        printf("\nAccount Number: %llu", usr.accountNo);
        printf("\nContact Details: %s", usr.phoneNo);
        printf("\nAadhar Number: %s", usr.aadharNo);
        printf("\n\n\n-----------------------------------------------------------------------------------------------------\n");

        printf("\n\t\t\t\t\tWelcome! %s %s", usr.firstName, usr.lastName);
        printf("\n\n------------------------------------------------------------------------------------------------------");
        while (cont == 'y')
        {

          printf("\nPress 1 to check balance");
          printf("\nPress 2 to deposit an amount");
          printf("\nPress 3 to withdraw an amount");
          printf("\nPress 4 to online tranfer");
          printf("\nPress 5 to change password");

          printf("\n\nEnter your choice: ");
          scanf("%d", &choice);

          switch (choice)
          {
          case 1:
            system("cls");
            printf("\n\nYour account balance is %.2f", usr.balance);
            break;

          case 2:
            system("cls");
            printf("\nPlease Enter the amount you wish to deposit: ");
            scanf("%f", &amount);
            usr.balance += amount;
            fp = fopen(filename, "w");
            fwrite(&usr, sizeof(struct user), 1, fp);
            if (fwrite != NULL)
            {
              system("cls");
              printf("\n%.2f Successfully deposited to your account! \n\nAvailable account balance is %.2f", amount, usr.balance);
            }
            fclose(fp);
            break;

          case 3:
            system("cls");
            printf("\nPlease Enter the amount you wish to withdraw: ");
            scanf("%f", &amount);
            usr.balance -= amount;
            fp = fopen(filename, "w");
            fwrite(&usr, sizeof(struct user), 1, fp);
            if (fwrite != NULL)
            {
              system("cls");
              printf("\n%.2f has been withdrawed from you account... \n\nAvailable account balance is %.2f", amount, usr.balance);
            }
            fclose(fp);
            break;
          case 4:
            printf("Please Enter the Phone number to which you wish to transfer the amount: ");
            scanf("%s", &phone);
            printf("\nPlease enter the amount to transfer: ");
            scanf("%f", &amount);
            strcpy(filename, phone);
            fp = fopen(strcat(filename, ".dat"), "r");
            if (fp == NULL)
            {
              printf("\nNo account found registered with %s, Make sure you have provided the correct phone number!", phone);
            }
            else
            {

              fread(&usr1, sizeof(struct user), 1, fp);
              fclose(fp);
              if (amount > usr.balance)
              {
                printf("\nInsufficient Balance...");
              }
              else
              {

                fp = fopen(filename, "w");
                usr1.balance += amount;
                fwrite(&usr1, sizeof(struct user), 1, fp);
                fclose(fp);
                if (fwrite != NULL)
                {
                  printf("\nYou have successfully transferred the amount of %.2fRs to %s.\n\nYour available balance is %.2f", amount, phone, usr.balance - amount);
                  strcpy(filename, usr.phoneNo);
                  fp = fopen(strcat(filename, ".dat"), "w");
                  usr.balance -= amount;
                  fwrite(&usr, sizeof(struct user), 1, fp);
                  fclose(fp);
                }
              }
            }
            break;
          case 5:
            system("cls");
            printf("\nPlease Enter your password: ");
            scanf("%s", &pword);
            if (!strcmp(pword, usr.password))
            {
              printf("\nEnter new password: ");
              scanf("%s", &pword);
              fp = fopen(filename, "w");
              strcpy(usr.password, pword);
              fwrite(&usr, sizeof(struct user), 1, fp);
              if (fwrite != NULL)
              {
                printf("\nPassword changed successfully!");
              }
            }
            else
            {
              printf("\nIncorrect Password :(\nPlease provide the correct password!");
            }
            break;

          default:
            printf("Invalid Input! try again later...");
            break;
          }

          printf("\nDo you want to continue the transactios: [y/n]\t");
          getchar();
          scanf("%c", &cont);
          system("cls");
        }
      }
      else
      {

        printf("\nInvalid password! Please try again...");
      }
    }
  }
  getchar();
  return 0;
}