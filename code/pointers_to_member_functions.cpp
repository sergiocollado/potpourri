// this is an example of pointers to function members
// https://coliru.stacked-crooked.com/a/be4b102ed48727d2

/**
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out

hello world!

function chain: 16 15 
funtion pointer: 16

funtion pointer: 36

getcallbacks: 16 36
function chain callbacks 16 36 

unordered array  4 3 2 1 
ordered array  1 2 3 4 

bye
**/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <functional> 
#include <algorithm>

//example of pointers to function members

class Myclass
{
public:
Myclass(int field1, int field2):Field1(field1),Field2(field2){  } 

std::string getField1(){  return std::to_string(Field1); }
std::string getField2(){ return std::to_string(Field2); }

private:
int Field1;
int Field2;

};

class Myreport
{
public:

Myreport(int prio):prio(prio) {}

int prio;
std::function<std::string (void)> mycallback;
void getcallbackfield2(Myclass &myclass)
  {
    mycallback = std::bind(&Myclass::getField2, myclass);
    return;
  }
}; 

bool comparePrios( Myreport &r1, Myreport &r2) //this function is needed for std::sort()
{
    return (r1.prio < r2.prio);
}

int main()
{ 
   std::cout << std::endl <<  "hello world!" << std::endl << std::endl;
   
   Myclass Info1(15,16);

    //definition of a vector for chainning function pointers
   std::vector<std::function<std::string (void)>> functionsChain;
   
   functionsChain.push_back(std::bind(&Myclass::getField2, &Info1) ); 
   functionsChain.push_back(std::bind(&Myclass::getField1, &Info1) ); 

   std::cout << "function chain: ";
   
    for(auto x: functionsChain)
    {   
     std::cout << x() << " "; 
    }
    
   std::cout << std::endl;
   
   //definition of a function pointer to a memeber function for a given object
   std::function<std::string (void)>myfunction = std::bind(&Myclass::getField2, &Info1);
   
   std::cout << "funtion pointer: " << myfunction() << std::endl; 
   
   Myclass Info2(35,36);
   
   std::cout << std::endl; 
   
   //redirect the pointer
   myfunction = std::bind(&Myclass::getField2, &Info2);
   std::cout << "funtion pointer: " << myfunction()  << std::endl; 

   std::cout << std::endl <<  "getcallbacks: ";
   
   Myreport report1(5);
   Myreport report2(7);
   
   report1.getcallbackfield2(Info1);
   report2.getcallbackfield2(Info2);
   
   std::cout << report1.mycallback() << " " <<  report2.mycallback() <<  std::endl;
   
   //definition of a vector for chainning function pointers
   std::vector<std::function<std::string (void)>> functionsChainCallbacks;
   
   functionsChainCallbacks.push_back(report1.mycallback); 
   functionsChainCallbacks.push_back(report2.mycallback ); 
   
    std::cout <<  "function chain callbacks ";
    for(auto x: functionsChainCallbacks)
    {   
     std::cout << x() << " "; 
    }
    
  std::cout << std::endl << std::endl;
    
   std::vector<Myreport> myreportvector;
    
   Myreport r1(54);  // lowest priority
   Myreport r2(43);
   Myreport r3(25);
   Myreport r4(15);   // highest priority 
   
   Myclass I1(21,4);
   Myclass I2(32,3);
   Myclass I3(43,2);
   Myclass I4(54,1);
   
   //get callbacks
   r1.getcallbackfield2(I1);
   r2.getcallbackfield2(I2);
   r3.getcallbackfield2(I3);
   r4.getcallbackfield2(I4);
   
   myreportvector.push_back(r1);
   myreportvector.push_back(r2);
   myreportvector.push_back(r3);
   myreportvector.push_back(r4);
      
    std::cout <<  "unordered array  ";
    for(auto x: myreportvector)
    {   
     std::cout << x.mycallback() << " "; 
    }
    
   std::cout<< std::endl;
   
   std::sort(myreportvector.begin(),myreportvector.end(), comparePrios);
   
    std::cout <<  "ordered array  ";
    for(auto x: myreportvector)
    {   
     std::cout << x.mycallback() << " "; 
    }
    
    
   std::cout << std::endl << std::endl <<  "bye" << std::endl;
}



