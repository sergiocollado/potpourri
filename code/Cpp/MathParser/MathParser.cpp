#include <iostream>
#include <string>
#include <map>
#include <cctype> //for isalpha, isalnum....

using namespace std;

bool dbugflag = false;
int counter=0;

enum class Kind: char
{
    name, number, end, plus = '+', minus = '-',
    mult = '*', div = '/', print = ';', assign = '=',
    lp= '(', rp = ')'
};

struct Token
{
    Kind kind;
    string string_value;
    double number_value;
};

double error(const string&  s)
{
    static int num_errors=0;
    num_errors++;
    cerr<<"error "<< num_errors<<": "<<s << '\n';
    return 1;
}

class Token_stream
{
private:

    istream* ip; //Pointer to the input stream
    bool owns; //defines if the Token_stream owns the stream
    Token ct{Kind::end}; //current Token.
    map<string,double>table;

    void close()
    {
        if (owns)
            delete ip;
    }

public:

    Token_stream(istream& s):ip{&s}, owns{false} {};
    Token_stream(istream* p):ip{p}, owns{true} {};

    ~Token_stream()
    {
        close();
    };

    Token get(); //read and return next token
    const Token& current(); //get most recently read token.

    void set_input(istream& s)
    {
        close();
        ip=&s;
        owns=false;
    }
    void set_input(istream* p)
    {
        close();
        ip=p;
        owns=true;
    }

};

const Token& Token_stream::current()
{
    return ct;
}

Token Token_stream::get()
{
    char ch=0;

    do
    {
        //ip->get- in the case no character is returned, then we end.
        if(!ip->get(ch))
        {
         return ct= {Kind::end};
        }

    }

    while(ch!='\n' && isspace(ch) ); //keep advancing.

    switch(ch)
    {

    //handle operators:
    case '\n':
    case ';': //end of expression, print-
        return ct= {Kind::end}; //assignation and return
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        if(dbugflag) std::cout << ++counter << "g-ch: " << ch << ";" << "\n" ;
        return ct= {static_cast<Kind>(ch)};
    // is a return and assignment at the same time
    // the static cast is needed to assure that in this
    // case the ch is of type 'kind'

    //handle numbers
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        ip->putback(ch); //put the char back into the stream
        *ip>> ct.number_value;  //read the number
        if(dbugflag) std::cout << ++counter << "g-num: " << ct.number_value << ";" << "\n" ;
        ct.kind=Kind::number;
        return ct;
    default:
        //handle names
        if(isalpha(ch))
        {
            ct.string_value = ch;
            while( ip->get(ch) && isalnum(ch))
                ct.string_value += ch; //append to the string-value
            ip->putback(ch);
            if(dbugflag) std::cout << "g-name: " <<  ct.string_value << ";" << "\n";
            return ct= {Kind::name};
        }
        error("bad token- unrecognized name or operation");
        return ct= {Kind::print};
    }

}

class MathParser
{

public:
    Token_stream ts;
    map<string,double> variables; //so you can define: radius_earth=6700;

    MathParser(istream* p):ts{*p} {};
    MathParser(istream& s):ts{&s} {};

    double prim(bool get);
    double term(bool get);
    double expr(bool get);
    void calculate();
};


/** \brief prim stands for primary element
 *
 *      number
 *      a name
 *      name = expression
 *      - primary (negative primary)
 *      (expression) (use of parenthesis)
 */
