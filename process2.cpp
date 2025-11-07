#include <iostream>
#include <unistd.h>

// Joodi Al-Asaad
// Aryan Singh

int main() {
    int counter = 100; 
    while (counter > -500) {
        std::cout << "Process 2 (exec child): counter = " << counter 
                  << ", PID = " << getpid() << std::endl;
        counter--;      
        sleep(1);       
    }

    std::cout << "Process 2 has reached below -500, terminating now." << std::endl;
    return 0;
}
