#include <bits/stdc++.h>
#include <string>
#include <map>
using namespace std;

/************************************/
void process();
class client_info;
map<string, client_info> customers;
int code = 100;
map<string, bool> exist;
map<string, bool> allow;
class client_info
{
protected:
    string name; char password[5];
    string id;

public:
    long long balance;
    void Enter_info(string n, string ID)
    {
        name = n, id = ID, balance = 0;
        string pass = to_string(1000 + rand() % 9000);
        int j = 0;
        for (int i = 0; i < 4; i++)
            password[i] = pass[i];
        password[4] = '\0';
        cout << "Your code : " << code << endl
             << "Your password : " << password << endl
             << "Please save them to access your account\n";
    }
    void Show_balance(string code)
    {
        cout << "Name : " << name << endl
             << "Balance : " << balance << endl;
    }
    string get_pass()
    {
        return password;
    }
};
class Accounts
{
public:
    void new_account()
    {
        string name;
        string id;
        cout << "Enter your name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your ID : ";
        cin >> id;
        cout << endl;
        customers[to_string(code)].Enter_info(name, id);
        exist[to_string(code)] = true;
        allow[to_string(code)] = true;
        code++;
    }
};
class BS : public Accounts
{
public:
    bool Depsoit_money(long long amount, string code);
    bool Withdraw_money(long long amount, string code);
    bool Transfer_money(long long amount, string code1, string code2);
    bool Show_account_balance(string code);
    bool check_pass(string code, char pass[])
    {
        return customers[code].get_pass() == string(pass) ? 1 : 0;
    }
};
BS NewBank;
bool BS::Depsoit_money(long long amount, string code)
{
    if (amount >= 0)
    {
        customers[code].balance += amount;
        return 1;
    }
    else
        return 0;
}
bool BS::Withdraw_money(long long amount, string code)
{
    if (customers[code].balance >= amount)
    {
        customers[code].balance -= amount;
        return 1;
    }
    else
    {
        cout << "There is not enough money!\n";
        return 0;
    }
}
bool BS::Transfer_money(long long amount, string code1, string code2)
{
    if (exist[code1] && exist[code2])
    {
        if (customers[code1].balance >= amount)
        {
            customers[code1].balance -= amount, customers[code2].balance += amount;
            return 1;
        }
        else
        {
            cout << "There is not enough money!\n";
            return 0;
        }
    }
    else
    {
        cout << "Wrong code!\n";
        return 0;
    }
}
bool BS::Show_account_balance(string code)
{
    if (exist[code])
    {
        cout << "Your balance : " << customers[code].balance;
        return 1;
    }
    else
    {
        cout << "Wrong code!\n";
        return 0;
    }
}
short page1()
{
    short q;
    while (true)
    {
        cout << "==================================\n"
             << "Welcome to NeoBank😊!\n"
             << "Please choose an option.\n"
             << "==================================\n"
             << "1. Log in to your account\n"
             << "2. Creat a new account\n"
             << "3. Exit\n"
             << "==================================\n"
             << "-> ";
        cin >> q;
        if (q > 0 && q < 4)
        {
            break;
        }
    }
    return q;
}
void page2(string code)
{
    int q;
    string c = code;
    cout << "==================================\n"
         << "1. Depsoit money\n"
         << "2. Withdraw money\n"
         << "3. Transfer money\n"
         << "4. Show account balance\n"
         << "5. Log out\n"
         << "==================================\n"
         << "->";
    cin >> q;
    if ((q > 0 && q < 6))
    {

        long long amount;
        if (q == 1)
        {
            cout << "Enter the amount you want to deposit : ", cin >> amount;
            bool b = NewBank.Depsoit_money(amount, code);
            page2(c);
        }
        else if (q == 2)
        {
            cout << "Enter the amount you want to withdraw : ", cin >> amount;
            bool b = NewBank.Withdraw_money(amount, code);
            page2(c);
        }
        else if (q == 3)
        {
            string T_code;
            cout << "Enter the account code you want transfer to : ", cin >> T_code;
            if (exist[T_code])
            {
                cout << "Enter the amount you want to transfer : ", cin >> amount;
                bool b = NewBank.Transfer_money(amount, code, T_code);
                page2(c);
            }
            else
            {
                cout << "Wrong code!\n";
                page2(c);
            }
        }
        else if (q == 4)
        {
            NewBank.Show_account_balance(code);
        }
        process();
    }
}
void process()
{
    int q = page1();
    if (q == 1)
    {
        string code;
        cout << "Enter your code : ", cin >> code, cout << endl;
        if (exist[code])
        {
            if (allow[code])
            {
                int j = 3;
                bool x = false;
                while (j-- && !x)
                {
                    char pass[5];
                    cout << j << " Enter your password : ", cin >> pass, cout << endl;
                    if (NewBank.check_pass(code, pass))
                        x = true;
                    else
                        cout << "Wrong password you have " << j << "try!\n";
                }
                if (x)
                {
                    page2(code);
                }
                else
                {
                    allow[code] = false;
                    cout << "Your account is locked\n";
                    process();
                }
            }
            else
            {
                cout << "Your account is locked\n";
            }
        }
        else
        {
            cout << "Wrong code!\n";
            process();
        }
    }
    if (q == 2)
    {
        NewBank.new_account();
        process();
    }
    if (q == 3)
    {
        cout << "\nThank you for using NeoBank!\n";
        cout << "Goodbye 👋\n";
        exit(0);
    }
}
int main()
{
    process();
}
