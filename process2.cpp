#include <iostream>
#include <unistd.h>

//Joodi Al-Asaad
//Aryan Singh

int main() {
    int counter = 100; 
    while (true) {
        std::cout << "Process 2 (exec child): counter = " << counter << ", PID = " << getpid() << std::endl;
        counter--;      
        sleep(1);       
    }
    return 0;
}