double  MathParser::prim(bool get)
{
    if(get)
        ts.get(); //read next token steam. - ts.current is updated

    if(dbugflag) std::cout <<++counter << "prim: " << ts.current().number_value << ";" << "\n" ;

    switch (ts.current().kind) //check the type of ts.current.
    {
    case Kind::number: //floating points
    {
        double v = ts.current().number_value;
        ts.get();
        if(dbugflag) std::cout <<--counter << "return_prim_number: " << ts.current().number_value << ";" << "\n" ;
        return v;
    }
    case Kind::name:
    {
        //this is for assigning values, like: radius = 6378.388;
        //check if the name is in the map of defined names.
        double& v= variables[ts.current().string_value]; //find the corresponding int the Map table.

        //check if the following character is an assignation.

        if(ts.get().kind == Kind::assign)
        {
               v=expr(true); //assignment.
        }
        if(dbugflag) std::cout << --counter <<"return_prim assignation: " << ts.current().number_value << ";" << "\n" ;
        return v;
        //the parser will reach this point so, to retrieve the data
        //double& v = variable["radius"];
        //v = 378.388;
    }
    case Kind::minus:
        if(dbugflag) std::cout <<--counter << "return_prim_negation: " << ts.current().number_value << ";" << "\n" ;
        return -(prim(true));  //
    case Kind::lp:  //left parenthesis
    {
        auto e = expr(true);
        if(ts.current().kind != Kind::rp)
            return error("parenthesis \')\' expected ");
        ts.get();
        if(dbugflag) std::cout <<--counter << "return_prim_left_parenthesis: " << ts.current().number_value << ";" << "\n" ;
        return e;
    }
    default:
        if(dbugflag) std::cout << --counter <<"return_prim default " << ";" << "\n" ;
        return error("primary expected");
    }
}

/** \brief term stand for: term/primary or term * primary or primary. This function handles multiplication and division
 */
double  MathParser::term(bool get)
{
    double on_the_left = prim(get); //gets the element to the right
    //if it is a multiplication or division, then it handles it... otherwise it just return the element.
    if(dbugflag) std::cout << ++counter <<"term: " << ts.current().number_value << ";" << "\n" ;

    for(;;)
    {
        switch(ts.current().kind)
        {
        case Kind::mult:
            on_the_left*=prim(true); //gets another element to the left.
            if(dbugflag) std::cout << --counter << "term_mult: " << on_the_left << ";" << "\n" ;
            break;
        case Kind::div:
            if(auto d= prim(true))   //gets another element to the left.
            {
                on_the_left/= d;
                if(dbugflag) std::cout << --counter << "term_divi: " << on_the_left << ";" << "\n" ;
                break;
            }
            return error("divide by 0");
        default:
            if(dbugflag) std::cout << --counter << "term_default" << ";" << "\n" ;
            return on_the_left;
        }
    }
}

/** \brief expr stands for expression, that is an addition or subtraction.
*
*   expression + term
*   expression - term
*   term
*
*/
double  MathParser::expr(bool get) //this function handles addition and substractions.
{
    double on_the_left = term(get); //gets the element to the right-
     if(dbugflag) std::cout << ++counter << "expr: " << ts.current().number_value << ";" << "\n" ;
    //after the previous command, the ts.current -current token stream - is updated.

    //if it is an addition or a subtraction, it handles it, otherwise it left is
    //unchanged, then it returns that value.
    for(;;)  //for-ever
    {
        switch(ts.current().kind)
        {
        case Kind::plus:
            on_the_left += term(true);
            if(dbugflag) std::cout << --counter << "expr_plus: " << on_the_left << ";" << "\n" ;
            break;
        case Kind::minus:
            on_the_left -= term(true);
            if(dbugflag) std::cout <<--counter << "expr_minus: " << on_the_left << ";" << "\n" ;
            break;
        default:
            if(dbugflag) std::cout << --counter << "expr_default: " << on_the_left << ";" << "\n" ;
            return on_the_left;
        }
    }

}

void  MathParser::calculate()
{

    for(;;)  //'for'-ever ;)
    {
        ts.get();
        if(ts.current().kind==Kind::end) ; //nothing
        if(ts.current().kind == Kind::print)
                continue;
        //ans  = expr(false);
        cout<< "$    " << expr(false) <<'\n'<<'\n';
        counter=0;
    }
}

int main()
{
    cout << "Hello world!  This is my home-made calculator :D" << std::endl;

    MathParser mp(cin);
    mp.calculate();
    return 1;

}
