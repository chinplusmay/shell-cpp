#include <iostream>
#include <string>
#include <sstream>    // For splitting PATH string
#include <vector>     // For storing PATH directories
#include <cstdlib>    // For getenv() to read environment variables
#include <sys/stat.h> // For stat() to check file existence and permissions
#include <unistd.h>   // For access() to check execute permissions

// Function to search for an executable in PATH
// Returns the full path if found, or empty string if not found
std::string findInPath(const std::string& command) {
    // Get the PATH environment variable
    const char* path_env = std::getenv("PATH");
    
    // If PATH is not set, return empty string
    if (path_env == nullptr) {
        return "";
    }
    
    // Convert PATH to a C++ string for easier manipulation
    std::string path_str(path_env);
    
    // Create a string stream to parse PATH by ':' delimiter
    std::stringstream ss(path_str);
    std::string directory;
    
    // Split PATH by ':' and check each directory
    while (std::getline(ss, directory, ':')) {
        // Construct the full path: directory + "/" + command
        std::string full_path = directory + "/" + command;
        
        // Check if file exists and has execute permissions
        // access() with X_OK checks if the file is executable
        if (access(full_path.c_str(), X_OK) == 0) {
            // File exists and is executable, return the full path
            return full_path;
        }
        // If access() returns -1, either the file doesn't exist
        // or it exists but lacks execute permissions
        // In both cases, we continue to the next directory
    }
    
    // No executable found in any PATH directory
    return "";
}

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
      // Extract the command name after "type "
      // in.substr(5) skips "type " (5 characters including the space)
      std::string tpin = in.substr(5);
      
      // Step 1: Check if the command is a builtin
      if(tpin == "echo" || tpin == "exit" || tpin == "type"){
        // If it's a builtin, report it as such
        std::cout<<tpin<<" is a shell builtin"<<std::endl;
      }
      else{
        // Step 2: Not a builtin, so search in PATH directories
        std::string found_path = findInPath(tpin);
        
        // Check if we found an executable
        if(!found_path.empty()){
          // Executable found, print the full path
          std::cout<<tpin<<" is "<<found_path<<std::endl;
        }
        else{
          // No executable found in PATH
          std::cout<<tpin<<": not found"<<std::endl;
        }
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
