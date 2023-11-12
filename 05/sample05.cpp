#include <cstdio>
#include "Swarm.h"

int main()
{
   int t;
   Swarm *swarm;

   srand((unsigned int)time(NULL));

   swarm = new Swarm("sampledata.csv");
   for(t = 1; t <= TIME_MAX; t++) {
      swarm->move();
      printf("時刻%d：最良評価値%f\n", t, swarm->gBestValue);
   }
   swarm->printResult();
   delete swarm;

   return 0;
}
