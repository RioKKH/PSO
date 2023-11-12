#include "Particle.h"

// コンストラクタ
// argSwarm: 属している粒子群
Particle::Particle(Swarm *argSwarm)
{
    int i;

    swarm = argSwarm;
    pos = new double [swarm->dataset->exVarNum];
    velocity = new double [swarm->dataset->exVarNum];
    for (i = 0; i < swarm->dataset->exVarNum; i++) {
        pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
        velocity[i] = COEF_MAX + (COEF_MAX - COEF_MIN) * RAND_01;
    }
    pBestPos = new double [swarm->dataset->exVarNum];
    pBestValue = DBL_MAX;
    evaluate();
}

/**
 * デストラクタ
 */
Particle::~Particle()
{
    delete [] pos;
    delete [] velocity;
    delete [] pBestPos;
}

