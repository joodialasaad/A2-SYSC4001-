#include <iostream>
#include <unistd.h>  //to get pid 

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
    } else {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Parent process: iteration " << i 
                    << ", PID = " << getpid() << std::endl;
            sleep(1);
        }
    }


    return 0; 

}
