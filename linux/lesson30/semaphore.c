#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include<semaphore.h>

pthread_mutex_t mutex;
sem_t psem;
sem_t csem;

struct Node
{
    int num;
    struct Node *next;
};

struct Node *head = NULL;

void *producer(void *arg)
{
    while (1)
    {
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());

        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
        usleep(100);
    }
    return NULL;
}

void *customer(void *arg)
{
    while (1)
    {
        sem_wait(&csem);
        pthread_mutex_lock(&mutex);
        struct Node *tmp = head;
        head = head->next;
        printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
        usleep(100);
    }
    return NULL;
}

int main()
{

    pthread_mutex_init(&mutex, NULL);
    sem_init(&psem,0,8);
    sem_init(&csem,0,0);

    // 创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(ptids[i], NULL);
        pthread_join(ctids[i], NULL);
    }


    pthread_exit(NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&csem);
    sem_destroy(&psem);

    return 0;
}
