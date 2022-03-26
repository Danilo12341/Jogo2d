#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "tinyxml.h"
#include <math.h>
#include "circulo.h"
#include "retangulo.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "jogador.h"
#define TAMANHO_JANELA 500
#define INC_KEY 0.02
#define INC_ANG 1
#define INC_KEYIDLE 0.01

using namespace std;
vector<Circulo> circulos;
vector<Retangulo> retangulos;
Retangulo arena;
Circulo jogador1;
Jogador jogadorplay1;
Jogador jogadorplay1inicial;
vector<Jogador> jogadores;
vector<Jogador> jogadoresInicial;
int contadorClicks = 0;
double gravidade;
bool fim = false;
bool morreu = false;
bool pular = false;
//Key status
int keyStatus[256];
Tiro* tiro = NULL;
Tiro* tiro2 = NULL;
Tiro* tiros[30];




static GLdouble framerate = 0;
int teste=0;
void * timesRoman = GLUT_BITMAP_TIMES_ROMAN_24;
static char str[2000];


bool loadXml(char** argv){
    TiXmlDocument doc;
	string diretorio = argv[1];
	/*strcat(argv[1], "arena_teste.svg");*/
	if(!doc.LoadFile(argv[1])){
		cout << "Falha ao abrir o svg Certifique-se que contém o arquivo arena_teste.svg no diretorio " << diretorio << endl;
		return false;
	}
	TiXmlElement* root = doc.FirstChildElement();
    if ( NULL != root){
       for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
            std::string elemName = elem->Value();
            const char* attr;
            Circulo c;
            Retangulo r;
            if(elemName == "rect"){	
                
                attr = elem->Attribute("width");
                if(attr != NULL)
                   r.setWidth(atof(attr));

                attr = elem->Attribute("height");
                if(attr != NULL)
                   r.setHeight(atof(attr));

                attr = elem->Attribute("x");
                if(attr != NULL)
                    r.setRx(atof(attr));

                attr = elem->Attribute("y");
                if(attr != NULL)
                   r.setRy(atof(attr));

                attr = elem->Attribute("fill");
                if(attr != NULL)
                    r.setCor(attr);

              retangulos.push_back(r);
            }
            else if(elemName == "circle"){

              
                attr = elem->Attribute("cx");
                if(attr != NULL)
                  c.setCx(atof(attr));

                attr = elem->Attribute("cy");
                if(attr != NULL)
                   c.setCy(atof(attr));

                attr = elem->Attribute("r");
                if(attr != NULL)
                   c.setRaio(atof(attr));

                attr = elem->Attribute("fill");
                if(attr != NULL)
                   c.setCor(attr);

                circulos.push_back(c);
               		    
            }
       }
    }
    doc.Clear();
	return true;
}
void resetar(){
    
   jogadores =jogadoresInicial;
   jogadorplay1 =jogadorplay1inicial;
   jogadorplay1.resetarthetas();
   bool morreu = false;

   for(int i=0;i<jogadores.size();i++){
       jogadores[i].resetarthetas();
   }

   
  
}
void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {  
        case 'A':
        case 'a':
             keyStatus[(int)('a')] = 1;
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1;
             break;
        case 'r':
        case 'R':
             keyStatus[(int)('r')] = 1; 
      
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}
int valor =1;

void init(void)
{
  glClearColor(0.0, 0.0,0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(arena.getRx(),arena.getRx()+arena.getWidth(), arena.getRy()+arena.getHeight(),arena.getRy(), -1.0, 1.0);
     
  
}
void salvainicial(){


    jogadoresInicial = jogadores;
    jogadorplay1inicial = jogadorplay1;

   
}



void ganhou()
{   
    jogadorplay1.setCx(arena.getRx() + arena.getWidth()+1000);
    glColor3ub(0,255,255);
    char *tmpStr;
    sprintf(str, "Voce Ganhou, Aperte r para reiniciar");
    glRasterPos2f(jogadorplay1.getCx()-30, jogadorplay1.getCy()-20);
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(timesRoman, *tmpStr);
        tmpStr++;
    }
}
void perdeu()
{   jogadorplay1.setCx(arena.getRx() + arena.getWidth()+1000);
    glColor3ub(0,255,255);
    char *tmpStr;
    sprintf(str, "Game Over, Aperte r para reiniciar");
    glRasterPos2f(jogadorplay1.getCx()-30, jogadorplay1.getCy()-20);
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(timesRoman, *tmpStr);
        tmpStr++;
    }
}




