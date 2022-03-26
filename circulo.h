#ifndef CIRCULO_H_
#define CIRCULO_H_
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>

using namespace std;

class Circulo{
    double cx;
    double cy;
    double raio;
    string cor;
  
public:
    void setCx(const double cx);
    double getCx();
    void setCy(const double cy);
    double getCy();
    void setRaio(const double raio);
    double getRaio();
    void setCor(const string cor);
    string getCor();
    void Desenhacirculo(double R, double G, double B);
    
};

#endif // CIRCULO_H_
