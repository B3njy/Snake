#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio2.h>
#include <windows.h>
using namespace std;

#define Arriba 72
#define Abajo 80
#define Derecha 77
#define Izquierda 75

int _xc=20,_yc=20;
int tupuntos,puntos,SPEED=205;

void marco(){
    textcolor(BLACK);
    for(int a=1;a<=79;a++){
        gotoxy(a,3);
        printf("%c",205);
        gotoxy(a,26);
        printf("%c",205);
    }
    for(int a=3;a<=26;a++){
        gotoxy(1,a);
        printf("%c",186);
        gotoxy(80,a);
        printf("%c",186);
    }

    gotoxy(1,3);printf("%c",201);
    gotoxy(1,26);printf("%c",200);
    gotoxy(80,3);printf("%c",187);
    gotoxy(80,26);printf("%c",188);
}

class Snake{
    int x=10,y=10;
    int posision[200][2];
    int tamano=6;
    int desicion=3;
    int nose=1;
    char tecla;
public:
    Snake(int _x,int _y);
    void elegir_movimiento();
    void borrar();
    void pintar();
    void cuardar_posicion();
    int colision();
    void mover();
    void servir();
    void comer();
    void puntuacionM();
    void guarPuntos();
    void tuPuntuacion();
};

Snake::Snake(int _x=10,int _y=10){
    x=_x;
    y=_y;
}

void Snake::cuardar_posicion(){
    posision[nose][0]=x;
    posision[nose][1]=y;
    nose++;
    if(nose==tamano){nose=1;}
}

void Snake::pintar(){
    for(int a=1;a<tamano;a++){
        gotoxy(posision[a][0],posision[a][1]);
        textcolor(LIGHTBLUE);
        printf("X");
    }
}

void Snake::borrar(){
    for(int a=1;a<tamano;a++){
        gotoxy(posision[a][0],posision[a][1]);
        printf(" ");
    }
}

void Snake::elegir_movimiento(){
    if(kbhit()){
        tecla=getch();
        switch(tecla){
            case Arriba:if(desicion!=2){desicion=1;}
            break;
            case Abajo:if(desicion!=1){desicion=2;}
            break;
            case Derecha:if(desicion!=4){desicion=3;}
            break;
            case Izquierda:if(desicion!=3){desicion=4;}
            break;
        }
    }
}

void Snake::mover(){
    if(desicion==2){y++;}
    if(desicion==3){x++;}
    if(desicion==4){x--;}
    if(desicion==1){y--;}
}

int Snake::colision(){
    if(y==3||y==26||x==1||x==79){return 1;}

    for(int a=tamano-1;a>0;a--){
        if((posision[a][0]==x)and(posision[a][1]==y)){return 1;}
    }
}

void Snake::servir(){

    gotoxy(_xc,_yc);
    textcolor(MAGENTA);
    cout<<"0";
}

void Snake::comer(){
    Snake snake1;
    if(x==_xc&&y==_yc){
        _xc=rand()%79+1;
        _yc=rand()%23+3;
        tamano++;
        tupuntos=tupuntos+5;
        if(SPEED==0){
            SPEED=200;
        }else{SPEED--;}
        snake1.servir();
    }
}

void Snake::tuPuntuacion(){
    gotoxy(3,2);
    textcolor(WHITE);cout<<"TU PUNTUACION: ";textcolor(LIGHTCYAN);cout<<tupuntos;
}

void Snake::puntuacionM(){
    FILE *Puntos;
    Puntos=fopen("Puntos.txt","rb");
    fflush(Puntos);
    fscanf(Puntos,"%d",&puntos);
    gotoxy(33,2);
    textcolor(WHITE);cout<<"MEJOR RECORD: ";textcolor(LIGHTGREEN);cout<<puntos;
    fclose(Puntos);
}

void Snake::guarPuntos(){
    FILE *Puntos;
    if(tupuntos>puntos){
        Puntos=fopen("Puntos.txt","w");
        if(Puntos==NULL){
            gotoxy(33,2);
            cout<<"xxxx";
        }
        fprintf(Puntos,"%d",tupuntos);
        fclose(Puntos);
    }
}

void juego(){
    tupuntos=0;
    Snake snake1;
    gotoxy(31,10);
    textcolor(BLACK);
    cout<<"Pulse una tecla para iniciar"<<endl;
    getch();
    system("cls");
    marco();
    snake1.servir();
    while(snake1.colision()!=1){
        snake1.tuPuntuacion();
        snake1.puntuacionM();
        snake1.borrar();
        snake1.cuardar_posicion();
        snake1.comer();
        snake1.pintar();
        snake1.elegir_movimiento();
        snake1.elegir_movimiento();
        snake1.mover();
        Sleep(SPEED);
    }
    snake1.guarPuntos();
}

int main(){
    char ext;
    textbackground(DARKGRAY);
    clrscr();
    gotoxy(20,10);
    textcolor(BLACK);
    cout<<"Bienvenido";
    do{
        juego();
        system("cls");
        if(tupuntos>puntos){
            textcolor(BLACK);
            gotoxy(20,10);
            cout<<"GENIAL OBTUVISTE UN NUEVO RECORD."<<endl;
            gotoxy(25,12);
            textcolor(WHITE);cout<<"NUEVO RECORD: ";textcolor(LIGHTGREEN);cout<<tupuntos;
        }
        else{
            gotoxy(23,10);
            textcolor(BLACK);cout<<"HAS PERDIDO";
            gotoxy(20,12);
            textcolor(WHITE);cout<<"PUNTOS OBTENIDOS: ";textcolor(LIGHTCYAN);cout<<tupuntos;
        }
        gotoxy(20,14);
        textcolor(BLACK);cout<<"QUIERES VOLVER A JUGAR (";textcolor(RED);cout<<"S";textcolor(BLACK);
        cout<<"/";textcolor(RED);cout<<"N";textcolor(BLACK);cout<<")?"<<endl;
        fflush(stdin);
        gotoxy(25,15);
        textcolor(RED);
        fflush(stdin);
        cin>>ext;
        system("cls");
    }while((ext!='n')and(ext!='N'));
    gotoxy(20,13);
    textcolor(BLACK);
    cout<<"GRACIAS POR JUGAR...";
    Sleep(1100);
}
