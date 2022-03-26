#include "jogador.h"
float PI2=3.1416;


void Jogador::setCx(const double cx){
    this->cx = cx;
}
double Jogador:: getCx(){
   return this->cx;
}
void Jogador::setCy(const double cy){
    this->cy = cy;
}
double Jogador:: getCy(){
   return this->cy;
}
void Jogador::setRaio(const double raio){
    this->raio = raio;
}
double Jogador::getRaio(){
   return this->raio;
}
void Jogador::setCor(const string cor){
    this->cor = cor;
}
string Jogador:: getCor(){
   return this->cor;
}

int  Jogador::getparadodireita(){
    return this->paradodireita;
}
        
void  Jogador::setparadodireita(int valor){
      this->paradodireita=valor;
}

void Jogador::MoveEmX(double dx,GLdouble deltaTime)
{
   this->cx += dx*deltaTime;
    
}
void Jogador::MoveEmY(double dy,GLdouble deltaTime)
{
   this->cy += dy*deltaTime;
    
}
void Jogador::RodaBracoup(double inc){
 
         
    if (Thetabraco > -45){
        Thetabraco += inc;
        
    }
     
}
void Jogador::RodaBracodown(double inc){
 
    if (Thetabraco < 45){
        Thetabraco += inc;
        
    }    
}
void Jogador::Rodaquadrail1 (double inc)
{
    if(Thetaquadril1 > -46 && voltandoperna1 == 0 && andar == 0){
        
        Thetaquadril1+= inc;
    }else{
      if(andar==0){
        voltandoperna1 =1;
        if (voltandoperna1==1)
        Thetaquadril1-= inc;
        if(Thetaquadril1 == 0){
            voltandoperna1=0;
            andar =1;
        }
      }

    }    
    
}

void Jogador::Rodaquadrail2 (double inc)
{
    if(Thetaquadril2 > -46 && voltandoperna2 == 0 && andar == 1 ){
        
        Thetaquadril2+= inc;
    }else{
      if(andar==1){
        voltandoperna2 =1;
        if (voltandoperna2==1)
        Thetaquadril2-= inc;
        if(Thetaquadril2 == 0){
            voltandoperna2=0;
            andar =0;
        }
      }

    }    
    
}
void Jogador::Rodajoelho1 (double inc)
{   
    if(Thetajoelho1 < 60 && voltandojoelho1 == 0){
      Thetajoelho1 += inc;
      
    }else{
        voltandojoelho1=1;
        if(voltandojoelho1==1){
           Thetajoelho1 -= inc;
        }
        if(Thetajoelho1 ==0){
            voltandojoelho1=0;
        }
    }
    
    
}
void Jogador::Rodajoelho2 (double inc)
{   
    if(Thetajoelho2 < 60 && voltandojoelho2 == 0){
      Thetajoelho2 += inc;
      
      
    }else{
        voltandojoelho2=1;
        if(voltandojoelho2==1){
           Thetajoelho2 -= inc;
        }
        if(Thetajoelho2 ==0){
            voltandojoelho2=0;
        }
    }
    
    
}

void Jogador::Desenhacirculo(double x, double y,double R, double G, double B){
    int i;
    GLfloat radius;
    int triangleAmount =40;
    GLfloat twicePi = 2.0 * PI2;
    glBegin(GL_TRIANGLE_FAN);
    if(this->cor=="green"){
        glColor3ub(0,255, 0);
        radius=this->raio*0.3;
        twicePi = 2.0 * PI2;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
        }
        glEnd();
    }else{

        glColor3ub(255,0,B);
        radius=this->raio*0.3;
        twicePi = 2.0 * PI2;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
        }
        glEnd();

    }
}

void Jogador::DesenhaRect(double altura,double largura,double R, double G, double B){
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(largura,0);
        glVertex2f(largura,altura);
        glVertex2f(0,altura);
    glEnd();
}

void Jogador::DesenhaRect2(double altura,double largura,double R, double G, double B){
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(-largura/2,0);
        glVertex2f(largura/2,0);
        glVertex2f(largura/2,altura);
        glVertex2f(-largura/2,altura);
    glEnd();
}

