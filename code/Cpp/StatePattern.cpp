#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class State
{
    OffHook,
    Connecting,
    Connected,
    OnHold
};

inline ostream& operator<<(ostream& os, const State& s)
{
    switch(s)
    {
    case State::OffHook:
        os << "off the hook";
        break;
    case State::Connecting:
        os << "connecting";
        break;
    case State::Connected:
        os << "connected";
        break;
    case State::OnHold:
        os << "on hold";
        break;
    default:
        break;
    }
    return os;
}


enum class Trigger
{
    CallDialed,
    HungUp,
    CallConnected,
    PlaceOnHold,
    TakenOffHold,
    LeftMessage
};

inline ostream& operator<<(ostream& os, const Trigger& s)
{
    switch(s)
    {
    case Trigger::CallConnected:
        os << "call connected";
        break;
    case Trigger::CallDialed:
        os << "call dialed";
        break;
    case Trigger::HungUp:
        os << "hung up";
        break;
    case Trigger::LeftMessage:
        os << "left message";
        break;
    case Trigger::TakenOffHold:
        os << "taken off hold";
        break;
    case Trigger::PlaceOnHold:
        os << "placed on hold";
        break;
    default:
        break;
    }
    return os;
}




int main()
{
    cout << "State Pattern!" << endl;

    map<State, vector<pair<Trigger, State>>> rules;
    rules[State::OffHook] = {
        {Trigger::CallDialed, State::Connecting}
    };
    rules[State::Connecting] = {
        {Trigger::HungUp, State::OffHook},
        {Trigger::CallConnected, State::Connected}
    };
    rules[State::Connected] = {
        {Trigger::LeftMessage, State::OffHook},
        {Trigger::HungUp, State::OffHook},
        {Trigger::PlaceOnHold, State::OnHold}
    };
    rules[State::OnHold] = {
        {Trigger::TakenOffHold, State::Connected},
        {Trigger::HungUp, State::OffHook}
    };

    //definition of the current state.
    State currentState{ State::OffHook};

    while (true)
    {
       cout << "the current phone state is: " << currentState  << "\n";
       cout << "  ... select the trigger: " << "\n";

       select_trigger:
       int i = 0;
       for (auto item: rules[currentState])
       {
            cout << i++ << "      . " << item.first << "\n";
       }
       int input;
       cin >> input;
       if (input < 0 || (input+1)>rules[currentState].size())
       {
           cout << "incorrect option. please try again.\n";
           goto select_trigger;
       }

       currentState = rules[currentState][input].second;
    }

    cout << "done using the phone.\n";

    getchar();
    return 0;
}