int colisao(Jogador jog1, vector<Retangulo> regantulo){
   
    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx() > regantulo[p].getRx() && jog1.getCx() < (regantulo[p].getRx()+regantulo[p].getWidth())
               && jog1.getCy() > regantulo[p].getRy() && jog1.getCy() < (regantulo[p].getRy()+regantulo[p].getHeight()))
             
             {
                return 1;
              
            }
           
        }
        
    }
    return 0;       
}

int colisao3(Jogador jog1, vector<Retangulo> regantulo){
   
    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx() > regantulo[p].getRx()+jog1.getRaio()*0.5 && jog1.getCx() < (regantulo[p].getRx()+regantulo[p].getWidth()-jog1.getRaio()*0.5)
               && jog1.getCy() > regantulo[p].getRy() && jog1.getCy() < (regantulo[p].getRy()+regantulo[p].getHeight()))
             
             {
                return 1;
              
            }
           
        }
        
    }
    return 0;       
}


int colisadodireita(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx()+jog1.getRaio()*0.3 > regantulo[p].getRx() && jog1.getCx()+jog1.getRaio()*0.3 < regantulo[p].getRx()+regantulo[p].getWidth()
               && (jog1.getCy()-2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-0.2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-0.2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy() && jog1.getCy() > regantulo[p].getRy()+regantulo[p].getHeight()))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}

int colisadodireitainimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCx()+jog1.getRaio()*0.3 > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()+jog1.getRaio()*0.3 < jogadores[p].getCx()+jogadores[p].getRaio()*0.3 
               && (jog1.getCy()-2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jogadores[p].getCy() 
              || jog1.getCy()-0.2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-0.2*jog1.getRaio() < jogadores[p].getCy()))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}

int colisadoesquerdainimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCx()-jog1.getRaio()*0.3 > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()-jog1.getRaio()*0.3 < jogadores[p].getCx()+jogadores[p].getRaio()*0.3 
               && (jog1.getCy()-2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jogadores[p].getCy() 
              || jog1.getCy()-0.2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-0.2*jog1.getRaio() < jogadores[p].getCy()))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadoesquerdainimigo2(Jogador jog1, Jogador jog2){


    if(jog1.getCx()-jog1.getRaio()*0.3 > jog2.getCx()-jog2.getRaio()*0.3 && jog1.getCx()-jog1.getRaio()*0.3 < jog2.getCx()+jog2.getRaio()*0.3 
    && (jog1.getCy()-2*jog1.getRaio() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jog2.getCy() 
    || jog1.getCy() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy() < jog2.getCy()))
            
     {
                
                return 1;
              
    }
                 
    return 0;

}
int colisadodireitainimigo2(Jogador jog1, Jogador jog2){


    if(jog1.getCx()+jog1.getRaio()*0.3 > jog2.getCx()-jog2.getRaio()*0.3 && jog1.getCx()+jog1.getRaio()*0.3 < jog2.getCx()+jog2.getRaio()*0.3 
    && (jog1.getCy()-2*jog1.getRaio() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jog2.getCy() 
    || jog1.getCy() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()< jog2.getCy()))
            
     {
                
                return 1;
              
    }
                 
    return 0;

}


int colisadoesquerda(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx()-jog1.getRaio()*0.3 > regantulo[p].getRx() && jog1.getCx()-jog1.getRaio()*0.3 < regantulo[p].getRx()+regantulo[p].getWidth()
               && (jog1.getCy()-2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-0.2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-0.2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy() && jog1.getCy() > regantulo[p].getRy()+regantulo[p].getHeight()))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadotopo(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCy()-jog1.getRaio()*2 > regantulo[p].getRy() && jog1.getCy()-jog1.getRaio()*2 < regantulo[p].getRy()+regantulo[p].getHeight()
               && (jog1.getCx()-0.15*jog1.getRaio() > regantulo[p].getRx() && jog1.getCx()-0.15*jog1.getRaio() < regantulo[p].getRx()+regantulo[p].getWidth()
              || jog1.getCx()+0.15*jog1.getRaio() > regantulo[p].getRx() && jog1.getCx()+0.15*jog1.getRaio() < regantulo[p].getRx()+regantulo[p].getWidth()))
            
    
             {
            
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadotopinimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCy() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy() < jogadores[p].getCy()
               && (jog1.getCx()-0.3*jog1.getRaio() > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()-0.3*jog1.getRaio() < jogadores[p].getCx()+jogadores[p].getRaio()*0.3
              || jog1.getCx()+ 0.3*jog1.getRaio() > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()+0.3*jog1.getRaio() < jogadores[p].getCx()+jogadores[p].getRaio()*0.3))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}