void Jogador::Desenhacorpo(double x,double y,double R, double G, double B){
    
    glPushMatrix();
    glTranslatef(x-0.3*this->raio,y+0.3*this->raio,0);
    DesenhaRect(0.7*this->raio,0.6*this->raio,R,G,B);
    glPopMatrix();

}
void Jogador::Desenhabraco(double x,double y,double R, double G, double B){
    if(this->cor == "green"){
        glPushMatrix();
        glTranslatef(x,y+0.5*this->raio,0);
        glRotatef(Thetabraco, 0, 0, 1);
        DesenhaRect(0.2*this->raio,0.6*this->raio,R,G,B);  
        glPopMatrix();   
    }
    if(this->cor == "red"){
        glPushMatrix();
        glTranslatef(x-0.6*this->raio,y+0.5*this->raio,0);
        glRotatef(Thetabraco, 0, 0, 1);
        DesenhaRect(0.2*this->raio,0.6*this->raio,R,G,B);  
        glPopMatrix();   
    }
}
void Jogador::Desenhaperna1(double x,double y,double R, double G, double B){
     glPushMatrix();
    glTranslatef(x-this->raio*0.3/2,y+this->raio,0);
    glRotatef(Thetaquadril1, 0, 0, 1);
    DesenhaRect2(0.35*this->raio,this->raio*0.3/2,R,G,B);
    glTranslatef(0,0.35*this->raio,0);
    glRotatef(Thetajoelho1, 0, 0, 1);
    DesenhaRect2(0.35*this->raio,this->raio*0.3/2,R,G,B);
    glPopMatrix();
}
void Jogador::Desenhaperna2(double x,double y,double R, double G, double B){
    glPushMatrix();
    glTranslatef(x+this->raio*0.3/2,y+this->raio,0);
    glRotatef(Thetaquadril2, 0, 0, 1);
    DesenhaRect2(0.35*this->raio,this->raio*0.3/2,R,G,B);
    glTranslatef(0,0.35*this->raio,0);
    glRotatef(Thetajoelho2, 0, 0, 1);
    DesenhaRect2(0.35*this->raio,this->raio*0.3/2,R,G,B);
    glPopMatrix();
    
}
void Jogador::DesenhaJogador(double x,double y){
    glPushMatrix();
    glTranslatef(x,y-1.7*this->raio,0);
    Desenhacirculo(this->cx,this->cy,0,255,0);
    Desenhacorpo(this->cx,this->cy,0,255,0);
    Desenhabraco(this->cx,this->cy,255,255,0);
    Desenhaperna1(this->cx,this->cy,255,0,0);
    Desenhaperna2(this->cx,this->cy,255,0,0);
    glPopMatrix();
}

Tiro* Jogador::Atira() {
    if(this->cor == "green"){
        int radius = this->raio*0.1;
        int Angule = Thetabraco;
        int firstX = this->cx +  radius * sin(-Angule * M_PI / 180);
        int firstY = (this->cy-1.1*this->raio) +  radius * cos(-Angule * M_PI / 180);
        return new Tiro(firstX ,firstY, Angule - 90);
    }else{
        int radius = this->raio*0.1;
        int Angule = Thetabraco;
        int firstX = this->cx +  radius * sin(-Angule * M_PI / 180);
        int firstY = (this->cy-1.1*this->raio) +  radius * cos(-Angule * M_PI / 180);
        return new Tiro(firstX ,firstY, Angule - 270);

    }
}

 void Jogador::resetarthetas(){

    this->Thetabraco=0;
    this->Thetaquadril1=0;
    this->Thetajoelho1=0;
    this->Thetaquadril2=0;
    this->Thetajoelho2=0;

    voltandoperna1 = 0;
    voltandojoelho1 = 0;
    voltandoperna2 = 0;
    voltandojoelho2 = 0;
    andar =0;
            
}

bool Jogador::Atingido(Tiro* tiro) {
    GLfloat posx, posy;
    tiro->GetPos(posx, posy);
    //cout << "posx = " << posx << " posy = " << posy << endl;

    if(posx > (this->getCx()- this->getRaio()*0.3) && posx < (this->getCx()+ this->getRaio()*0.3)
    && posy > this->getCy()-2*this->getRaio() && posy < (this->getCy())){
         return 1;
     }else{
         return 0;
     }
              
    
}