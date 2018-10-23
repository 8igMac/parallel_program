#include <iostream>
#include <random>
#include <cstdlib>

int main(int argc, char** argv)
{
    // check passed in argument
    if(argc != 3)
    {
        std::cout << "usage: ./PROGRAM NUM_CPU NUM_TOSS" << std::endl;
        return -1;
    }

    // set up random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // start tossing
    long long int number_in_circle = 0;
    long long int number_of_toss = std::strtoll(argv[2], NULL, 10);
    double x, y;
    double distance_sqr;
    for(long long int toss=0; toss<number_of_toss; toss++)
    {
        // assign x and y random double [-1,1]
        x = dis(gen);
        y = dis(gen);

        distance_sqr = x*x + y*y;

        if(distance_sqr < 1)
            number_in_circle++;
    }

    // calculate estimated pi
    double pi_estimate = 
        4*number_in_circle / ((double) number_of_toss);

    // output pi
    std::cout << pi_estimate << std::endl;
}
