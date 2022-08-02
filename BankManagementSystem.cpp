/*FACULTY OF COMPUTERS AND ARTIFICIAL INTELLIGENCE, CAIRO UNIVERSITY
Author : Abdelrhman sayed ali
Program Name: Bank Management System.c plus plus*/
#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <windows.h>
using namespace std;

class Data
{
    private:
        double balance;
        string lastName;
        string firstName;
        int numAccount;
        
    public:
        Data(){}
        void setFirstName()
        {
            cout << "\nPlease, Enter the First Name : \n>>>";
            cin >> firstName; 
        }
        void setLastName()
        {
            cout << "\nPlease, Enter the Last Name : \n>>>";
            cin >> lastName;
        }
        void setBalance()
        {
            cout << "\nPlease, Enter your Initial Balance: \n>>>";
            cin >> balance;
        }

        string getFirstName()
        {
            return firstName;
        }
        string getLastName()
        {
            return lastName;
        }
        double getBalance()
        {
            return balance;
        }
        void print()
        {
            cout << "\nYour First Name is : " << firstName;
            cout << "\nYour Last Name is : " << lastName;
            
        }
        friend void saveData();
        friend void loadData();
        friend void GetNumAccount(int inNumAccount, int CBalance);
        friend void GetNumAccountToBalanceEnquiry(int inNumAccount);
        friend void deposit(int inNumAccount, int depositBalance);
        friend void withdrawal(int inNumAccount, int depositBalance);
        friend void showAcounts();
};

int displaymenu();
void OpenAccount();
void FunBalanceEnquiry();
void FunDeposit();
void FunWithdrawal();
void saveData();
void loadData();
int CreateNumberAccount();
void GetNumAccount(int inNumAccount, int CBalance);
void GetNumAccountToBalanceEnquiry(int inNumAccount);
void deposit(int inNumAccount, int depositBalance);
void withdrawal(int inNumAccount, int depositBalance);
void changePassInFile(string StrOldBalance, string StrNewBalance);
void showAcounts();
void setTextColor(int n);

vector<Data>UsersData;
fstream useFile;

string firstName;
string lastName;
double Balance;
int numAccount;
int inNumAccount;
bool Switch = true;

int main()
{
    
    system("cls");
    cout <<"\n\n\t\t\t[---------------Welcome User In BANK MANAGEMENT SYSTEM---------------]\n\n";
    int choice;
    while (true)
    {
        
        choice = displaymenu();
        if (choice == 1)
        {
            OpenAccount();
            //system("cls");
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();
        }  
        else if (choice == 2)
        {
            FunBalanceEnquiry();
            //system("cls");
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();
        }
        else if (choice == 3)
        {
            FunDeposit();
            //system("cls");
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();
        }
        else if (choice == 4)
        {
            FunWithdrawal();
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();

        }
        /*else if (choice == 5)
        {
            //system("cls");
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();
        }*/
        else if (choice == 5)
        {
            system("cls");
            loadData();
            showAcounts();
            //system("cls");
            cout << "\n\n\t\t\t[******* * ******* * ******* * ******* * ******* * *******]";
            displaymenu();
            cout << "\n\n";
                
        }
        else if(choice == 6)
        {
            cout << "\n\n\t\t\t***** Thank you User for use this System *****\n\n";
            return 0;
        }
    }
    
 
}
int displaymenu()
{
    string StrChoice;

    cout << "\n\n                             --->>>Select One Option From This Menu <<<--- \n\n";
    cout << "\n\t1)Open an Account\n\t2)Balance Enquiry\n\t3)Deposit\n\t4)Withdrawal" << 
    "\n\t5)Show All Account\n\t6)Exit\n\n";
    cout << "Please User, Enter the choice you want from this list : \n>>>";
    cin >> StrChoice;
    regex filter("[1-6]?");
    if (regex_match(StrChoice, filter))
    {
        int IntChoice = stoi(StrChoice);
        return IntChoice;
    }
    else
    {
        cout << "           **** Invaild Input ****\n";
        displaymenu();
    }
    
}

void loadData()
{
    useFile.open("Data.txt", ios::in);
    while (!useFile.eof())
    {
        Data NextUser;
        useFile >> NextUser.firstName;
        useFile >> NextUser.lastName;
        useFile >> NextUser.balance;
        useFile >> NextUser.numAccount;
        UsersData.push_back(NextUser); 
    }
    
    
}

void saveData()
{
    Data NextUser;
    useFile.close();
    useFile.open("Data.txt", ios::app);
    useFile << firstName;
    useFile <<  "  ";
    useFile << lastName;
    useFile <<  "  ";
    useFile << Balance;
    useFile <<  "  ";
    useFile << numAccount;
    useFile << endl;
    useFile.close();

}


void OpenAccount()
{
    setTextColor(10);
    loadData();
    Data d;
    d.setFirstName();
    d.setLastName();
    d.setBalance();
    firstName = d.getFirstName();
    lastName = d.getLastName();
    Balance = d.getBalance();
    numAccount = CreateNumberAccount();
    cout <<"\n\t\t***** Congratulations Accout is Created *****";
    cout << "\n\nYour Number Account is : " << numAccount;
    setTextColor(9);
    d.print();
    cout << "\nYour Account Balance is : " << Balance;
    saveData();
    cout << "\n\n";
    setTextColor(7);

}


