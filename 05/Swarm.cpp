#include "Swarm.h"

// コンストラクタ
// fileName: データセットのファイル名
Swarm::Swarm(char *fileName)
{
   int i, best;

   dataset = new Dataset(fileName);
   particle = new Particle* [SWARM_SIZE];
   best = 0;
   for(i = 0; i < SWARM_SIZE; i++) {
      particle[i] = new Particle(this);
      if(particle[best]->value > particle[i]->value) {
         best = i;
      }
   }
   gBestPos = new double [dataset->exVarNum];
   for(i = 0; i < dataset->exVarNum; i++) {
      gBestPos[i] = particle[best]->pos[i];
   }
   gBestValue = particle[best]->value;
}

// デストラクタ
Swarm::~Swarm()
{
   int i;

   for(i = 0; i < SWARM_SIZE; i++) {
      delete particle[i];
   }
   delete [] particle;
   delete [] gBestPos;
   delete dataset;
}

// 粒子を移動し，グローバルベストを更新する
void Swarm::move()
{
   int i, best;

   // すべての粒子を移動する
   best = -1;
   for(i = 0; i < SWARM_SIZE; i++) {
      particle[i]->move();
      if(gBestValue > particle[i]->value) {
         best = i;
      }
   }

   // グローバルベストを更新する
   if(best != -1) {
      for(i = 0; i < dataset->exVarNum; i++) {
         gBestPos[i] = particle[best]->pos[i];
      }
      gBestValue = particle[best]->value;
   }   
}

// 結果を表示する
void Swarm::printResult()
{
   dataset->setCoef(gBestPos);
   dataset->printEquation();
}