void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);
   

    arena.DesenhaRect(0,0,1);
    for (int i = 0; i < retangulos.size(); i++){
        if(retangulos[i].getCor()=="black"){
        retangulos[i].DesenhaRect(0,0,0);
        }
    }
    /*jogador1.Desenhacirculo(0,255,0); 
     jogadorplay1.getCy() > (91.6-4.2*jogadorplay1.getRaio()
    */
    
   
    if(jogadorplay1.getCx()> arena.getRx()+ arena.getWidth() || morreu== true){
         fim = true;
         if(morreu==true){
            
           perdeu();
         }else{
            ganhou(); 
         }
         
    

    }
   
   for (int i = 0; i < jogadores.size(); i++){

       if(jogadores[i].getCy() < (arena.getRy()+arena.getHeight()) && !colisao(jogadores[i],retangulos) && jogadores[i].getCor()=="red"){
       
           jogadores[i].MoveEmY(0.1,1);
           jogadores[i].setCy(jogadores[i].getCy()+0.1);

       }
                     
    }
    
    if(jogadorplay1.getCy() < (arena.getRy()+arena.getHeight())&& !colisao(jogadorplay1,retangulos) && !colisadotopinimigo(jogadorplay1,jogadores)){

        static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
        GLdouble curTime, deltaTime;
        curTime = glutGet(GLUT_ELAPSED_TIME);
        deltaTime = curTime - prevTime;
        prevTime = curTime;
        framerate = 1.0 / deltaTime * 1000;
        double inc = INC_KEYIDLE;
          
        jogadorplay1.MoveEmY(0.1,1);
        jogadorplay1.setCy(jogadorplay1.getCy()+0.1);

        
    }
        
    jogadorplay1.Desenha();
    for (int i = 0; i < jogadores.size(); i++){
        if(jogadores[i].getCor()=="red"){
           jogadores[i].Desenha();
        }
    }
    if (tiro)
        tiro->Desenha();


    for(int k=0;k<jogadores.size();k++){
       if(jogadores[k].getCor()=="red"){
           if(tiros[k])
              tiros[k]->Desenha();

       }
    }
    
    


   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}
int teste2;
void  moveoponente(GLdouble time){

    for(int i=0;i<jogadores.size();i++){
        if(jogadores[i].getparadodireita() == 0 && !colisadoesquerdainimigo2(jogadores[i],jogadorplay1) && colisao3(jogadores[i],retangulos)){   
            jogadores[i].MoveEmX(0.002,time);
            jogadores[i].setCx(jogadores[i].getCx()+ 0.002*time);    
        }
        else{
          if(jogadores[i].getCy()<(arena.getRy()+arena.getHeight())){
              if(jogadores[i].getparadodireita()==0){
                jogadores[i].MoveEmX(-0.002,time);
                jogadores[i].setCx(jogadores[i].getCx()-0.002*time);
                jogadores[i].setparadodireita(1);
              }  
                if(colisao3(jogadores[i],retangulos) && jogadores[i].getparadodireita() == 1){    
                jogadores[i].MoveEmX(-0.002,time);
                jogadores[i].setCx(jogadores[i].getCx()-0.002*time);
                }else{
                    jogadores[i].MoveEmX(0.002,time);
                    jogadores[i].setCx(jogadores[i].getCx()+0.002*time);
                    jogadores[i].setparadodireita(0);
                }
            }
        }
    }

}
void  moveoponente2(GLdouble time){
   
   for(int i=0;i<jogadores.size();i++){
     if(jogadores[i].getCy() > (arena.getRy()+arena.getHeight())){


         if(!colisadodireita(jogadores[i],retangulos) && jogadores[i].getCor()=="red" && !colisadoesquerdainimigo2(jogadores[i],jogadorplay1)&&jogadores[i].getCx() < (arena.getRx()+arena.getWidth()) && jogadores[i].getparadodireita() == 0 ){
            jogadores[i].MoveEmX(0.002,time);
            jogadores[i].setCx(jogadores[i].getCx()+ 0.002*time);
         }else{                    
            jogadores[i].setparadodireita(1);
            if(!colisadoesquerda(jogadores[i],retangulos) && jogadores[i].getCx() > arena.getRx() && jogadores[i].getparadodireita() == 1){
                jogadores[i].MoveEmX(-0.002,time);
                jogadores[i].setCx(jogadores[i].getCx()-0.002*time);
                
            }else{
                jogadores[i].setparadodireita(0);
            }


         }

     }


   }

}



