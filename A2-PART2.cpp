#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <cstdlib>

// Joodi Al-Asaad
// Aryan Singh

struct SharedData {
    int multiple;
    int counter;
};
#ifndef _SEM_SEMUN_UNDEFINED
#else
union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};
#endif

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
    int shmid = shmget(key, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shmid < 0) {
        std::cerr << "Parent: Shared memory creation failed!" << std::endl;
        return 1;
    }

    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid < 0) {
        std::cerr << "Parent: Semaphore creation failed!" << std::endl;
        return 1;
    }

#ifndef _SEM_SEMUN_UNDEFINED
    semctl(semid, 0, SETVAL, 1);
#else
    union semun sem_union;
    sem_union.val = 1;
    semctl(semid, 0, SETVAL, sem_union);
#endif

    SharedData* data = (SharedData*)shmat(shmid, nullptr, 0);
    if (data == (void*)-1) {
        std::cerr << "Parent: Shared memory attach failed!" << std::endl;
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
        while (true) {
            sem_wait(semid);
            if (data->counter > 150) {
                sem_signal(semid);
                break;
            }

            if (data->counter % data->multiple == 0)
                std::cout << "Parent: " << data->counter << " is a multiple of " << data->multiple << std::endl;
            else
                std::cout << "Parent: counter = " << data->counter << std::endl;

            data->counter++;
            sem_signal(semid);
            sleep(1);
        }

        wait(nullptr);

        std::cout << "Parent: counter > 150, cleaning up shared memory." << std::endl;
        shmdt(data);
        shmctl(shmid, IPC_RMID, nullptr);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