void FunBalanceEnquiry()
{
    system("cls");
    loadData();
    setTextColor(10);
    cout << "\nPlease User, Enter Your Account Number : \n>>>";
    cin >> inNumAccount;
    setTextColor(9);
    cout << "\n\t\t----- >>>> Your Account Details : "; 
    GetNumAccountToBalanceEnquiry(inNumAccount);
    setTextColor(7);
}

void FunDeposit()
{
    system("cls");
    loadData();
    setTextColor(10);
    int depositBalance;
    cout << "\nPlease User, Enter Your Account Number : \n>>>";
    cin >> inNumAccount;
    cout << "\nEnter Balance to deposit it in your Account : \n>>>";
    cin >> depositBalance;
    deposit(inNumAccount, depositBalance);
    //loadData();
    setTextColor(9);
    cout << "\n\n";
    cout << "\t\tAmount Disposited";
    cout << "\n";
    GetNumAccount(inNumAccount, depositBalance);
    setTextColor(7);
}

void FunWithdrawal()
{
    Switch = false;
    //system("cls");
    loadData();
    setTextColor(10);
    int withdrawalBalance;
    cout << "\nPlease User, Enter Your Account Number : \n>>>";
    cin >> inNumAccount;
    cout << "\nEnter Balance to withdrawal it from your Account : \n>>>";
    cin >> withdrawalBalance;
    withdrawal(inNumAccount, withdrawalBalance);
    //loadData();
    setTextColor(9);
    cout << "\n\n";
    cout << "\t\tAmount Withdrawn";
    cout << "\n";
    GetNumAccount(inNumAccount, withdrawalBalance);
    setTextColor(7);

}

int CreateNumberAccount()
{
    numAccount = 0;
    for(Data user:UsersData)
    {
        numAccount++;
    }
    return numAccount;
}

void GetNumAccount(int inNumAccount, int CBalance)
{
    cout << "\n\nYour Number Account is : " << inNumAccount;
    for (Data user : UsersData)
    {
        if((inNumAccount == user.numAccount) && (Switch))// your choice Deposit Balance
        {
            user.print();
            cout << "\nYour Account Balance is : " << user.balance + CBalance;
            break;
        }
        else if ((inNumAccount == user.numAccount) && (!Switch))// your choice withdrawal Balance
        {
            user.print();
            if (user.balance - CBalance < 0)
            {
                cout << "\n\t\t***** If the amount is withdrawn, you will owe a debt *****";
                cout << "\nYour Account Balance is : " << user.balance - CBalance;
            }
            else
            {
                cout << "\nYour Account Balance is : " << user.balance - CBalance;
            }
            break;
        }
    }
    cout << "\n\n";
}

void GetNumAccountToBalanceEnquiry(int inNumAccount)
{
    cout << "\n\nYour Number Account is : " << inNumAccount;
    for (Data user : UsersData)
    {
        if(inNumAccount == user.numAccount)
        {
            user.print();
            cout << "\nYour Account Balance is : " << user.balance;
            break;
        }
    }

}

void deposit(int inNumAccount, int depositBalance)
{
    int oldBalance;
    int newBalance;
    for (Data user : UsersData)
    {
        if (inNumAccount == user.numAccount)
        {
            oldBalance = user.balance;
            newBalance = user.balance + depositBalance;
            break;
        }
    }
    string StrOldBalance = to_string(oldBalance);
    string  StrNewBalance = to_string(newBalance);
    changePassInFile(StrOldBalance, StrNewBalance);
    
}


void withdrawal(int inNumAccount, int withdrawalBalance)
{
    int oldBalance;
    int newBalance;
    for (Data user : UsersData)
    {
        if (inNumAccount == user.numAccount)
        {
            oldBalance = user.balance;
            newBalance = user.balance - withdrawalBalance;
            break;
        }
    }
    
    

    string StrOldBalance = to_string(oldBalance);
    string  StrNewBalance = to_string(newBalance);
    changePassInFile(StrOldBalance, StrNewBalance);

}


void showAcounts()
{
    int counter = 1;
    for (Data user : UsersData)
    {
        if (counter < UsersData.size())
        {
            cout << "\n\n\t ACCOUNT : " << counter;
            cout << "\n";
            user.print();
            cout << "\nYour Account Balance is : " << user.balance;
            counter++;
            cout << "\n\n\t\t\t---------------------------------------------------------\n";
        }
        
    }
}

void changePassInFile(string StrOldBalance, string StrNewBalance)
{
    char line[100];
    
    vector<string> text;
    int k = 0;
    useFile.close();
    useFile.open("Data.txt");

    while (!useFile.eof()) 
    {
        useFile.getline(line, 100, '\n');
        text.push_back(string(line));
    }
    int x ,z;
    for (int i = 0 ; i< text.size() ; i++)
    {
        if (text[i].find(StrOldBalance,0) < 1000)
        {
            x = text[i].find(StrOldBalance, 0);
            z = i;
        }
    }


    for (int j = x ; j < (x + StrNewBalance.size()) ; j++ )
    {
        text[z][j] = StrNewBalance[k];
        k++;
    }
    useFile.close();
    useFile.open("Data.txt",ios::out);
    
    for (int i = 0; i< text.size() ; i++)
    {
        useFile << text[i];
        useFile << '\n';

    }
    useFile.close();
}

void setTextColor(int n)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, n);

}
