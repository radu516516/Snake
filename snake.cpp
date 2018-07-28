#include "snake.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
using namespace std;

void snake::SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);//pt culoare
}
/*
1: Blue
 2: Green
 3: Cyan
 4: Red
 5: Purple
 6: Yellow (Dark)
 7: Default white
 8: Gray/Grey
 9: Bright blue
 10: Brigth green
 11: Bright cyan
 12: Bright red
 13: Pink/Magenta
 14: Yellow
 15: Bright white
-Numbers after 15 are background colors-
*/


snake::snake()//initializare program;
{
    head=new nod_snake;
    head->prev=NULL;
    head->next=NULL;
    directie=Stanga;
    scor=0;
    lungime_snake = 1;
    color=238;
    speed=300;
    dead = false;
   a("harta.txt");//capu isi ia coordonatele din harta
    tail=head;
    system("cls");
    //ctor
}

void snake::add_node(punct p)//marire snake cu inca un node;
{
    lungime_snake++;
    nod_snake *temp=new nod_snake;
    nod_snake *temp1=new nod_snake;
    temp1=head;
    while (temp1->next!=NULL)
    {
            temp1=temp1->next;
    }
    temp->coord.x=p.x;
    temp->coord.y=p.y;
    temp1->next=temp;
    temp->next=NULL;
    temp->prev=temp1;
    tail=temp;
    harta[tail->coord.x][tail->coord.y]='2';//updatare harta;//'2' = bucata snake//pune noul nod pe harta
}

void snake::incarca_harta(char *nume_fisier) // HARTA // LOADING HARTA
{
   FILE *FisierHarta;
    FisierHarta = fopen(nume_fisier,"r");
    if(FisierHarta == NULL)
    {
        system("cls");
        puts("Harta nu a putut fi incarcata !");
        getchar();
        exit(1);
    }
    else
    {
        fscanf(FisierHarta,"%d",&linii);
        fscanf(FisierHarta,"%d",&coloane);
        char c;//CARACTERELE DIN FISIER SUNT PUSE IN C TEMPORAR
        int i = 0, j = 0;//index
       //ALOCARE DINAMICA MATRICE
        harta=new char*[linii];
        for( i = 0; i < linii; ++i)
        {
            harta[i] = new char[coloane];
        }
        i=0;
        j=0;
        c=fgetc(FisierHarta);//PRIMU CARACTER E ENTER
        //harta[i][j] = c;
        do
        {
            c = fgetc(FisierHarta);//C IA UN CARACTER DIN FISIER
            switch(c)
            {
                    case '0'://SPATIU LIBER
                        harta[i][j] = c;
                        j++;
                        break;

                    case '1'://PERETE
                        harta[i][j] = c;
                        j++;
                        break;
                    case '2'://CAP SARPE
                        harta[i][j] = c;
                        //j++;
                        head->coord.x=i;//coordonatele capului din harta.txt
                        head->coord.y=j;
                        j++;
                        break;

                    case '\n'://ENDL
                        j = 0;
                        i++;
                        break;

                    default:
                        break;
                }
            }
            while (c != EOF);//EOF = -1 end of file
            fclose (FisierHarta);
        }
    fclose(FisierHarta);
}

void snake::afisare_harta()
{

    for ( int i = 0 ; i <linii;i++)
    {
        for ( int j = 0 ; j <coloane;j++)
        {
            if ( harta[i][j]=='1')
            {
                SetColor(255);
                cout<<char(178);//extended ascii code
                SetColor(7);
            }
            if ( harta[i][j]=='0')
            {
                cout<<" ";
            }
            if ( harta[i][j]=='2')
            {
                SetColor(color);
                cout<<char(254);
                SetColor(7);
            }
        }
        cout<<endl;
    }
}

