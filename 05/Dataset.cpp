#include <cstdio>
#include "Dataset.h"

// コンストラクタ
// fileName: データセットのファイル名
Dataset::Dataset(char *fileName)
{
   int i, j, columnNum;
   char line[1024];
   FILE *fp;
   char *pos1;
   char *pos2;

   // 説明変数の数とデータ数の取得
   if((fp = fopen(fileName, "r")) == NULL) {
      printf("%sが開けません．\n", fileName);
      exit(1);
   }
   exVarNum = -1;
   dataNum = 0;
   while(fgets(line, 1024, fp)) {
      if(strcmp(line, "\n")) {
         columnNum = 1;
         pos1 = line;
         do {
            pos2 = strchr(pos1, ',');
            if(pos2) {
               if(pos2 == pos1) {
                  printf("空のデータが含まれています．");
                  exit(1);
               }
               columnNum++;
               pos1 = pos2 + 1;
            }
         } while(pos2);
         if(*pos1 == '\n') {
            printf("空のデータが含まれています．");
            exit(1);
         }
         if(exVarNum == -1) {
            exVarNum = columnNum - 1;
         } else if(exVarNum != columnNum - 1) {
            printf("列数の異なるレコードがあります．");
            exit(1);
         }
         dataNum++;
      }
   }
   fclose(fp);

   // 領域を確保し初期化する
   exData = new double* [dataNum];
   exSData = new double* [dataNum];
   resData = new double [dataNum];
   resSData = new double [dataNum];
   exAve = new double [exVarNum];
   exSd = new double [exVarNum];
   coef = new double [exVarNum];
   for(j = 0; j < exVarNum; j++) {
      exAve[j] = 0.0;
      exSd[j] = 0.0;
   }
   resAve = 0.0;
   resSd = 0.0;

   // データを読込む
   if((fp = fopen(fileName, "r")) == NULL) {
      printf("%sが開けません．\n", fileName);
      exit(1);
   }
   for(i = 0; i < dataNum; i++) {
      exData[i] = new double [exVarNum];
      exSData[i] = new double [exVarNum];
      fgets(line, 1024, fp);
      pos1 = line;
      for(j = 0; j < exVarNum; j++) {
         pos2 = strchr(pos1, ',');
         *pos2 = '\0';
         exData[i][j] = atof(pos1);
         exAve[j] += exData[i][j];
         pos1 = pos2 + 1;
      }
      pos2 = strchr(pos1, '\n');
      *pos2 = '\0';
      resData[i] = atof(pos1);
      resAve += resData[i];
   }
   fclose(fp);

   // 平均と標準偏差を算出する
   for(j = 0; j < exVarNum; j++) {
      exAve[j] /= dataNum;
      for(i = 0; i < dataNum; i++) {
         exSd[j] += pow(exData[i][j] - exAve[j], 2.0);
      }
      exSd[j] = sqrt(exSd[j] / dataNum);
   }
   resAve /= dataNum;
   for(i = 0; i < dataNum; i++) {
      resSd += pow(resData[i] - resAve, 2.0);
   }
   resSd = sqrt(resSd / dataNum);

   // 標準化データに変換する
   for(i = 0; i < dataNum; i++) {
      for(j = 0; j < exVarNum; j++) {
         exSData[i][j] = (exData[i][j] - exAve[j]) / exSd[j];
      }
      resSData[i] = (resData[i] - resAve) / resSd;
   }
}

// デストラクタ
Dataset::~Dataset()
{
   int i;

   for(i = 0; i < dataNum; i++) {
      delete [] exData[i];
      delete [] exSData[i];
   }
   delete [] exData;
   delete [] exSData;
   delete [] resData;
   delete [] resSData;
   delete [] exAve;
   delete [] exSd;
   delete [] coef;
}

// 標準偏回帰係数から偏回帰係数と定数項を算出する
// sCoef : 標準偏回帰係数の配列
void Dataset::setCoef(double *sCoef)
{
   int i;

   constant = resAve;
   for(i = 0; i < exVarNum; i++) {
      coef[i] = resSd / exSd[i] * sCoef[i];
      constant -= coef[i] * exAve[i];
   }
}

// 重回帰式を表示する
void Dataset::printEquation()
{
   int i;

   printf("重回帰式：y = ");
   for(i = 0; i < exVarNum; i++) {
      printf("%.3f x%d + ", coef[i], i + 1);
   }
   printf("%.3f\n", constant);
}
