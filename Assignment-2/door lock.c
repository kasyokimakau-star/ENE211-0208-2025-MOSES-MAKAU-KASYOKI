#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #define DELAY_1S() Sleep(1000)      /* milliseconds on Windows */
#else
    #include <unistd.h>
    #define DELAY_1S() sleep(1)         /* seconds on Linux/macOS */
#endif

#define MAX_ATTEMPTS 3
#define PIN_LENGTH   4
#define LOCK_SECONDS 5

static int is_all_digits(const char *s) {
    for (; *s; s++) {
        if (!isdigit((unsigned char)*s)) return 0;
    }
    return 1;
}

static int is_valid_pin(const char *pin) {
    return strlen(pin) == PIN_LENGTH && is_all_digits(pin);
}

static void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void show_menu(void) {
    printf("\n=== Device Menu ===\n");
    printf("1. Open Door\n");
    printf("2. Change Username\n");
    printf("3. Change PIN\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

static void lockout(void) {
    printf("System locked! Wait for %d seconds...\n", LOCK_SECONDS);
    for (int i = LOCK_SECONDS; i >= 1; i--) {
        printf("%d... ", i);
        fflush(stdout);
        DELAY_1S();
    }
    printf("\nYou can try again now.\n\n");
}

int main(void) {
    char correctPin[20] = "9999";
    char username[30]   = "admin";
    char userPin[20];

    int granted = 0;

    /* Keep allowing rounds of 3 attempts until access is granted */
    while (!granted) {
        int attempt = 0;

        while (attempt < MAX_ATTEMPTS) {
            printf("Enter PIN: ");
            if (scanf("%19s", userPin) != 1) {
                printf("\nInput error\n");
                return 1;
            }

            if (!is_valid_pin(userPin)) {
                printf("PIN must be %d digits\n", PIN_LENGTH);
                attempt++;
            } else if (strcmp(userPin, correctPin) == 0) {
                printf("Access Granted\n");
                granted = 1;
                break;
            } else {
                printf("Access Denied\n");
                attempt++;
            }

            printf("Remaining attempts: %d\n", MAX_ATTEMPTS - attempt);
        }

        if (!granted) {
            lockout();
        }
    }

    /* Device menu */
    int choice = 0;
    while (choice != 4) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            clear_input();
            printf("Invalid input. Enter a number from 1 to 4.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                printf("Door opened.\n");
                break;
            case 2:
                printf("Enter new username: ");
                if (scanf("%29s", username) == 1) {
                    printf("Username changed to %s\n", username);
                }
                break;
            case 3:
                printf("Enter new PIN: ");
                if (scanf("%19s", userPin) == 1) {
                    if (is_valid_pin(userPin)) {
                        strcpy(correctPin, userPin);
                        printf("PIN changed successfully.\n");
                    } else {
                        printf("PIN must be %d digits. PIN not changed.\n", PIN_LENGTH);
                    }
                }
                break;
            case 4:
                printf("Goodbye, %s.\n", username);
                break;
            default:
                printf("Invalid option. Choose 1-4.\n");
        }
    }

    return 0;
}