double anterior;
double anterior2;
double anterior3;
int valor3;
void idle(void)
{
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
    double inc = INC_KEYIDLE;



    glClearColor(0.0, 0.0,0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(jogadorplay1.getCx()-arena.getHeight()/2,jogadorplay1.getCx()+arena.getHeight()/2,arena.getRy()+arena.getHeight(),arena.getRy(), -1.0, 1.0);
    glutPostRedisplay();

    if(keyStatus[(int)('a')] && !colisadoesquerda(jogadorplay1,retangulos) && !colisadoesquerdainimigo(jogadorplay1,jogadores) && jogadorplay1.getCx()-0.3*jogadorplay1.getRaio()>arena.getRx() )
    {
        jogadorplay1.setCx(jogadorplay1.getCx()-(INC_KEY*deltaTime));
        jogadorplay1.MoveEmX(-INC_KEY,deltaTime);
        jogadorplay1.Rodaquadrail1(-INC_ANG);
        jogadorplay1.Rodaquadrail2(-INC_ANG);
        jogadorplay1.Rodajoelho1(INC_ANG);
        jogadorplay1.Rodajoelho2(INC_ANG);
        
    }
    if(keyStatus[(int)('d')] && !colisadodireita(jogadorplay1,retangulos) && !colisadodireitainimigo(jogadorplay1,jogadores))
    {   
        jogadorplay1.setCx(jogadorplay1.getCx()+(INC_KEY*deltaTime));
        jogadorplay1.MoveEmX(INC_KEY,deltaTime);
        jogadorplay1.Rodaquadrail1(-INC_ANG);
        jogadorplay1.Rodaquadrail2(-INC_ANG);
        jogadorplay1.Rodajoelho1(INC_ANG);
        jogadorplay1.Rodajoelho2(INC_ANG);
    
    }
    if(true){
      moveoponente(deltaTime);
      moveoponente2(deltaTime);
      for(int u=0;u<jogadores.size();u++){
          if(jogadores[u].getCor()!="green"){
            jogadores[u].Rodaquadrail1(-INC_ANG);
            jogadores[u].Rodaquadrail2(-INC_ANG);
            jogadores[u].Rodajoelho1(INC_ANG);
            jogadores[u].Rodajoelho2(INC_ANG);
          }
       }     

    }
    if(pular){

        jogadorplay1.setCy(jogadorplay1.getCy()-jogadorplay1.getRaio()*3);
        jogadorplay1.MoveEmY(-jogadorplay1.getRaio()*3,1);
        pular=false;
 
    }
    
    if(keyStatus[(int)('r')]){
       if(fim){
           resetar();
           fim = false;
           morreu=false;
       }
    }
    if(prevTime-anterior>4000){
        for(int k=0;k<jogadores.size();k++){
            if(jogadores[k].getCor()=="red" && jogadores[k].getCy()>(arena.getRy()+arena.getHeight())){
                anterior = prevTime;
                tiros[k] = jogadores[k].Atira();
                
            }
        }
    }
    for(int k=0;k<jogadores.size();k++){

        if(jogadores[k].getCor()=="red" && jogadores[k].getCy()>(arena.getRy()+arena.getHeight())){
             if (tiros[k]) {
                tiros[k]->Move(deltaTime);

                for (int j=0;j<retangulos.size();j++){
                    if (retangulos[j].Atingido(tiros[k]) && retangulos[j].getCor()=="black") {
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;    
                    } 
                }

                if (jogadorplay1.Atingido(tiros[k])) {
                    delete tiros[k];
                    tiros[k] = NULL;
                    morreu=true;
                    return;    
                }
                if(true){
                    GLfloat posx, posy;
                    tiros[k]->GetPos(posx, posy);
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth()){
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;
                    }
                }
     

                if (!tiros[k]->Valido()) {
                    delete tiros[k];
                    tiros[k]= NULL;
                }
            }
        }

    }
    if(prevTime-anterior2>5000){
        for(int k=0;k<jogadores.size();k++){
            if(jogadores[k].getCor()=="red" && jogadores[k].getCy() < (arena.getRy()+arena.getHeight())){
                anterior2 = prevTime;
                tiros[k] = jogadores[k].Atira();
                
            }
        }
    }
    for(int k=0;k<jogadores.size();k++){
        if(jogadores[k].getCor()=="red" && jogadores[k].getCy()<(arena.getRy()+arena.getHeight())){
             if (tiros[k]) {
                tiros[k]->Move(deltaTime);
                
                for (int j=0;j<retangulos.size();j++){
                    if (retangulos[j].Atingido(tiros[k]) && retangulos[j].getCor()=="black") {
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;    
                    } 
                }

                if (jogadorplay1.Atingido(tiros[k])) {
                    delete tiros[k];
                    tiros[k] = NULL;
                    morreu=true;
                    return;    
                }
                 if(true){
                    GLfloat posx, posy;
                    tiros[k]->GetPos(posx, posy);
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth()){
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;
                    }
                }

                if (jogadorplay1.Atingido(tiros[k])) {
                    delete tiros[k];
                    tiros[k] = NULL;
                    morreu=true;
                    return;    
                } 
                
               
                if (!tiros[k]->Valido()) {
                    delete tiros[k];
                    tiros[k]= NULL;
                }
            }
        }

    }
    if (tiro) {
        tiro->Move(deltaTime);

        for (int j=0;j<jogadores.size();j++){
            if (jogadores[j].Atingido(tiro) && jogadores[j].getCor()=="red") {
                delete tiro;
                tiro = NULL;
                jogadores[j].setCy(arena.getRy()+arena.getHeight() +1000);
                jogadores[j].setCx(arena.getRx()+arena.getWidth()+2000);
                return;    
            } 
        }

        for (int j=0;j<retangulos.size();j++){
            if (retangulos[j].Atingido(tiro) && retangulos[j].getCor()=="black") {
                delete tiro;
                tiro = NULL;
                return;    
            } 
        }
         if(true){
                    GLfloat posx, posy;
                    tiro->GetPos(posx, posy);
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth() ||
                    posy < arena.getRy() || posy > arena.getRy()+arena.getHeight()  ){
                        delete tiro;
                        tiro = NULL;
                        return;
                    }
                }
        
        if (!tiro->Valido()) {
            delete tiro;
            tiro = NULL;
        }
       

    }
}

