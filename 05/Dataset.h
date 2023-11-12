#pragma once

// 標準ヘッダのインクルード
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

class Dataset
{
public:
   Dataset(char *fileName);
   ~Dataset();
   void setCoef(double *sCoef); // 標準偏回帰係数から偏回帰係数を求める
   void printEquation();        // 重回帰式を表示する

   int dataNum;      // データ数
   int exVarNum;     // 説明変数の個数
   double **exData;  // 説明変数のデータ（オリジナル）
   double *resData;  // 目的変数のデータ（オリジナル）
   double **exSData; // 説明変数のデータ（標準化）
   double *resSData; // 目的変数のデータ（標準化）
   double *coef;     // 偏回帰係数
   double constant;  // 定数項

private:
   double *exAve;    // 説明変数の平均
   double resAve;    // 目的変数の平均
   double *exSd;     // 説明変数の標準偏差
   double resSd;     // 目的変数の標準偏差
};
