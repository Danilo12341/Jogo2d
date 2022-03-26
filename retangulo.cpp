#include "retangulo.h"


void Retangulo::setWidth(const double width){
    this->width = width;
}
double Retangulo:: getWidth(){
   return this->width;
}
void Retangulo::setHeight(const double height){
    this->height= height;
}
double Retangulo:: getHeight(){
   return this->height;
}
void Retangulo::setRy(const double ry){
    this->ry = ry;
}
double Retangulo:: getRy(){
   return this->ry;
}
void Retangulo::setRx(const double rx){
    this->rx = rx;
}
double Retangulo:: getRx(){
   return this->rx;
}

void Retangulo::setCor(const string cor){
    this->cor = cor;
}
string Retangulo:: getCor(){
   return this->cor;
}

void Retangulo::DesenhaRect(double R, double G, double B){
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(this->rx,this->ry+this->height);
        glVertex2f(this->rx+this->width, this->ry+this->height);
        glVertex2f(this->rx + this->width,this->ry);
        glVertex2f(this->rx,this->ry);
    
    glEnd();
}
bool Retangulo::Atingido(Tiro* tiro){

    GLfloat posx, posy;
    tiro->GetPos(posx, posy);

    if(posx > this->getRx() && posx < this->getRx() + this->getWidth()
    && posy > this->getRy() && posy < this->getRy() + this->getHeight()){
         return 1;
     }else{
         return 0;
     }


}



