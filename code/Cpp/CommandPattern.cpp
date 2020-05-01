#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //to use for_each
#include <initializer_list>

using namespace std;

struct BankAccount
{
    int balance = 0;
    int overdraft_limit = -500;

    void deposit(int amount)
    {
        balance += amount;
        cout << "deposited: " << amount << " , balance now: " << balance << '\n';
    }

    void withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            cout << "withdrew:  " << amount << ", balance is now: " << balance << '\n';
        }
    }
};

struct iCommand
{
    virtual ~iCommand() = default;
    virtual void call() const = 0;
    virtual void undo() const = 0;
};

struct Command: iCommand
{
    BankAccount& account;
    enum Action{ deposit, withdraw } action;
    int amount;

    Command(BankAccount& account, const Action action, const int amount):
        account(account),action(action), amount(amount) {};

    void call() const override
    {
        switch(action)
        {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
            break;
        default: break;
        }
    }

    void undo() const override
    {
        switch(action)
        {
        case deposit:
            cout << "undo: ";
            account.withdraw(amount);
            break;
        case withdraw:
            cout << "undo: ";
            account.deposit(amount);
            break;
        default: break;
        }
    }
};

struct CommandList: vector<Command>, iCommand
{
    CommandList(const std::initializer_list<value_type>& _Ilist): vector<Command>(_Ilist)
    {
    }

    void call() const override
    {
        for(auto& cmd : *this)
            cmd.call();
    }
    void undo() const override
    {
         for_each(rbegin(), rend(),
             [](const Command& cmd){ cmd.undo(); });
    }
};



int main()
{
    cout << "Command Pattern!" << endl;
    BankAccount myba;
    CommandList commands{
        Command{myba, Command::deposit, 100},
        Command{myba, Command::withdraw, 200}
    };

    cout << endl << "balance: " << myba.balance << endl;

    commands.call();

    cout << endl << "balance: " << myba.balance << endl;

    commands.undo();

    cout << endl << "balance: " << myba.balance << endl;

    getchar();
    return 0;
}
