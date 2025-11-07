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
        for (int i = 0; i < 5; ++i) {
            std::cout << "Child process: iteration " << i 
                      << ", PID = " << getpid() << std::endl;
            sleep(1);
        }
        std::cout << "Child process completed." << std::endl;
    } else {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Parent process: iteration " << i 
                      << ", PID = " << getpid() << std::endl;
            sleep(1);
        }
        wait(nullptr); 
        std::cout << "Parent: child has finished." << std::endl;
    }

    return 0;
}
