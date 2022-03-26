#include "circulo.h"
float PI=3.1416;

void Circulo::setCx(const double cx){
    this->cx = cx;
}
double Circulo:: getCx(){
   return this->cx;
}
void Circulo::setCy(const double cy){
    this->cy = cy;
}
double Circulo:: getCy(){
   return this->cy;
}
void Circulo::setRaio(const double raio){
    this->raio = raio;
}
double Circulo:: getRaio(){
   return this->raio;
}
void Circulo::setCor(const string cor){
    this->cor = cor;
}
string Circulo:: getCor(){
   return this->cor;
}
void Circulo::Desenhacirculo(double R, double G, double B){

    double x, y;
    int i;
    GLfloat radius;
    int triangleAmount =40;
    GLfloat twicePi = 2.0 * PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R,G, B);
    x=this->cx; y=this->cy; radius =this->raio;
    twicePi = 2.0 * PI;
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
    glVertex2f(
        x + (radius * cos(i *  twicePi / triangleAmount)),
        y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}
    



