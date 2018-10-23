#include <iostream>
#include <random>
#include <cstdlib>
#include <pthread.h>

void* estimate_pi(void* id);


long long int num_toss;
long long int eve_glb_num_in_circle = 0;
long long int odd_glb_num_in_circle = 0;
long long int work_load;
pthread_mutex_t mutex_eve, mutex_odd;


int main(int argc, char** argv)
{
    // check number of arguments and get arguments
    int num_core;
    long long int num_toss;
    if(argc != 3)
    {
        std::cout << "usage: ./PROGRAM NUM_CPU NUM_TOSS" << std::endl;
        return -1;
    }
    else
    {
        num_core = std::strtoll(argv[1], NULL, 10);
        num_toss = std::strtoll(argv[2], NULL, 10);
    }

    // init mutex
    pthread_mutex_init(&mutex_eve, NULL);
    pthread_mutex_init(&mutex_odd, NULL);

    // calculate workload per thread and 
    // spawn threads to estimate pi
    work_load = num_toss / num_core;
    pthread_t *thread_handler = new pthread_t[num_core-1];
    for(long thread=0; thread<num_core-1; thread++)
        pthread_create(
                &thread_handler[thread]
                , NULL
                , estimate_pi
                , (void*)thread
                );

    // main thread estimate pi
    estimate_pi((void*)(num_toss-1));

    // join
    for(int thread=0; thread<num_core-1; thread++)
        pthread_join(thread_handler[thread], NULL);

    // calculate estimated pi and print out
    double pi_estimate = 
        4*(eve_glb_num_in_circle+odd_glb_num_in_circle) / ((double) num_toss);
    std::cout << pi_estimate << std::endl;

    // free memory and destroy mutex
    delete [] thread_handler;
    pthread_mutex_destroy(&mutex_eve);
    pthread_mutex_destroy(&mutex_odd);
}

void* estimate_pi(void* id)
{
    // set up random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    long long int num_in_circule = 0;
    double x, y, dis_sqr;
    long tid = (long)id;

    for(long long int toss=0; toss<work_load; toss++)
    {
        x = dis(gen);
        y = dis(gen);
        dis_sqr = x*x + y*y;
        if(dis_sqr < 1.0)
            num_in_circule++;
    }

    // add result to global sum
    if(tid%2 == 0)
    {
        pthread_mutex_lock(&mutex_eve);
        eve_glb_num_in_circle += num_in_circule;
        pthread_mutex_unlock(&mutex_eve);
    }
    else
    {
        pthread_mutex_lock(&mutex_odd);
        odd_glb_num_in_circle += num_in_circule;
        pthread_mutex_unlock(&mutex_odd);
    }

    return NULL;
}
