#include <iostream>
#include <unistd.h>  //to get pid 

int main() {
    pid_t pid = fork(); 
    
    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
}
