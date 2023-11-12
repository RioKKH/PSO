#include "Particle.h"

// コンストラクタ
// argSwarm: 属している粒子群
Particle::Particle(Swarm *argSwarm)
{
   int i;

   swarm = argSwarm;
   pos = new double [swarm->dataset->exVarNum];
   velocity = new double [swarm->dataset->exVarNum];
   for(i = 0; i < swarm->dataset->exVarNum; i++) {
      pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
      velocity[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
   }
   pBestPos = new double [swarm->dataset->exVarNum];
   pBestValue = DBL_MAX;
   evaluate();
}

// デストラクタ
Particle::~Particle()
{
   delete [] pos;
   delete [] velocity;
   delete [] pBestPos;
}

// 粒子を移動する
void Particle::move()
{
   int i;

   for(i = 0; i < swarm->dataset->exVarNum; i++) {
      velocity[i] = INERTIA * velocity[i] 
                  + ACCEL_G * (swarm->gBestPos[i] - pos[i]) * RAND_01
                  + ACCEL_P * (pBestPos[i] - pos[i]) * RAND_01;
      pos[i] += velocity[i];
   }
   evaluate();
}

// 評価値を算出し，パーソナルベストを更新する
void Particle::evaluate()
{
   int i, j;
   double diff;

   // 評価値を算出する
   value = 0.0;
   for(i = 0; i < swarm->dataset->dataNum; i++) {
      diff = swarm->dataset->resSData[i];
      for(j = 0; j < swarm->dataset->exVarNum; j++) {
         diff -= pos[j] * swarm->dataset->exSData[i][j];
      }
      value += pow(diff, 2.0);
   }

   // パーソナルベストを更新する
   if(pBestValue > value) {
      for(i = 0; i < swarm->dataset->exVarNum; i++) {
         pBestPos[i] = pos[i];
      }
      pBestValue = value;
   }
}
