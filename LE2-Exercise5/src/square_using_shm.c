#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define SHM_SIZE sizeof(struct shared_memory)
#define MY_SHM_ID 1234

struct shared_memory
{
    int number;
    int square;
    int flag; // 0: parent reads, 1: child writes
};

int CalculateSquare(int n)
{
    int square = 0;
    for (int i = 0; i < n; ++i)
    {
        square += n;
    }
    return square;
}

int main()
{
    int shmid;
    struct shared_memory *shm;

    shmid = shmget(MY_SHM_ID, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (shm == (struct shared_memory *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    shm->flag = 0;
    shm->number = 0;
    shm->square = 0;

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        srand(time(NULL));
        for (int i = 1; i <= 1000; ++i)
        {
            int square = CalculateSquare(i);
            int sleep_time = (rand() % 3) + 1; // Sleep for 1 to 3 seconds
            sleep(sleep_time);
            // usleep(rand() % 1000000);

            shm->number = i;
            shm->square = square;
            shm->flag = 1;

            while (shm->flag == 1)
            {
                usleep(100);
            }
        }

        if (shmdt(shm) == -1)
        {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        for (int i = 1; i <= 1000; ++i)
        {
            while (shm->flag == 0)
            {
                usleep(100);
            }

            printf("Square of %d is %d\n", shm->number, shm->square);

            shm->flag = 0;
        }

        if (shmdt(shm) == -1)
        {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }

        wait(NULL);
    }

    return 0;
}