#ifndef HARALICK_H
#define HARALICK_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <stdio.h>

#include "globalvar.h"

class Haralick
{
public:
    Haralick();
    ~Haralick();

    void HaralickInit(unsigned short * matrizImg, int altura, int largura, int nc, int ntrds)
    {
        this->matrizImg = matrizImg;
        this->altura = altura;
        this->largura = largura;
        this->Ng = nc;
        this->ntrds = ntrds;
    }


    int * getMc0();
    int * getMc45();
    int * getMc90();
    int * getMc135();
    int * getMatTot();

private:
    int * __restrict__ matrizCoF;
    int Ng;
    int altura, largura;
    int distancia;
    int ntrds;
    unsigned short * matrizImg;
    int * matrizCo0;
    int * matrizCo45;
    int * matrizCo90;
    int * matrizCo135;

    double mediaH(const double * __restrict__ p, int tam);

    void mc0_(unsigned short* mIMG, int i, int j, int* matrizCoTmp);
    void mc45_(unsigned short* mIMG, int i, int j, int* matrizCoTmp);
    void mc90_(unsigned short* mIMG, int i, int j, int* matrizCoTmp);
    void mc135_(unsigned short* mIMG, int i, int j, int* matrizCoTmp);

    double P_x_mais_y(const double * __restrict__ p, const int k, int tam);
    double P_x_menos_y(const double * __restrict__ p, const int k, int tam);


    double *matriz;


public:

    void calcularMatrizCoN(double* matrizCoN, int distancia);

    void atCpu(double *matriz, int tam)
    {
            this->matriz = matriz;
            this->Ng = tam;
    }

    void calcATH(double *, bool *);

    double energia(); // f1
    double contraste(); // f2
    double correlacao(); // f3
    double variancia(); // f4
    double mdi(); // f5
    double mediaSoma(); // f6
    double varianciaSoma(); // f7
    double somaEntropia(); // f8
    double entropia(); // f9
    double varianciaDiferenca(); // f10
    double diferencaEntropia(); // f11
    double medidasCorrelacao1(); // f12
    double medidasCorrelacao2(); // f13

    double hx();
    double hy();
    double px(int);
    double py(int);
    double hxy();
    double hxy1();
    double hxy2();

};

#endif // HARALICK_H
