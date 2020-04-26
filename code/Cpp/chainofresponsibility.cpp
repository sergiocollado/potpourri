#include <iostream>
#include <string>

using namespace std;

class Creature
{
public:
    string name;
    int attack;
    int defense;

    Creature(const string& name, const int attack, const int defense): name(name), attack(attack), defense(defense)
    {
         cout << "Beware of " << name << "!\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
    {
        return os << "name: " << obj.name << ", attack: " << obj.attack << ", defense: "  << obj.defense << '\n';
    }
};

class CreatureModifier
{
    CreatureModifier* next = nullptr;
protected:
    Creature& creature;
public:
    explicit CreatureModifier(Creature& creature): creature(creature)
    {
    }
    virtual ~CreatureModifier() = default;
    void add(CreatureModifier* cm)
    {
        if (next) { next->add(cm); }
         //this will add the modification at the current end of the chain
        else {  next = cm; }
    }
    virtual void handle()
    {
        if(next) {
            cout << "... casted ";
            next->handle();
        }
        //this will propagate the call through the chain.
    }
};

//three buffs:
//1 double attack
//2 def +1 unless power > 2
//3 no buffs applicable.

class DoubleAttackModifier: public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature& creature): CreatureModifier(creature)
    {}
    void handle() override
    {
        creature.attack *= 2;
        cout << "... attack x2!!"  << endl;
        CreatureModifier::handle();//this will allow for other changes in the chain of responsibility.
    }
};

class IncreaseDefModifier: public CreatureModifier
{
public:
    explicit IncreaseDefModifier(Creature& creature): CreatureModifier(creature)
    {
    }
    void handle() override
    {
        if(creature.attack <= 2)
        {
            ++creature.defense;
            cout << "... defense+1!!" << endl;
        }
        CreatureModifier::handle(); //this will allow for other changes in the chain of responsibility.
    }
};

class DebuffModifier: public CreatureModifier
{
    public:
    explicit DebuffModifier(Creature& creature): CreatureModifier(creature)
    {
    }
    void handle() override
    {
        {
            cout << "... DEBUFF!!" << endl;
        }
       // CreatureModifier::handle();
       //As the base methond handle() is not invoqued, the chain of repsonsability is chortcircuit...
       //and none of it will have effect.
    }
};
int main()
{
    cout << "Chain of Responsibility Pattern!\n" << endl;

    Creature monster{"basic monster", 1,1};
    cout << monster << '\n';

    Creature monster2{"buff monster", 1,1};
    CreatureModifier buff{monster2};
    DoubleAttackModifier buffattack{monster2};
    IncreaseDefModifier  buffdefense{monster2};
    buff.add(&buffattack);
    buff.add(&buffdefense);
    buff.handle();
    cout << monster2 << '\n';

    Creature monster3{"other buff monster", 1,1};
    CreatureModifier buff3{monster3};
    DoubleAttackModifier buffattack3{monster3};
    IncreaseDefModifier  buffdefense3{monster3};
    DebuffModifier       debuff3{monster3};
    buff3.add(&debuff3); //notice the order is important
    buff3.add(&buffattack3);
    buff3.add(&buffdefense3);

    buff3.handle();
    cout << monster3 << '\n';

    getchar();
    return 0;
}
