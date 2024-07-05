#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CHAIRS 5

pthread_mutex_t mutex;
pthread_cond_t cond_customers;
pthread_cond_t cond_barber;

int waiting_customers = 0;
int barber_sleeping = 0;

void *barber(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (waiting_customers == 0)
        {
            printf("Barber is sleeping...\n");
            barber_sleeping = 1;
            pthread_cond_wait(&cond_customers, &mutex); // Wait for a customer to arrive
        }

        waiting_customers--;
        printf("Barber is cutting hair. Waiting customers: %d\n", waiting_customers);

        pthread_mutex_unlock(&mutex);

        // hair cutting
        sleep(2);

        // Notify the customer that hair cutting is done
        pthread_cond_signal(&cond_barber);
    }
    return NULL;
}

void *customer(void *arg)
{
    pthread_mutex_lock(&mutex);

    if (waiting_customers < NUM_CHAIRS)
    {
        waiting_customers++;
        printf("Customer sits in waiting room. Waiting customers: %d\n", waiting_customers);

        if (barber_sleeping)
        {
            printf("Customer wakes up the barber.\n");
            barber_sleeping = 0;
            pthread_cond_signal(&cond_customers); // Wake up the barber
        }

        // Wait for the barber to cut the hair
        pthread_cond_wait(&cond_barber, &mutex);
        printf("Customer is getting a haircut and leaving.\n");

        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Customer leaves as no chairs are available.\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t barber_thread;
    pthread_t customer_threads[10];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_customers, NULL);
    pthread_cond_init(&cond_barber, NULL);

    pthread_create(&barber_thread, NULL, barber, NULL);

    for (int i = 0; i < 10; i++)
    {
        sleep(rand() % 3);
        pthread_create(&customer_threads[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }

    // Cancel the barber thread (in a real program, you should use a more graceful method)
    pthread_cancel(barber_thread);
    pthread_join(barber_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_customers);
    pthread_cond_destroy(&cond_barber);

    return 0;
}
