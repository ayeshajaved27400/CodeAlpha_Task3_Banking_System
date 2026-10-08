#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Transaction Class
class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() {
        cout << left << setw(15) << type
             << setw(12) << amount
             << details << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        transactions.push_back(
            Transaction("Deposit", amount, "Money deposited")
        );

        cout << "Deposit successful!\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;
        transactions.push_back(
            Transaction("Withdrawal", amount, "Money withdrawn")
        );

        cout << "Withdrawal successful!\n";
        return true;
    }

    bool transferTo(Account &receiver, double amount) {
        if (amount <= 0) {
            cout << "Invalid transfer amount!\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(
            Transaction("Transfer", amount,
                        "Transferred to Account " +
                        to_string(receiver.accountNumber))
        );

        receiver.transactions.push_back(
            Transaction("Received", amount,
                        "Received from Account " +
                        to_string(accountNumber))
        );

        cout << "Fund transfer successful!\n";
        return true;
    }

    void displayAccountInfo() {
        cout << "\n--- Account Information ---\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << fixed << setprecision(2)
             << balance << endl;
    }

    void displayTransactions() {
        cout << "\n--- Transaction History ---\n";

        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        cout << left << setw(15) << "Type"
             << setw(12) << "Amount"
             << "Details" << endl;

        cout << "------------------------------------------\n";

        for (Transaction &transaction : transactions) {
            transaction.display();
        }
    }
};

// Customer Class
class Customer {
private:
    int customerID;
    string name;
    vector<Account> accounts;

public:
    Customer(int id, string customerName) {
        customerID = id;
        name = customerName;
    }

    int getCustomerID() {
        return customerID;
    }

    string getName() {
        return name;
    }

    void createAccount(int accountNumber) {
        accounts.push_back(Account(accountNumber));
        cout << "Account created successfully!\n";
    }

    Account* findAccount(int accountNumber) {
        for (Account &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }

        return nullptr;
    }

    void displayCustomerInfo() {
        cout << "\n--- Customer Information ---\n";
        cout << "Customer ID: " << customerID << endl;
        cout << "Name: " << name << endl;

        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        cout << "Accounts:\n";

        for (Account &account : accounts) {
            cout << "Account No: "
                 << account.getAccountNumber()
                 << " | Balance: "
                 << account.getBalance() << endl;
        }
    }
};

int main() {
    Customer customer(101, "Ayesha");

    int choice;

    do {
        cout << "\n========== BANKING SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Display Account Information\n";
        cout << "6. View Transaction History\n";
        cout << "7. Display Customer Information\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int accountNumber;

            cout << "Enter account number: ";
            cin >> accountNumber;

            customer.createAccount(accountNumber);
        }

        else if (choice == 2) {
            int accountNumber;
            double amount;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account *account = customer.findAccount(accountNumber);

            if (account != nullptr) {
                cout << "Enter deposit amount: ";
                cin >> amount;

                account->deposit(amount);
            }
            else {
                cout << "Account not found!\n";
            }
        }

        else if (choice == 3) {
            int accountNumber;
            double amount;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account *account = customer.findAccount(accountNumber);

            if (account != nullptr) {
                cout << "Enter withdrawal amount: ";
                cin >> amount;

                account->withdraw(amount);
            }
            else {
                cout << "Account not found!\n";
            }
        }

        else if (choice == 4) {
            int senderNumber, receiverNumber;
            double amount;

            cout << "Enter sender account number: ";
            cin >> senderNumber;

            cout << "Enter receiver account number: ";
            cin >> receiverNumber;

            Account *sender = customer.findAccount(senderNumber);
            Account *receiver = customer.findAccount(receiverNumber);

            if (sender != nullptr && receiver != nullptr) {
                cout << "Enter transfer amount: ";
                cin >> amount;

                sender->transferTo(*receiver, amount);
            }
            else {
                cout << "One or both accounts not found!\n";
            }
        }

        else if (choice == 5) {
            int accountNumber;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account *account = customer.findAccount(accountNumber);

            if (account != nullptr) {
                account->displayAccountInfo();
            }
            else {
                cout << "Account not found!\n";
            }
        }

        else if (choice == 6) {
            int accountNumber;

            cout << "Enter account number: ";
            cin >> accountNumber;

            Account *account = customer.findAccount(accountNumber);

            if (account != nullptr) {
                account->displayTransactions();
            }
            else {
                cout << "Account not found!\n";
            }
        }

        else if (choice == 7) {
            customer.displayCustomerInfo();
        }

        else if (choice == 8) {
            cout << "Thank you for using the Banking System!\n";
        }

        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}