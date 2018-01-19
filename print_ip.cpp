#include "print_ip.hpp"

#include <vector>
#include <list>
#include <string>
#include <tuple>

int main()
{
    print_ip(char(-1));
    print_ip(short(0), std::cout);
    print_ip(int(2130706433), std::cout);
    print_ip(long(8875824491850138409), std::cout);
    auto ss =std::string("String print as is");
    print_ip(ss);  
    
    std::vector<uint8_t> a;
    a.push_back('1');
    a.push_back('2');
    a.push_back('3');
    a.push_back('4');
    print_ip(a);
      
    std::list<std::string> l;
    l.push_back("first");
    l.push_back("second");
    l.push_back("third");
    l.push_back("fourth");
    print_ip(l);
      
    auto t=std::make_tuple(short(11),short(22),short(33),short(44));
    print_ip(t);
}
