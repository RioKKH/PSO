#pragma once

#include "Dataset.h"
#include "Swarm.h"
class Swarm;

// 定数の定義
#define TIME_MAX   1000 // 最終時刻
#define SWARM_SIZE 100  // 粒子群のサイズ
#define INERTIA    0.9  // 慣性係数
#define ACCEL_P    0.8  // 加速係数（パーソナルベスト）
#define ACCEL_G    0.8  // 加速係数（グローバルベスト）
#define COEF_MIN   -1   // 標準偏回帰係数の最小値
#define COEF_MAX   1    // 標準偏回帰係数の最大値

// 0以上1以下の実数乱数
#define RAND_01 ((double)rand() / RAND_MAX)

class Particle
{
public:
   Particle(Swarm *argPS);
   ~Particle();
   void move();       // 粒子を移動する

   Swarm *swarm;      // 属している粒子群
   double *pos;       // 位置
   double *velocity;  // 速度
   double value;      // 評価値

private:
   void evaluate();   // 評価値を算出する

   double *pBestPos;  // パーソナルベストの位置
   double pBestValue; // パーソナルベストの評価値
};
