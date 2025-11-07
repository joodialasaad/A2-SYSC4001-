#include <iostream>
#include <unistd.h>   
#include <sys/wait.h> 

int main() {
    pid_t pid = fork(); 

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
    else if (pid == 0) {
        int counter = 0;
        while (true) {
            std::cout << "Process 2 (child): counter = " << counter << ", PID = " << getpid() << std::endl;
            counter++;
            sleep(1); 
        }
    } 
    else {
        int counter = 0;
        while (true) {
            std::cout << "Process 1 (parent): counter = " << counter << ", PID = " << getpid() << std::endl;
            counter++;
            sleep(1);
        }
    }
    return 0;
}
