// g++ -std=c++20 -O2 -Wall -pedantic -lpthread  main.cpp && ./a.out

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <iostream>
#include <iomanip>

int main()
{
    const auto p0 = std::chrono::time_point<std::chrono::system_clock>{};
    const auto p1 = std::chrono::system_clock::now();  // now
    const auto p2 = p1 - std::chrono::hours(24);       // yesteday
        
    const unsigned int IntervalinMilliseconds = 125;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(IntervalinMilliseconds) );
    const auto p3 = std::chrono::system_clock::now();  // now + interval in milliseconds aprox.
    
    std::cout << " ----- " << '\n';   
    
    std::time_t epoch_time = std::chrono::system_clock::to_time_t(p0);
    std::cout << "epoch: " << std::ctime(&epoch_time);
    
    std::time_t today_time = std::chrono::system_clock::to_time_t(p1);
    std::cout << "today: " << std::ctime(&today_time);
 
 
 
    std::cout << "hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p1.time_since_epoch()).count() 
              << '\n';
    std::cout << "yesterday, hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p2.time_since_epoch()).count() 
              << '\n';
            
    std::cout << " ----- " << '\n';      
               
    std::cout << "hours:  "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p1.time_since_epoch()).count() % 24
              << '\n';
              

    std::cout << "minutes:  "
              << std::chrono::duration_cast<std::chrono::minutes>(
                   p1.time_since_epoch()).count() % 60
              << '\n';    
              
    std::cout << "seconds:  "
              << std::chrono::duration_cast<std::chrono::seconds>(
                   p1.time_since_epoch()).count() % 60
              << '\n';    
              
    std::cout << "milliseconds:  " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                   p1.time_since_epoch()).count() % 1000
              << '\n'; 
 
    std::cout << "milliseconds2: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                   p3.time_since_epoch()).count() % 1000
              << '\n'; 
    
    std::cout << "milliseconds difference: " << std::chrono::duration_cast<std::chrono::milliseconds>(
                   p3.time_since_epoch() - p1.time_since_epoch() ).count() << '\n';
     
     
    std::cout << " ----- " << '\n';  
        
    std::cout << "Current time with milliseconds\n";
    
    std::ios state(nullptr);
    state.copyfmt(std::cout); // save current formatting
     
    std::cout  << std::setw(2)
               << std::setfill('0') 
               << std::chrono::duration_cast<std::chrono::hours>(p1.time_since_epoch()).count() % 24 
               << ":"
               << std::setw(2)
               << std::setfill('0') 
               <<  std::chrono::duration_cast<std::chrono::minutes>(p1.time_since_epoch()).count() % 60
               << ":"
               << std::setw(2)
               << std::setfill('0') 
               << std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() % 60
               << "."
               << std::setw(3) 
               << std::setfill('0') 
               << std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count() % 1000
               << '\n';
    
    std::cout.copyfmt(state); // restore previous formatting   
}
