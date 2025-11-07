#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

// Joodi Al-Asaad
// Aryan Singh

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } 
    else if (pid == 0) {
        execl("./process2", "process2", nullptr);
        std::cerr << "Exec failed!" << std::endl;
        return 1;
    } 
    else {
        int counter = 0;
        while (true) {
            if (counter % 3 == 0)
                std::cout << "Cycle number: " << counter << " – " << counter << " is a multiple of 3" << std::endl;
            else
                std::cout << "Cycle number: " << counter << std::endl;

            counter++;
            sleep(1);
        }

        wait(nullptr);
        std::cout << "Parent: Child process has finished, parent ending too." << std::endl;
    }

    return 0;
}
