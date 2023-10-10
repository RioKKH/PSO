#pragma once

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <cmath>

class Dataset
{
public:
    Dataset();
    Dataset(char *fileName);
    ~Dataset();

    //- 標準偏回帰係数から予測値を計算する
    void setCoef(double *sCoef);
    //- 重回帰式を表示する
    void printEquation();

    int dataNum;        //- データ数
    int exVarNum;       //- 説明変数の数
    double **exData;    //- 説明変数のデータ(オリジナル)
    double *resData;    //- 目的変数のデータ(オリジナル)
    double **exSData;   //- 説明変数のデータ(標準化)
    double *resSData;   //- 目的変数のデータ(標準化)
    double *coef;       //- 偏回帰係数
    double constant;    //- 定数項


private:
    double *exAve;      //- 説明変数の平均値
    double resAve;      //- 目的変数の平均値
    double *exSd;       //- 説明変数の標準偏差
    double resSd;       //- 目的変数の標準偏差
};



