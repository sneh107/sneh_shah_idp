/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file sleeping_barber.c
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jun/5/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define NUM_CHAIRS 5

pthread_mutex_t mutex;
pthread_cond_t cond_customers;
pthread_cond_t cond_barber;

int waiting_customers = 0;
int barber_sleeping = 0;

/**
 * @brief Barber thread function.
 * 
 * This function simulates the barber's behavior of waiting for customers,
 * cutting hair, and then sleeping if no customers are present.
 * 
 * @param arg Pointer to the arguments for the barber (unused).
 * @return void* Returns NULL on completion.
 */

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

/**
 * @brief Customer thread function.
 * 
 * This function simulates the customer's behavior of arriving at the barbershop,
 * waiting for a haircut if a chair is available, or leaving if no chairs are available.
 * 
 * @param arg Pointer to the arguments for the customer (unused).
 * @return void* Returns NULL on completion.
 */

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

/**
 * @brief Main function to initialize resources and create threads.
 * 
 * The function initializes mutexes and condition variables, creates the barber thread,
 * and simulates the arrival of customers by creating customer threads.
 * 
 * @return int Returns 0 on successful completion.
 */

int main()
{
    pthread_t barber_thread;
    pthread_t customer_threads[10];

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("Mutex init has failed");
        return -1;
    }

    if (pthread_cond_init(&cond_customers, NULL) != 0)
    {
        perror("Condition variable init for customers has failed");
        return -1;
    }

    if (pthread_cond_init(&cond_barber, NULL) != 0)
    {
        perror("Condition variable init for barber has failed");
        return -1;
    }

    if (pthread_create(&barber_thread, NULL, barber, NULL) != 0)
    {
        perror("Error creating barber thread");
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        sleep(rand() % 3);
        if (pthread_create(&customer_threads[i], NULL, customer, NULL) != 0)
        {
            perror("Error creating customer thread");
            return -1;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(customer_threads[i], NULL) != 0)
        {
            perror("Error joining customer thread");
            return -1;
        }
    }

    // Cancel the barber thread (in a real program, you should use a more graceful method)
    if (pthread_cancel(barber_thread) != 0)
    {
        perror("Error canceling barber thread");
        return -1;
    }

    if (pthread_join(barber_thread, NULL) != 0)
    {
        perror("Error joining barber thread");
        return -1;
    }

    if (pthread_mutex_destroy(&mutex) != 0)
    {
        perror("Error destroying mutex");
        return -1;
    }

    if (pthread_cond_destroy(&cond_customers) != 0)
    {
        perror("Error destroying customers condition variable");
        return -1;
    }

    if (pthread_cond_destroy(&cond_barber) != 0)
    {
        perror("Error destroying barber condition variable");
        return -1;
    }

    return 0;
}

