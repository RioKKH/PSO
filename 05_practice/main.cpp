// #include <iostream>
#include <cstdio>
#include <string>
#include "Swarm.h"
// #include "Particle.h"

int main()
{
    int t;
    Swarm *swarm;

    srand((unsigned int)time(NULL));

    std::string str = "sampledata.csv";
    char *cstr = &str[0];
    swarm = new Swarm(cstr);
    // const char *cstr = str.c_str();

    for (t = 1; t <= TIME_MAX; t++) {
        swarm->move();
        printf("時刻%d : 最良評価値%f\n", t, swarm->gBestValue);
    }

    swarm->printResult();
    delete swarm;

    return 0;
}
