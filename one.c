#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>

// edited by nishank

int random_number(){
    srand(time(NULL));
    int secret = rand() % 100 + 1;
    return secret;
}
void number_guessing(){
    int number = random_number();
    int guess;

    printf("\nThis is number guessing game\n");
    printf("You have to guess the correct number which is totally random and it is between 1 to 100\n\n");
    
    int attempts = 0;

    
    int flag = 1;
    while(flag){
        scanf("%d", &guess);
        attempts++;

        if(guess < (number-30)){
            printf("Too Low\n\n");
        }
        else if(guess < (number-15)){
            printf("Low\n\n");
        }
        else if(guess < (number)){
            printf("Close but Low\n\n");
        }
        else if(guess > (number)){
            printf("Close but High\n\n");
        }
        else if(guess > (number+15)){
            printf("High\n\n");
        }
        else if(guess > (number+30)){
            printf("Too High\n\n");
        }

        if(guess == number){
            printf("You guess right\n\n");
            flag = 0;
        }
        }
        printf("You took %d attempts\n", attempts);

    }

int unlock_device()
{
    char string[50];
    printf("Enter \"UNLOCK\" to begin\n");
    scanf("%s", string);

    if (strcmp(string, "UNLOCK") == 0)
    {
        printf("Device Unlocked\n");
        return 1;
    }
    else
    {
        printf("Access Denied");
        return 0;
    }
}

// can add more functions in the calculator later when the whole structure is done...
// calc is done for now
float calculator()
{
    float a, b;
    char operator;
    printf("\nWelcome to the calculator!\n");

    printf("Enter first number: ");
    scanf("%f", &a);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);
    printf("Enter second number: ");
    scanf("%f", &b);

    switch (operator)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b != 0)
        {
            return a / b;
        }
        else
        {
            printf("Error");
            return 0;
        }
    default:
        printf("Invalid operator");
        return 0;
    }
}

int menu()
{

    int choice;
    printf("\nMain Menu:\n");
    printf("1. Calculator\n");
    printf("2. Number guessing game\n");
    printf("3. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void what_to_do(int choice)
{
    switch (choice)
    {
    case 1:
    {
        float result = calculator();
        if (result == (int)result)
        {
            printf("Result: %d\n", (int)result);
        }
        else
        {
            printf("Result: %.2f\n", result);
        }
        break;
    }

    case 2:
        number_guessing();
        break;

    case 3:
        printf("Exiting menu...\n");
        break;

    default:
        printf("Invalid Choice\n");
    }
}

int main()
{
    if (!unlock_device())
    {
        return 0;
    }

    int flag = 1;
    while (flag)
    {
        int choice = menu();
        if (choice == 3)
        {
            printf("You chose to exit from the menu.\n");
            break;
        }

        what_to_do(choice);

        char cont;
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &cont);
        if (cont == 'n' || cont == 'N')
        {
            flag = 0;
            printf("You have exited, and device is locked...\n");
        }
    }
    return 0;
}
