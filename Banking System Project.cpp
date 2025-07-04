#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Transaction {
public:
	string type;
	double amount;
	string date;
	
	Transaction(string t, double a){
		type = t;
		amount = a;
		
		time_t now = time(0);
		date = ctime(&now);
		date.pop_back();
	}
	
	void display() {
		cout << type << " of Rs. " << amount << " on " << date <<endl;
	}
};

class Account {
private:
	int accountNumber;
	double balance;
	vector<Transaction> history;
	
public:
	Account(int accNo) {
		accountNumber = accNo;
		balance = 0.0;
		}
		
		void deposit(double amount) {
			balance += amount;
			history.push_back(Transaction("Deposit", amount));
			cout << "Deposit successful.\n";
		}
		
		bool withdraw(double amount) {
			if (balance >= amount) {
				balance -= amount;
				history.push_back(Transaction("Withdrawal", amount));
				cout << "Withdrawal successful.\n";
				return true;
			}
			else {
				cout << "Insufficient balance!\n";
				return false;
			}
		}
		
		bool transfer(Account& to, double amount){
			if (withdraw(amount)){
			to.deposit(amount);
			history.push_back(Transaction("Transfer to Acc #" + to.getAccountNumberStr(), amount));
			return true;
		}
		return false;
	}
	
	void showBalance() {
		cout << "Account #" << accountNumber << " | Balance: Rs " << balance << endl;
		}
		
		void showTransactions() {
			cout << "Transaction History for Account #" << accountNumber << ":\n";
			for (Transaction& t : history) {
				t.display();
			}
		}
		
		int getAccountNumber() {
			return accountNumber;
		}
		
		string getAccountNumberStr() {
			return to_string(accountNumber);
		}
	};
	
	class Customer {
	public: 
		string name;
		int customerID;
		Account* account;
		
		Customer(string n, int id, int accNo) {
			name = n;
			customerID = id;
			account = new Account(accNo);
		}
		
		void displayInfo() {
			cout << "Customer ID: " << customerID << " | Name: " << name <<endl;
			account->showBalance();
		}
		
		~Customer() {
			delete account;
	}	
};

int main() {
	vector<Customer*> customers;
	int choice, custID = 1000, accNo = 10001;
	
	while (true) {
		cout << "\n--- Banking System Menu ---\n";
		cout << "1. Create Customer & Account\n";
		cout << "2. Deposit Money\n";
		cout << "3. Withdraw Money\n";
		cout << "4. Transfer Funds\n";
		cout << "5. Show Account Info\n";
		cout << "6. View Transactions\n";
		cout << "7. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;
		
		if (choice == 1) {
			string name;
			cout << "Enter Customer Name: ";
			cin >> name;
			Customer* cust = new Customer(name, custID++, accNo++);
			customers.push_back(cust);
		cout << "Customer created with ID: " <<cust->customerID
				<< " and Account #: " <<cust->account->getAccountNumber() <<endl;
		}
		else if (choice >= 2 && choice <= 6) {
			int acc;
			cout << "Enter Account Number: ";
			cin >> acc;
			Account* selectedAcc = nullptr;
			
			for (Customer* c : customers) {
				if(c->account->getAccountNumber() == acc) {
				selectedAcc = c->account;
				break;
				}
			}
			
			if (!selectedAcc) {
				cout << "Account not found!\n";
				continue;
			}
			
			if (choice == 2) {
			 double amt;
			 cout << "Enter amount to deposit: ";
			 cin >> amt;
			 selectedAcc->deposit(amt);
			}
			else if (choice == 3) {
				double amt;
				cout << "Enter amount to withdraw: ";
				cin >> amt;
				selectedAcc->withdraw(amt);
			}
			else if (choice == 4) {
				int toAcc;
				double amt;
				cout << "Enter receiver account number: ";
				cin >> toAcc;
				cout << "Enter amount to transfer: ";
				cin >> amt;
				
				Account* receiver = nullptr;
				for (Customer* c : customers) {
					if (c->account->getAccountNumber() == toAcc) {
					receiver = c->account;
					break;
				}
			}
			
			if (receiver) {
				selectedAcc->transfer(*receiver, amt);
				}
				else {
					cout << "Receiver account not found!\n";
				}
			}
				else if (choice == 5) {
					selectedAcc->showBalance();
				}
				else if (choice == 6) {
					selectedAcc->showTransactions();
				}
			}
		else if (choice == 7) {
				break;
			}
			else {
				cout << "Invalid option.\n";
			}
		}
					
	for (Customer* c : customers) {
		delete c;
	}
	
	return 0;

}