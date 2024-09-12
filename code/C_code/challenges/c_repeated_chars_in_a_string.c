#include <iostream>
#include <string>
#include <vector>


void removeRepeatedChars(std::string & text, unsigned int count) {

    unsigned char current_char{};
    unsigned char previous_char{0};
    unsigned int rep= 0;
    
    std::cout << "string length: " << text.length() << '\n';
    
    for (size_t i = 0; i < text.length(); ++i) {
        
        //std::cout << "string length: " << text.length() << "-";
        current_char = text[i];
        //std::cout << "debug: current_char: " << current_char;
        
        if (current_char != previous_char) {
            rep = 1;
        }
        else { 
            ++rep; 
        }
        
        //std::cout << " -rep: " << rep;
        if (rep > count) {
            //std::cout << " - remove: " << text[i];
            text.erase(i, 1);
            --i; // to compensate that the indexes has been moved.
        }
        //std::cout  << '\n';
        
        previous_char = current_char;
    }
}


int main()
{
    
  std::cout << "Orbito, te saluto!\n";
  
  std::cout << "test1: " << "kkklld\n";
  
  std::string test1{"kkklld"};
  
  removeRepeatedChars(test1, 2),
  
  std::cout << test1 << '\n';
  
  
  
  std::cout << "\ntest2: " << "yyzzzxp\n";
  
  std::string test2{"yyzzzxp"};
  
  removeRepeatedChars(test2, 1),
  
  std::cout << test2 << '\n';
  
  
    
  std::cout << "\ntest3: " << "rreerr\n";
  
  std::string test3{"rreerr"};
  
  removeRepeatedChars(test3, 1),
  
  std::cout << test3<< '\n';
  
  
}
