#include <bits/stdc++.h>
#include <string>
#include <set>
#include <map>
using namespace std;

/************************************/

class accounts
{
private:
    char Name[100];
    int ID;
    char Password[7];

public:
    int balance;
    void New_Account(char c[], int id)
    {
        strcpy(Name, c);
        ID = id;
        balance = 0;
        string Pass = "";
        for (int i = 0; i < 6; i++)
        {
            int digit = rand() % 10;
            Password[i] = '0' + digit;
        }
        Password[6] = '\0';
    }
    void Client_info()
    {
        cout << "==================================\n"
             << "Your name : " << Name << endl
             << "Your id : " << ID << endl
             << "Your Password : " << Password << endl;
    }
    bool check_pass(char p[])
    {
        if (strcmp(p, Password) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

map<int, accounts> client;

class operation : public accounts
{
private:
    static int Code;

public:
    static void op(int p)
    {
        Code = p;
        cout << "==================================\n"
             << "1. Depsoit money\n"
             << "2. Withdraw money\n"
             << "3. Transfer money\n"
             << "4. Show account balance\n"
             << "5. Log out\n"
             << "==================================\n"
             << "->";
        int OP = 0;
        while (!(OP > 0 && OP < 6))
        {
            cin >> OP;
            int amount;
            if (OP == 1)
            {
                cout << "Enter the amount you want to deposit : ";
                cin >> amount;
                client[Code].balance += amount;
                cout << "Successful operation\n";
            }
            else if (OP == 2)
            {
                while (true)
                {
                    cout << "Enter the amount you want to withdraw : ";
                    cin >> amount;
                    if (client[Code].balance >= amount)
                    {
                        client[Code].balance -= amount;
                        cout << "Successful operation\n";
                        break;
                    }
                    else
                    {
                        cout << "Not enough money\n"
                             << "Your current balance : " << client[Code].balance << endl;
                    }
                }
            }
            else if (OP == 3)
            {
                cout << "Enter the account code you want transfer to : ";
                int T_code;
                while (true)
                {
                    cin >> T_code;
                    if (client.count(T_code))
                    {
                        while (true)
                        {
                            cout << "Enter the amount you want to transfer : ";
                            cin >> amount;
                            if (client[Code].balance >= amount)
                            {
                                client[Code].balance -= amount;
                                client[T_code].balance += amount;
                                cout << "Successful operation\n";
                                break;
                            }
                            else
                            {
                                cout << "Not enough money\n"
                                     << "Your current balance : " << client[Code].balance << endl;
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << "Not a valid code!\n";
                    }
                }
            }
            else if (OP == 4)
            {
                cout << "Your current balance : " << client[Code].balance << endl;
            }
            else if (OP == 5)
            {
                cout << endl;
            }
            else
            {
                cout << "Please enter a valid number\n";
            }
        }
        cout << "Thank you for using NeoBack\n\n\n";
    }
};
int operation::Code = 0;
int main()
{

    int number_of_clients = 1;
    bool x = true;
    while (x)
    {
        {
            cout << "==================================\n"
                 << "Welcome to NeoBank!\n"
                 << "Please choose an option.\n"
                 << "==================================\n"
                 << "1. Log in to your account\n"
                 << "2. Creat a new account\n"
                 << "3. Close program\n"
                 << "==================================\n"
                 << "-> ";
            int q = 0;
            while (!(q == 1 || q == 2 || q == 3))
            {
                cin >> q;
                if (q == 1)
                {
                    cout << "Please enter your code : ";
                    int code;
                    int tries = 0;
                    while (tries < 3)
                    {
                        cin >> code;
                        tries++;
                        if (client.count(code))
                        {
                            char pass[7];
                            int t = 0;
                            while (t < 3)
                            {
                                t++;
                                cout << "Enter the password : ";
                                cin >> pass;
                                if (client[code].check_pass(pass))
                                {
                                    operation::op(code);
                                    while (true)
                                    {
                                        cout << "Are you want to do any operation ? \n"
                                             << "1. Yes\n"
                                             << "2. No\n"
                                             << "->";
                                        int A;
                                        cin >> A;
                                        if (A == 1)
                                        {
                                            operation::op(code);
                                        }
                                        else if (A == 2)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Please enter a valid number\n";
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    cout << "Wrong password\n"
                                         << "You have" << 3 - t << " tries\n";
                                }
                            }
                            if (t == 3)
                            {
                                cout << "Sorry your account is locked\n";
                            }
                            break;
                        }
                        else
                        {
                            cout << "Not a valid code!\n";
                        }
                    }
                }
                else if (q == 2)
                {
                    char NAME[100];
                    int ID;
                    cout << "Please enter your name : ";
                    cin.ignore();
                    cin.getline(NAME, 100);
                    cout << "Please enter your id : ";
                    cin >> ID;
                    client[number_of_clients].New_Account(NAME, ID);
                    client[number_of_clients].Client_info();
                    cout << "Your code : " << number_of_clients << endl;
                    cout << "Thank you for using NeoBack\n\n"
                         << "==================================\n";
                    while (true)
                    {
                        cout << "Are you want to do any operation ? \n"
                             << "1. Yes\n"
                             << "2. No\n"
                             << "->";
                        int A;
                        cin >> A;
                        if (A == 1)
                        {
                            operation::op(number_of_clients);
                        }
                        else if (A == 2)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Please enter a valid number\n";
                        }
                    }
                    number_of_clients++;
                }
                else if (q == 3)
                {
                    x = false;
                }
                else
                {
                    cout << "Please enter a valid number\n";
                }
            }
        }
    }
    return 0;
}
