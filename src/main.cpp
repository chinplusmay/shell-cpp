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
    else if(in.find("type") != std::string::npos){
      std::string tpin = in.substr(5);
      if(tpin == "echo" || tpin == "exit" || tpin == "type"){
        std::cout<<tpin<<" is a shell builtin"<<std::endl;
      }
      else{
        std::cout<<tpin<<": not found"<<std::endl;
      }
    }
    else if(in.find("echo") != std::string::npos){
      std::cout<<in.substr(5)<<"\n";
    }
    else{
      std::cout<<in<<":"<<" "<<"command not found"<< std::endl;
    }
    
  }

}
