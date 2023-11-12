#include "Swarm.h"

/**
 * コンストラクタ
 * @param fileName : データセットのファイル名
 */
// fileName : データセットのファイル名
Swarm::Swarm(char *fileName)
{
    int i, best;
    
    dataset = new Dataset(fileName);
    particle = new Particle* [SWARM_SIZE];
    best = 0;
    for (i = 0; i < SWARM_SIZE; i++) {
        // this : 自分自身のポインタ
        particle[i] = new Particle(this);
        if (particle[best]->value > particle[i]->value) {
            best = i;
        }
    }
    // gBestPosの初期化。gBestPosは最良の粒子の位置を保持する。
    gBestPos = new double [dataset->exVarNum];
    for (i = 0; i < dataset->exVarNum; i++) {
        gBestPos[i] = particle[best]->pos[i];
    }
    gBestValue = particle[best]->value;
}

/**
 * デストラクタ
 * 2次元配列のdeleteの仕方が特殊なので注意。
 */
Swarm::~Swarm()
{
    int i;

    // particleは2次元配列なので、1行ずつdeleteする。
    for (i = 0; i < SWARM_SIZE; i++) {
        delete particle[i];
    }
    // 2次元配列の2次元目をdeleteする。
    delete [] particle;
    delete [] gBestPos;
    delete dataset;
}

/**
 * 粒子を移動し、グローバルベストを更新する
 * @param なし
 * @return なし
 */
void Swarm::move()
{
    int i, best;

    // 全ての粒子を移動する
    best = -1;
    for (i = 0; i < SWARM_SIZE; i++) {
        particle[i]->move();
        if (gBestValue > particle[i]->value) {
            best = i;
        }
    }

    // グローバルベストを更新する
    if (best != -1) {
        for (i = 0; i < dataset->exVarNum; i++) {
            gBestPos[i] = particle[best]->pos[i];
        }
        gBestValue = particle[best]->value;
    }

    return;
}

/**
 * 結果を表示する
 * @param なし
 * @return なし
 */
void Swarm::printResult()
{
    dataset->setCoef(gBestPos);
    dataset->printEquation();

    return;
}







