//reference: https://www.youtube.com/watch?v=4GU2YNsHrwg&t=4s
//reference: https://youtu.be/RVvVQpIy6zc

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //to use remove and remove_if
#include <mutex>

//in the observer pattern special care must be used when working
//with multithreaded systems, and whatch out for reentrancy issues.

using namespace std;

static mutex mtx;
struct Person;
struct PersonListener
{
    virtual ~PersonListener() = default;
    virtual void PersonChanged(Person& p,
                               const string& property_name,
                               const int new_value) = 0;
};
struct Person{
    Person(const int age):age(age)
    {
    }
    virtual int GetAge() const
    {
        return age;
    }
    virtual int SetAge(const int age)
    {
        if(this->age == age) return 0;
        this->age = age;
        notify("age",this->age);
    }
    void subscribe(PersonListener* pl)
    {
        lock_guard<mutex> guard{mtx};
        if (find(begin(listeners), end(listeners), pl) == end(listeners))
        { //this is to prevent double subscription.
              listeners.push_back(pl);
        }
    }
    void unsubscribe(PersonListener* pl)
    {
        lock_guard<mutex> guard{mtx};
        for(auto it = listeners.begin(); it!= listeners.end(); ++it)
        {
            if(*it == pl)
            {
                *it = nullptr;
            }
        }
    }
    void notify(const string& propierty_name, const int new_value)
    {
        lock_guard<mutex> guard{mtx};
        for(const auto listener: listeners)
        {
            if(listener)  //to handle the case listeners == nullptr
            {
                 listener->PersonChanged(*this, propierty_name, new_value);
            }
        }
        //next is to erase unsubscribed elements.
        listeners.erase(
            remove(listeners.begin(), listeners.end(), nullptr),listeners.end());
    }
private:
    int age;
    vector<PersonListener*> listeners; //WATCH OUT! because this vector is not thread safe.!
};

struct ConsoleListener: PersonListener
{
    void PersonChanged(Person& p, const string& property_name, const int new_value)
    {
        cout << "person's " << property_name << " has changed to: ";
        if (property_name == "age")
        {
            cout << static_cast<int>(new_value);
        }
        cout << "\n";
    }
};
int main()
{
    cout << "Observer Pattern!" << endl;

    Person p{0};
    ConsoleListener cl;
    p.subscribe(&cl);
    p.SetAge(p.GetAge()+1); //1
    p.SetAge(p.GetAge()+1); //2
    p.SetAge(p.GetAge()+1); //3
    p.SetAge(p.GetAge()+1); //4
    p.SetAge(p.GetAge()+1); //5

    p.unsubscribe(&cl);

    p.SetAge(p.GetAge()+1); //6
    p.SetAge(p.GetAge()+1); //7
    p.SetAge(p.GetAge()+1); //8

    getchar();
    return 0;
}
