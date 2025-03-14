#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <time.h>     
#include <math.h>     


struct Account {                                
    int accountNumber;                          
    char accountName[40];                       
    char accountType[10];                       
    int balance;                                
};

// For saving accounts
struct Account accounts[100];                   
int accountCount = 0;                           

int findAccounts(char *accountName);            
int findAccount(int accountNumber);             
void createAccount();
void checkBalance();
void deposit();
void withdraw();
void calculateCompoundInterest();
void transferMoney();
void displayMenu();
void saveAccountsToFile();
void loadAccountsFromFile();


int findAccounts(char *accountName){                                   
    int count = 0;                                                      
    for (int i = 0; i < accountCount; i++){                             
        if (strcmp(accounts[i].accountName, accountName) == 0){
            count++;
        }
    }
    return count;
}

// Function to find an account by account number
int findAccount(int accountNumber) {                                   
    for (int i = 0; i < accountCount; i++) {                            
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

// Function to create a new account
void createAccount() {
    if (accountCount >= 100) {                                          
        printf("\nMaximum account limit reached!\n");
        return;
    }

    struct Account newAccount;                                         
    printf("\nEnter your full name:\n");
    scanf(" %[^\n]", newAccount.accountName);

    // Check how many accounts the person already has
    int personAccounts = findAccounts(newAccount.accountName);          
    if (personAccounts >= 2) {
        printf("Each person can only have 2 accounts!\n");
        return;
    }

    printf("\nEnter type of account (savings, current):\n");           
    scanf(" %[^\n]", newAccount.accountType);

    // For generating a random number as account number
    srand(time(0) + accountCount);                                      
    newAccount.accountNumber = ((rand()*rand())%900000)+100000;
    newAccount.balance = 0;                                             

    accounts[accountCount++] = newAccount;                              

    printf("\nAccount created successfully!\n");
    printf("Account Name: %s\n", newAccount.accountName);
    printf("Account Number: %d\n", newAccount.accountNumber);
    printf("Account Type: %s\n", newAccount.accountType);

    saveAccountsToFile();                                               
}

// Function to check balance
void checkBalance() {
    int accountNumber;                                                  
    printf("Enter account number:\n");
    scanf("%d", &accountNumber);

    int index = findAccount(accountNumber);                             
    if (index != -1) {
        printf("\nAccount Balance: %d\n", accounts[index].balance);
    } else {
        printf("\nAccount not found!\n");
    }
}

// Function for amount deposit
void deposit() {
    int accountNumber, amount;                                         
    printf("Enter account number:\n");
    scanf("%d", &accountNumber);

    int index = findAccount(accountNumber);                             
    if (index != -1) {
        printf("Enter amount to deposit:\n");
        scanf("%d", &amount);
        if (amount > 0) {                                               
            accounts[index].balance += amount;
            printf("\nAmount Deposited Successfully!\n");
            printf("Updated Balance: %d\n", accounts[index].balance);
            saveAccountsToFile();                                       
        } else {
            printf("\nInvalid amount!\n");
        }
    } else {
        printf("\nAccount not found!\n");
    }
}

// Function for amount withdrawal
void withdraw() {
    int accountNumber, amount;
    printf("Enter account number:\n");
    scanf("%d", &accountNumber);

    int index = findAccount(accountNumber);                               
    if (index != -1) {
        printf("Enter amount to withdraw:\n");
        scanf("%d", &amount);

        if (amount >= 500 && amount <= (accounts[index].balance - 100)) {   
            accounts[index].balance -= amount;
            printf("\nAmount Withdrawn Successfully!\n");
            printf("Updated Balance: %d\n", accounts[index].balance);
            saveAccountsToFile();                                           
        } else if(amount < 500){
            printf("\nMinimum withdraw amount is 500\n");
        } else {
            printf("Minimum balance should be 100\n");
        }
    } else {
        printf("\nAccount not found!\n");
    }
}

// Function for calculate interest over a time period
void calculateCompoundInterest() {
    int accountNumber;
    printf("Enter account number:\n");
    scanf("%d", &accountNumber);

    int index = findAccount(accountNumber);                        
                                                                
    if (index != -1) {
        float rate;
        int time_period;
        printf("Enter annual interest rate (in %):\n");
        scanf("%f", &rate);
        printf("Enter time period (in years):\n");
        scanf("%d", &time_period);

        if(accounts[index].balance > 0){
        // Formula for compound interest
        double amount = accounts[index].balance * pow((1 + rate / 100), time_period);
        double interest = amount - accounts[index].balance;

        printf("\nCompound Interest: %.2f\n", interest);
        printf("Total Amount after Interest: %.2f\n", amount);
    } else {
        printf("\Invalid account balance!\n");
    }
}else{
    printf("\nAccount not found!\n");
    }
}

// Function to transfer money
void transferMoney(){                                          
                                                                
    int sourceAccount, targetAccount, amount;
    printf("Enter source account number:\n");
    scanf("%d", &sourceAccount);
    int sourceIndex = findAccount(sourceAccount);
    if (sourceIndex == -1) {
        printf("\nSource account not found!\n");
        return;
    }

    printf("Enter target account number:\n");
    scanf("%d", &targetAccount);
    int targetIndex = findAccount(targetAccount);
    if (targetIndex == -1) {
        printf("\nTarget account not found!\n");
        return;
    }

    printf("Enter amount to transfer:\n");
    scanf("%d", &amount);

    if (amount <= (accounts[sourceIndex].balance - 100)) {
        accounts[sourceIndex].balance -= amount;
        accounts[targetIndex].balance += amount;
        printf("\nMoney transferred successfully!\n");
        saveAccountsToFile();  // Save accounts to file after transfer
    } else {
        printf("\nInsufficient balance\nNOTE : Minimum balance should be 100\n");
    }
}

// Function to save accounts to a file
void saveAccountsToFile() {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d\t%s\t%s\t%d\n", accounts[i].accountNumber, accounts[i].accountName, accounts[i].accountType, accounts[i].balance);
    }

    fclose(file);
}

// Function to load accounts from a file
void loadAccountsFromFile() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        return;
    }

    accountCount = 0;
    while (fscanf(file, "%d %[^\t] %s %d",&accounts[accountCount].accountNumber, accounts[accountCount].accountName, accounts[accountCount].accountType, &accounts[accountCount].balance) == 4) {
        accountCount++;
    }

    fclose(file);
}

