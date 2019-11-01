#include <iostream>
#include <string>

//Example of default values in constructors.
//compile with: g++ -std=c++11  -Wall -pedantic -o main main.cpp && ./main
//https://coliru.stacked-crooked.com/a/fc5e31b227d40452
/* expected output
Date1: Today -		1 1 1970
DateA: Yesterday(0) -	0 1 1970
Date2: TodayAgain(1) -	1 1 1970
Date2: Tomorrow(2) -	2 1 1970
Date2: Tomorrow.add(1) -3 1 1970
Date2: NexMonth(1,2) - 	1 2 1970
Date3: Never{0} -	0 0 0
*/

class Date1
{   //default constructor used
    public: 
    int day=1, month=1, year=1970; 
};

class Date1A
{
  public:
  Date1A(int d=1, int m=1, int y=1970){day = d; month = m; year = y;}
  int day, month, year;
};

class Date2
{   //default values in the constructor
    public: 
    //constructor with member initilizers
    Date2(int d=1, int m=1, int y=1970): day(d), month(m), year(y){};
    //member function
    void add(int d=0, int m=0, int y=0){day+=d; month+=m; year+=y; }
    int day, month, year; 
};

class Date3
{   //default values in the constructor - curly brackets is more modern syntaxis. 
    public:
    Date3(int d, int m=0, int y=0): day{d}, month{m}, year{y}{};
    int day, month, year; 
};

int main()
{
    Date1 Today; //using the default contructors - it just present the default values. 
    std::cout<< "Date1: Today -\t\t"  << Today.day << " " << Today.month << " " << Today.year << std::endl;
    
    Date1A Yesterday(0); //in this constructor I am skipping the last two parameters of the constructor.
    std::cout<< "DateA: Yesterday(0) -\t"  << Yesterday.day << " " << Yesterday.month << " " << Yesterday.year << std::endl;
    
    Date2 TodayAgain(1); //in this constructor we are skipping the last two parameters
    std::cout<< "Date2: TodayAgain(1) -\t" << TodayAgain.day << " " << TodayAgain.month << " " << TodayAgain.year << std::endl;
       
    Date2 Tomorrow(2); //in this constructor we are skipping the last two parameters
    std::cout<< "Date2: Tomorrow(2) -\t"  << Tomorrow.day << " " << Tomorrow.month << " " << Tomorrow.year << std::endl;
       
    Tomorrow.add(1); //add time function, but skkipped the last two parameters
    std::cout<< "Date2: Tomorrow.add(1)- "  << Tomorrow.day << " " << Tomorrow.month << " " << Tomorrow.year << std::endl;
      
    Date2 NexMonth(1,2); //in this constructor we are skipping the last parameters
    std::cout<< "Date2: NexMonth(1,2) - \t"  << NexMonth.day << " " << NexMonth.month << " " << NexMonth.year << std::endl;
    
    Date3 Never{0}; // - curly brackets in definitions is a more modern cpp syntaxis. 
    std::cout<< "Date3: Never{0} -\t"  << Never.day << " " << Never.month << " " << Never.year << std::endl;

}
