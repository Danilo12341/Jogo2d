#ifndef JOGADOR_H_
#define JOGADOR_H_

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "tiro.h"

using namespace std;

class Jogador{

    double cx;
    double cy;
    double raio;
    double x;
    double y;
    string cor;
    double Thetabraco;
    double Thetaquadril1;
    double Thetajoelho1;
    double Thetaquadril2;
    double Thetajoelho2;
    double gravidade;
    int paradodireita;
    int voltandoperna1 = 0;
    int voltandojoelho1 = 0;
    int voltandoperna2 = 0;
    int voltandojoelho2 = 0;
    int andar =0;
    
    
    public:
        void jogador(){
        x= 0.0; 
        y= 0.0; 
        Thetabraco = 0; 
        Thetaquadril1 = 0;
        Thetajoelho1 = 0;
        Thetaquadril2 = 0;
        Thetajoelho2 = 0;
        paradodireita=0;
        };
        void resetarthetas();           
        void setCx(const double cx);
        double getCx();
        void setCy(const double cy);
        double getCy();
        int getparadodireita();
        void setparadodireita(int valor);
        void setRaio(const double raio);
        double getRaio();
        void setCor(const string cor);
        string getCor();
        void Desenhacirculo(double x, double y, double R, double G, double B);
        void DesenhaRect(double altura,double largura,double R, double G, double B);
        void DesenhaRect2(double altura,double largura,double R, double G, double B);
        void Desenhacabeca(double R, double G, double B);
        void Desenhacorpo(double x, double y,double R, double G, double B);
        void Desenhabraco(double x,double y,double R, double G, double B);
        void Desenhaperna1(double x,double y,double R, double G, double B);
        void Desenhaperna2(double x,double y,double R, double G, double B);
        void DesenhaJogador(double x,double y);
        void MoveEmX(double dx,GLdouble deltaTime);
        void MoveEmY(double dx,GLdouble deltaTime);
        void RodaBracoup(double inc);
        void RodaBracodown(double inc);
        void Rodaquadrail1(double inc);
        void Rodajoelho1(double inc);
        void Rodaquadrail2(double inc);
        void Rodajoelho2(double inc);
        bool Atingido(Tiro* tiro);
        Tiro* Atira();
        void Desenha(){ 
            DesenhaJogador(x,y);
        };

};
#endif // JOGADOR_H_s