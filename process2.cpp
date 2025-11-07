#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>

// Joodi Al-Asaad
// Aryan Singh

struct SharedData {
    int multiple;
    int counter;
};

int main() {
    key_t key = ftok("A2-PART2.cpp", 65);
    int shmid = shmget(key, sizeof(SharedData), 0666);
    if (shmid < 0) {
        std::cerr << "Child: Shared memory access failed!" << std::endl;
        return 1;
    }

    SharedData* data = (SharedData*)shmat(shmid, nullptr, 0);
    if (data == (void*)-1) {
        std::cerr << "Child: Shared memory attach failed!" << std::endl;
        return 1;
    }

    while (data->counter <= 100) {
        std::cout << "Child waiting... counter = " << data->counter << std::endl;
        sleep(1);
    }
    while (data->counter <= 50) {
        std::cout << "Child: counter = " << data->counter << ", multiple = " << data->multiple << std::endl;
        sleep(1);
    }

    std::cout << "Child: counter > 50, detaching shared memory and exiting." << std::endl;
    shmdt(data);

    return 0;
}
