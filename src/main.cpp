#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){
    std::cout<<"$ ";
    std::string in;
    std::getline(std::cin, in);
    if(in == "exit") break;
    std::cout<<in<<":"<<" "<<"command not found"<< std::endl;
  }

}
