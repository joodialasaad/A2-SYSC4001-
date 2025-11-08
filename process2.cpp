#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <cstdlib>

// Joodi Al-Asaad
// Aryan Singh

struct SharedData {
    int multiple;
    int counter;
};

void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok("A2-PART2.cpp", 65);
    int shmid = shmget(key, sizeof(SharedData), 0666);
    int semid = semget(key, 1, 0666);
    if (shmid < 0 || semid < 0) {
        std::cerr << "Child: Shared memory or semaphore access failed!" << std::endl;
        return 1;
    }

    SharedData* data = (SharedData*)shmat(shmid, nullptr, 0);
    if (data == (void*)-1) {
        std::cerr << "Child: Shared memory attach failed!" << std::endl;
        return 1;
    }

    while (true) {
        sem_wait(semid);

        if (data->counter > 150) {
            sem_signal(semid);
            break;
        }

        if (data->counter <= 100)
            std::cout << "Child waiting... counter = " << data->counter << std::endl;
        else
            std::cout << "Child: counter = " << data->counter << ", multiple = " << data->multiple << std::endl;

        sem_signal(semid);
        sleep(1);
    }

    std::cout << "Child: counter > 150, detaching shared memory and exiting." << std::endl;
    shmdt(data);

    return 0;
}