void snake::gotoxy( int column, int line )
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}
void snake::move_snake()//face aflare directie,modificare coordonoate sarpe in functie de directie,afisare pe ecran sarpe,update harta,si verificari
{
        if (kbhit()==true)
        {
            switch (_getch())
            {
            case 'w':
                directie=Sus;
                break;
            case 's':
                directie=Jos;
                break;
            case 'a':
                directie=Stanga;
                break;
            case 'd':
                directie=Dreapta;
                break;
            case ' ':
                directie=Stop;break;
            default:
                break;
            }
        }
        char a=254;//CARACTER SNAKE//254//233//167=best//
        punct p;
        switch (directie)//PARCURERE DE LA TAIL SPRE HEAD,FIECARE NOD IA COORDONATELE CELUI DIN FATA
        {
            case Sus://W
            {
                    nod_snake *temp=tail;
                    int x=tail->coord.x;//x,y pentru stergere tail initial
                    int y=tail->coord.y;
                    while ( temp->prev !=NULL)
                    {
                        temp->coord.x=temp->prev->coord.x;
                        temp->coord.y=temp->prev->coord.y;
                        temp=temp->prev;
                    }
                    temp->coord.x--;//temp arata la cap
                    gotoxy(y,x);
                    cout<<" ";       //stergere tail de pe ecran si din harta
                    harta[x][y]='0';
                    //extended ascii
                    //verif
                    if ( harta[head->coord.x][head->coord.y]=='1'||harta[head->coord.x][head->coord.y]=='2')//verificare lovire perete si sarpe
                    {
                        dead=true;
                        cout<<char(7);//death sound
                    }
                    //
                    if (head->coord.x==Steluta.x&&head->coord.y==Steluta.y)//POINT
                    {
                    scor += 1;
                    generare_steluta();
                    p.x=tail->coord.x;
                    p.y=tail->coord.y;
                    add_node(p);
                    speed-=2;
                    afisare_scor();

                    }
                    while ( temp!=NULL)
                    {
                        gotoxy(temp->coord.y,temp->coord.x);      //SCRIERE SARPE CU COORD MODIFICATE DUPA MISCARE PE ECRAN SI UPDATARE HARTA
                        //temp;
                        SetColor(color);
                        cout<<a;
                        SetColor(7);//7 = color default white;

                        harta[temp->coord.x][temp->coord.y]='2';
                        temp=temp->next;
                    }
                    break;
            }
            //S
            case Jos:
            {
                nod_snake *temp=tail;
                int x=tail->coord.x;
                int y=tail->coord.y;
                while ( temp->prev !=NULL)
                {
                    temp->coord.x=temp->prev->coord.x;
                    temp->coord.y=temp->prev->coord.y;
                    temp=temp->prev;
                }
                temp->coord.x++;
                gotoxy(y,x);
                cout<<" ";
                harta[x][y]='0';
                //VERIFICARI
                if ( harta[head->coord.x][head->coord.y]=='1'||harta[head->coord.x][head->coord.y]=='2')
                {
                    dead=true;
                    cout<<char(7);
                }
                if (head->coord.x==Steluta.x&&head->coord.y==Steluta.y)//POINT
                {
                    scor += 1;
                    generare_steluta();
                    p.x=tail->coord.x;
                    p.y=tail->coord.y;
                    add_node(p);
                    speed-=10;
                    afisare_scor();

                }
                while ( temp!=NULL)
                {
                    gotoxy(temp->coord.y,temp->coord.x);
                    SetColor(color);
                    cout<<a;
                    SetColor(7);

                    harta[temp->coord.x][temp->coord.y]='2';
                    temp=temp->next;
                }
                break;
            }
            //A
            case Stanga:
            {
                nod_snake *temp=tail;
                int x=tail->coord.x;
                int y=tail->coord.y;
                while ( temp->prev !=NULL)
                {
                    temp->coord.x=temp->prev->coord.x;
                    temp->coord.y=temp->prev->coord.y;
                    temp=temp->prev;
                }
                temp->coord.y--;
                gotoxy(y,x);
                cout<<" ";
                harta[x][y]='0';

                if ( harta[head->coord.x][head->coord.y]=='1'||harta[head->coord.x][head->coord.y]=='2')
                {
                    dead=true;
                    cout<<char(7);
                }

                if (head->coord.x==Steluta.x&&head->coord.y==Steluta.y)//POINT
                {
                    scor += 1;
                    generare_steluta();
                      p.x=tail->coord.x;
                    p.y=tail->coord.y;
                    add_node(p);
                    speed-=2;
                    afisare_scor();

                }
                while ( temp!=NULL)
                {
                    gotoxy(temp->coord.y,temp->coord.x);
                    SetColor(color);
                    cout<<a;
                    SetColor(7);

                    harta[temp->coord.x][temp->coord.y]='2';
                    temp=temp->next;
                }
                break;
            }
            //D
            case Dreapta:
            {
                nod_snake *temp=tail;
                int x=tail->coord.x;
                int y=tail->coord.y;
                while ( temp->prev !=NULL)
                {
                    temp->coord.x=temp->prev->coord.x;
                    temp->coord.y=temp->prev->coord.y;
                    temp=temp->prev;
                }
                temp->coord.y++;
                gotoxy(y,x);
                cout<<" ";
                harta[x][y]='0';

                if ( harta[head->coord.x][head->coord.y]=='1'||harta[head->coord.x][head->coord.y]=='2')
                {
                    dead=true;
                    cout<<char(7);
                }
                if (head->coord.x==Steluta.x&&head->coord.y==Steluta.y)//POINT
                {
                    scor += 1;
                    generare_steluta();
                      p.x=tail->coord.x;
                    p.y=tail->coord.y;
                    speed-=10;
                    add_node(p);
                    afisare_scor();

                }
                while ( temp!=NULL)
                {
                    gotoxy(temp->coord.y,temp->coord.x);
                    SetColor(color);
                    cout<<a;
                    SetColor(7);
                    harta[temp->coord.x][temp->coord.y]='2';
                    temp=temp->next;
                }
                break;
            }
            default:
                break;
    }
}

