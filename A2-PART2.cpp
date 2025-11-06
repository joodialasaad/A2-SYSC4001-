#include <iostream>
#include <unistd.h>  //to get pid 

int main() {
    pid_t pid = fork(); 
    std::cout << "Process started. PID = " << getpid() << std::endl;
    return 0;
}
