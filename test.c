#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *myturn(void *arg) {
    
    {
        sleep(1);
        printf("My Turn!\n");
    }
}

void yourturn() {
    while(1)
    {
        sleep(1);
        printf("Your Turn!\n");
    }
}

int main()
{
    pthread_t newthread;
    
    pthread_create(&newthread, NULL, myturn, NULL);
    //myturn();
    yourturn();
}