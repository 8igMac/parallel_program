#include <iostream>
#include <cstdlib>
#include <pthread.h>

int thread_count;

/*
void* greeting(void* rank)
{
    long my_rank = (long) rank;
    printf("hello from %ld of %ld\n", my_rank, thread_count);

    return NULL;
}
*/

void* greeting(void* )
{
    printf("hello");

    return NULL;

}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "usage: ./PROGRAM NUM_THREAD" << std::endl;
        return -1;
    }

    thread_count = std::strtol(argv[1], NULL, 10);

    pthread_t *thread_handles = new pthread_t[thread_count];

    for(long thread=0; thread<thread_count; thread++)
        pthread_create(
                &thread_handles[thread]
                , NULL
                , greeting
                , NULL
                );

    printf("hello from main thread\n");
    
    // join
    for(long thread=0; thread<thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    // free
    delete [] thread_handles;

    return 0;
}
