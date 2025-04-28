#include <iostream>
#include <string>
#include <random>

using namespace std;

class bankAccount 
{
private:
    int balance = 0; 
    int AccountNumber=0;

public:
    static int accountCount;

    void setBalance(int b) 
    { 
        balance = b; 
    }

    int getBalance()
    {
        return balance;
    }

    void generateAccountNumber()
    {
		AccountNumber = 23467623 + accountCount;
    }

    int getAccountNumber()
    {
        return AccountNumber;
    }

	bankAccount()
	{
		accountCount++;
	}
};

int bankAccount::accountCount = 0;

class fullName
{
private:
	string firstName;
	string middleName;
	string lastName;

public:

	fullName() : firstName(""), middleName(""), lastName("") {}

	fullName(string fname, string mname, string lname) 
	{
		firstName = fname;
		middleName = mname;
		lastName = lname;
	}
	string getFullName()
	{
		return firstName + " " + middleName + " " + lastName;
	}
};

class bankClient
{
private:
	fullName clientName;
	bankAccount clientAccount;
	string registrationDate;
	string accountType;
	int accountCount = 0;

public:
	bankClient(fullName name, int balance, string date, string type)
	{
		clientName = name;
		clientAccount.setBalance(balance);
		clientAccount.generateAccountNumber();
		registrationDate = date;
		accountType = type;
	}

	void showClientInfo()
	{
		cout << "Client Name: " << clientName.getFullName() << endl;
		cout << "Account Number: " << clientAccount.getAccountNumber() << endl;
		cout << "Balance: $" << clientAccount.getBalance() << endl;
		cout << "Registered on: " << registrationDate << endl;
		cout << "Account Type: " << accountType << endl;
	}
};

int main()
{
	fullName user1("John", "D.", "Smith");
	bankClient client1(user1, 1000, "2023-10-01", "Savings");
	client1.showClientInfo();
	cout << "\n\n";

	fullName user2("Jane", "A.", "Doe");
	bankClient client2(user2, 2000, "2022-03-14", "Current");
	client2.showClientInfo();
	cout << "\n\n";

	fullName user3("Alice", "B.", "Wonderland");
	bankClient client3(user3, 3000, "2025-02-09", "Savings");
	client3.showClientInfo();
	cout << "\n";

	cout << "Total number of accounts created: " << bankAccount::accountCount << endl;

	return 0;
}