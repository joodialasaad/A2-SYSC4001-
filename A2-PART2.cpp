#include <iostream>
#include <unistd.h>  //to get pid 

int main() {
    pid_t pid = fork(); 

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
    else if (pid == 0){
        std::cout << "Child process: PID = " << getpid() << ", Parent PID = " << getppid() << std::endl;
    }

    else {
        std::cout << "Parent process: PID = " << getpid() << ", Child PID = " << pid << std::endl;
    }

    return 0; 

}