void snake::afisare_scor()
{
	gotoxy(coloane/2-5, 0);
	cout<<"Scor :"<<scor;
}

void snake::generare_steluta()
{
    srand(time(NULL));
	int linie,coloana;
	do
	{
		linie = rand() % linii;
		coloana = rand () % coloane;
	}
	while(harta[linie][coloana] != '0');
	Steluta.y = coloana;
	Steluta.x = linie;
	gotoxy(Steluta.y, Steluta.x);
	SetColor(13);
	cout<<char(233);
	SetColor(7);
}

void snake::desenare_moarte()
{
	gotoxy(coloane/2-5, 9);
	cout<<"Scor :"<<scor;
	gotoxy(coloane/2-11, 10);
	puts("====================");
	gotoxy(coloane/2-11, 11);
	puts("= Ai pierdut !!!!! =");
	gotoxy(coloane/2-11, 12);
	puts("=    R - Joc Nou!  =");
	gotoxy(coloane/2-11, 13);
	puts("=    M - Meniu!    =");
	gotoxy(coloane/2-11, 14);
	puts("====================");
	directie = Stop;
}

int snake::get_speed()
{
    return speed;
}

void snake::setSpeed()
{

    cout<<"Please select difficulty:\n1.Easy\n2.Medium\n3.Hard\n4.Back";
      switch (_getch())
      {
        case '1':speed=500;initSpeed=500;break;
        case '2':speed=300;initSpeed=300;break;
        case '3':speed=100;initSpeed=100;break;
        default:;
        }

}
int snake::GetLinii()
{
    return linii;
}

int snake::getColoane()
{
    return coloane;
}
bool snake::Status()
{
    return dead;
}

void snake::delete_map()
{
    for ( int i = 0 ; i < linii;i++)
      delete[] harta[i];
    delete[] harta;
}

void snake::remove_snake()
{
    nod_snake *temp=new nod_snake;
    nod_snake *temp1=new nod_snake;
    temp=head;
    while(temp!=NULL)
    {
        temp1=temp->next;
        delete temp;
        temp=temp1;
    }
    delete temp1;
}

void snake::reinitialise()
{
    head=new nod_snake;
    head->prev=NULL;
    head->next=NULL;
    directie=Stanga;
    scor=0;
    lungime_snake = 1;
    color=238;
    speed=initSpeed;
    dead = false;
    incarca_harta("harta.txt");
    tail=head;
    system("cls");
}
