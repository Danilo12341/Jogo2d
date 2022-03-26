#ifndef RETANGULO_H_
#define RETANGULO_H_
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "tiro.h"

using namespace std;

class Retangulo{
    double width;
    double height;
    double rx;
    double ry;
    string cor;
  
public:
    void setWidth(const double circRaio);
    double getWidth();
    void setHeight(const double circRaio);
    double getHeight();
    void setRx(const double circRaio);
    double getRx();
    void setRy(const double circRaio);
    double getRy();
    void setCor(const string circRaio);
    string getCor();
    bool Atingido(Tiro* tiro);
    void DesenhaRect(double R, double G, double B);
    
};



#endif // RETANGULO_H_
