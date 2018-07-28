#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>

#include "snake.h"
//JOC SNAKE


using namespace std;

//TO DO
/*
//RERITE BUT BETTER

STELUTE
SCOR
MAYBE ANOTHER MAP

SPEED

colour


*/

int main()
{
    int x=0;
    int c;
   snake *a=new snake();
   Meniu:
   cout<<"1.Start Game!\n2.Select difficulty!\n3.Exit!";
   switch (_getch())
   {case '1':
         system("cls");cout<<"Ce harta doriti sa alegeti ? Aveti urmatoarele optiuni : "<<endl<<"1. HartaEasy"<<endl<<"2. HartaMedium"<<endl<<"3. HartaHard"<<endl<<"4.Back";

            switch(_getch())
            {
            case '1':
                c=1; a->incarca_harta("hartaEasy.txt"); system("cls"); break;

            case '2':
                c=2; a->incarca_harta("hartaMedium.txt"); system("cls"); break;

            case '3':
                c=3; a->incarca_harta("hartaHard.txt"); system("cls"); break;

            default:
                system("cls");goto Meniu; break;
            }
        InGame:
        system("cls");
        a->afisare_harta();
        a->generare_steluta();
        a->afisare_scor();
        while (a->Status()!=true)
        {

            Sleep(a->get_speed());
            a->move_snake();
            a->afisare_scor();
        }
            system("cls");
         a->delete_map();
         a->remove_snake();
        a->desenare_moarte();

        switch (_getch())
        {
            case 'r':
                a->reinitialise();
            if(c==1)a->incarca_harta("hartaEasy.txt");
            if(c==2)a->incarca_harta("hartaMedium.txt");
            if(c==3)a->incarca_harta("hartaHard.txt");
                goto InGame;
            break;
            case 'm': a->reinitialise();goto Meniu;break;
            default: a->reinitialise();goto Meniu;break;
        }

        break;
   case '2':
       system("cls");
       a->setSpeed();
       system("cls");
       goto Meniu;
    case '3':exit(1);
       default:system("cls");;
   }
   // a->incarca_harta("harta.txt");
//    delete a;
    //cout << "Hello world!" << endl;
    return 0;
}
