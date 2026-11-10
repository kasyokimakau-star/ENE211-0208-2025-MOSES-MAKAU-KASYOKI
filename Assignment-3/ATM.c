#include <stdio.h>
#include <stdbool.h>

#define STORED_PIN    1234
#define MAX_ATTEMPTS  3

static double balance = 1000.00;   /* starting balance */

/* ---------- Input helpers ---------- */

/* Clear leftover characters from the input buffer */
static void clearInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Read an integer safely; returns false on invalid input or EOF */
static bool readInt(int *value)
{
    if (scanf("%d", value) != 1) {
        if (feof(stdin)) {
            *value = 4;            /* treat EOF as Exit */
            return true;
        }
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

/* Read a double safely; returns false on invalid input */
static bool readDouble(double *value)
{
    if (scanf("%lf", value) != 1) {
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

/* ---------- Required functions ---------- */

/* Requirement 1: PIN verification, limited attempts */
bool login(void)
{
    int pin;

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("Enter your PIN: ");
        if (!readInt(&pin)) {
            printf("Invalid input. PIN must be numeric.\n");
        } else if (pin == STORED_PIN) {
            printf("Login successful.\n\n");
            return true;
        } else {
            printf("Incorrect PIN.\n");
        }
        if (attempt < MAX_ATTEMPTS) {
            printf("Attempts remaining: %d\n", MAX_ATTEMPTS - attempt);
        }
    }

    printf("Too many failed attempts. Access denied.\n");
    return false;
}

/* Requirement 2: display the menu */
void showMenu(void)
{
    printf("\n===== ATM MENU =====\n");
    printf("1. Balance Inquiry\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void checkBalance(void)
{
    printf("Your current balance is: %.2f\n", balance);
}

/* Requirement 5: amount must be positive */
void deposit(double amount)
{
    if (amount <= 0) {
        printf("Invalid amount. Deposit must be a positive number.\n");
        return;
    }
    balance += amount;
    printf("Deposited %.2f. New balance: %.2f\n", amount, balance);
}

/* Requirement 5: amount must be positive and not exceed balance */
void withdraw(double amount)
{
    if (amount <= 0) {
        printf("Invalid amount. Withdrawal must be a positive number.\n");
        return;
    }
    if (amount > balance) {
        printf("Insufficient funds. Your balance is %.2f\n", balance);
        return;
    }
    balance -= amount;
    printf("Withdrew %.2f. New balance: %.2f\n", amount, balance);
}

/* ---------- Main ---------- */

int main(void)
{
    int choice;
    double amount;

    printf("===== SIMULATED ATM =====\n");

    if (!login()) {
        return 1;                  /* deny access and exit */
    }

    /* Requirements 3 & 4: handle choice, repeat until Exit */
    do {
        showMenu();

        if (!readInt(&choice)) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                printf("Enter amount to deposit: ");
                if (readDouble(&amount)) deposit(amount);
                else printf("Invalid input. Please enter a number.\n");
                break;
            case 3:
                printf("Enter amount to withdraw: ");
                if (readDouble(&amount)) withdraw(amount);
                else printf("Invalid input. Please enter a number.\n");
                break;
            case 4:
                printf("Thank you for using the ATM. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please choose 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}