void mouse(int button, int state, int x, int y){
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
    double inc = INC_KEYIDLE;
    

    if (button == GLUT_LEFT_BUTTON){
        if (!tiro)
            tiro = jogadorplay1.Atira();
                 
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !colisadotopo(jogadorplay1,retangulos)){
       
        int incremento =0;
        if(jogadorplay1.getCy() > (arena.getRy()+arena.getHeight()) || colisao(jogadorplay1,retangulos) || colisadotopinimigo(jogadorplay1,jogadores)){
            pular=true;
            
            
        }
        
    
    }

  
}
void motionMouse(int x, int y)
{
    if(y<250){
      jogadorplay1.RodaBracoup(-(250-y)*0.01);
    }
    if (y>250){   
     jogadorplay1.RodaBracodown(-(250-y)*0.01);
    }

   
}
int main(int argc, char** argv){
    if(argc == 1){
		cout << "Informe o diretório do xml com as configurações!" << endl;
		return 0;
	}
	if(!loadXml(argv)){
		return 0;
	}
    for (int j = 0; j < retangulos.size(); j++){
        if(retangulos[j].getCor ()== "blue"){
            arena = retangulos[j];
        }
    }

    for (int i = 0; i < circulos.size(); i++){
        if(circulos[i].getCor()=="green"){
            jogador1 = circulos[i];
        }
    }
    for (int i = 0; i < circulos.size(); i++){
       Jogador j;
       jogadores.push_back(j);
       jogadores[i].setCx(circulos[i].getCx());
       jogadores[i].setCy(circulos[i].getCy());
       jogadores[i].setCor(circulos[i].getCor());
       jogadores[i].setRaio(circulos[i].getRaio());

       if(jogadores[i].getCor() == "green")  {
           jogadorplay1 = jogadores[i];
       } 
    }
    salvainicial();
    
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500,500); 
    glutInitWindowPosition (150, 150);
    glutCreateWindow ("Trabalho cg-2d");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(motionMouse);
    glutMouseFunc(mouse);
    init ();
    glutMainLoop();

    return 0;

}