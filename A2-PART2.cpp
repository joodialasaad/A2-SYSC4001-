#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cstdlib>

// Joodi Al-Asaad
// Aryan Singh

struct SharedData {
    int multiple;
    int counter;
};

int main() {
    key_t key = ftok("A2-PART2.cpp", 65);  
    int shmid = shmget(key, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shmid < 0) {
        std::cerr << "Shared memory creation failed!" << std::endl;
        return 1;
    }

    SharedData* data = (SharedData*)shmat(shmid, nullptr, 0);
    if (data == (void*)-1) {
        std::cerr << "Shared memory attachment failed!" << std::endl;
        return 1;
    }

    data->multiple = 3;  
    data->counter = 0;

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
        while (data->counter <= 50) {
            if (data->counter % data->multiple == 0)
                std::cout << "Parent: " << data->counter << " is a multiple of " 
                          << data->multiple << std::endl;
            else
                std::cout << "Parent: counter = " << data->counter << std::endl;

            data->counter++;
            sleep(1);
        }

        wait(nullptr);
        std::cout << "Parent: counter > 50, cleaning up shared memory." << std::endl;

        shmdt(data);
        shmctl(shmid, IPC_RMID, nullptr);
    }

    return 0;
}