// Function to display the main menu
void displayMenu(){
    printf("\n--* WELCOME TO OUR BANK PAGE *--\n");                         
    printf("\n->To create an account: PRESS 'a'\n");
    printf("->To open an existing account: PRESS 'o'\n");
}

// MAIN FUNCTION
int main() {
    loadAccountsFromFile();  // Load accounts from file at the start

    char choice;
    while (1) {
        displayMenu();
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                createAccount();
                break;
            case 'o':
                printf("Enter the account number: ");
                int acc;
                scanf(" %d", &acc);
                int index = findAccount(acc);
                if (index != -1) {
                    char ch;
                    printf("\n->To deposit money: press 'd'\n");
                    printf("->To withdraw money: press 'w'\n");
                    printf("->To check balance: press 'b'\n");
                    printf("->To calculate interest: press 'i'\n");
                    printf("->Transfer money to different account: press 't'\n");
                    printf("->To exit: press 'e'\n");
                    printf("->Enter your choice:\n");
                    scanf(" %c", &ch);
                    switch (ch) {
                        case 'd':
                            deposit();
                            break;
                        case 'w':
                            withdraw();
                            break;
                        case 'b':
                            checkBalance();
                            break;
                        case 'i':
                            calculateCompoundInterest();
                            break;
                        case 't':
                            transferMoney();
                            break;
                        case 'e':
                            printf("\nThanks for using our service. Have a great day ahead!\n");
                            saveAccountsToFile();  // Save accounts to file before exiting
                            return 0;
                        default:
                            printf("\nInvalid input, please try again.\n");
                            break;
                    }
                } else {
                    printf("\nAccount not found!\n");
                }
                break;

            default:
                printf("Invalid input, please try again.\n");
                break;
        }
    }

    return 0;
}
