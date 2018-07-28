#ifndef SNAKE_H
#define SNAKE_H

enum Directie  { Stop, Stanga , Sus , Dreapta , Jos };



typedef struct punct
{
    int x;
    int y;
};

typedef struct nod_snake
{
    punct coord;
    int color;
    nod_snake *next;
    nod_snake *prev;

};

class snake
{
private:
    nod_snake *head;
    nod_snake *tail;
    Directie directie;
    int lungime_snake;
    int color;//culoare snake
    int speed;
    bool dead;
    int scor;
    char** harta;//un vector de pointeri din care fiecare poincter arata la un vector(linie) http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    int linii;
    int coloane;
    punct Steluta;
    int initSpeed=300;

public:
    snake();
    ~snake();//dealocare harta si tot ce e alocat dinamic
    void add_node(punct p);
    void incarca_harta(char *nume_fisier);// HARTA
    void afisare_harta();
    void gotoxy( int column, int line );
    void move_snake();
    void SetColor(int value);
    void afisare_scor();
    void generare_steluta();
    void desenare_moarte();
    int get_speed();
    void setSpeed();
    int GetLinii();
    int getColoane();
    bool Status();
    void delete_map();
    void remove_snake();
    void reinitialise();
};

#endif // SNAKE_H
