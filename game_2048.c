#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>
#include <ctype.h>
#include <time.h>

#define ERROR  ERR  // definim variala de eroare

void meniu(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo,int *check_undo); // functia de afisare a meniului si de navigare in meniu
void new_game(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo,int *check_undo); //functia pentru joc
void left(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo); //functia de miscare la apasarea LEFT_KEY
void right(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo); //functia de miscare la apasarea RIGHT_KEY
void down(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo); //functia de miscare la apasarea DOWN_KEY
void up(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo); //functia de miscare la apasarea UP_KEY
void show_matrix_full(int **matrice,char *var,int *sum); // functia de afisare a tabelei cu numere
void show_matrix_empty(); // functia de afisare a tabelei goala
void left_check(int **v,int *vect_first,int **matrice_check); // functia verifica daca ne putem misca la stanga
void right_check(int **v,int *vect_first,int **matrice_check); // functia verifica daca ne putem misca la dreapta
void down_check(int **v,int *vect_first,int **matrice_check); // functia verifica daca ne putem misca jos
void up_check(int **v,int *vect_first,int **matrice_check); // functia verifica daca ne putem misca sus
void show_available_moves(int **check1,int **check2,int **matrice,int *vect_first,int **matrice_check); // functia arata miscarile posibile la momentul respectiv
void choose_alone(int **check1,int **check2,int **matrice,int *vect_first,int **matrice_check,int *sum,int *check_undo); // functia decide care miscare este mai buna, in cazul in care utilizatorul nu executa o comanda
void game_instructions(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo,int *check_undo); //functia arata cum instructiunile jocului
int left_choose(int **v,int *vect_first,int **matrice_check,int sum); // functia calculeaza suma in cazul in care miscare s-ar face la stanga
int right_choose(int **v,int *vect_first,int **matrice_check,int sum); // functia calculeaza suma in cazul in care miscare s-ar face la dreapta
int down_choose(int **v,int *vect_first,int **matrice_check,int sum); // functia calculeaza suma in cazul in care miscare s-ar face in jos
int up_choose(int **v,int *vect_first,int **matrice_check,int sum); // functia calculeaza suma in cazul in care miscare s-ar face in sus
void prim(); // functie de intampinare a utilizatorului
void atribuire(int **matrice_undo, int **matrice ); // atribuire matrice_undo pentru undo
int left_choose(int **v,int *vect_first,int **matrice_check,int sum) // functia calculeaza suma in cazul in care miscare s-ar face la stanga
{
  int stop; // variabila de verificare 
  int i,j,k;  // variabile de parcurgere a matricei
  int hold_pos; //variabila de verificare
  for(i=0;i<4;i++) //parcurgem matricea initiala 
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j]; // umplem matrice_check cu valorile matricei principale 
    }
  }
  for(k=0;k<4;k++) // parcurgem fiecare linie
  {
  hold_pos=0;
  stop=0;
  for(i=0;i<4;i++) // parcurgem fiecare coloana
  {
    if( v[k][i]!= 0) // in cazul in care intalnim un element care nu este zero in matricea principala
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--)  // pentru fiecare element care nu este zero incepem din stanga acestuia
      {
          if(v[k][j]==0) // in cazul in care elementul din stanga este 0
          {
            v[k][j]=v[k][j+1]; //il mutam pe pozitia anterioara
            v[k][j+1]=0;  // pe pozitia pe care se afla elementul diferit de 0 o facem 0
            if(v[k][j-1]==0 && hold_pos==2) // in cazul in care s-au adunat deja doua valori si suntem deja coloana a 3-a, scadem hold_pos-ul pentru a nu se reface operatia
              hold_pos--;          
          }
          if(v[k][j]==v[k][j+1] && stop==0) // daca avem doua casute alaturate egale si variabila stop = 0(adica nu s-a facut nicio alipire)
          {
            hold_pos=i; // retinem pozitia
            stop++; // s-a facut o alipire
            v[k][j]*=2; // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[k][j+1]=0; // pe pozitia din dreapta punem 0
            sum+=v[k][j]; // construim scorul
          }
          if(v[k][j]==v[k][j+1] && stop==1) //daca avem doua casute alaturate egale si variabila stop = 1(adica s-a facut o alipire)
          {
            {
            stop++; // s-a facut o alipire
            v[k][j]*=2; // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[k][j+1]=0; // pe pozitia din dreapta punem 0
            sum+=v[k][j]; // construim scorul
            }
          }
      }
    }
  }
  }
  return sum; // returneaza scorul
}
int right_choose(int **v,int *vect_first,int **matrice_check,int sum) // functia calculeaza suma in cazul in care miscare s-ar face la dreapta
{
  int stop; // variabila de verificare
  int i,j,k; // variabile de parcurgere
  int hold_pos; // variabila de verificare

  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j]; // umplem matrice_check cu valorile matricei principale 
    }
  }


  for(k=0;k<4;k++)  // parcurgem fiecare linie
  {
  hold_pos=3;
  stop=0;
  for(i=3;i>=0;i--) // parcurgem fiecare coloana
  {
    if( v[k][i] != 0) // in cazul in care intalnim un element care nu este zero in matricea principala
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++) //pentru fiecare element care nu este zero incepem din dreapta acestuia
      {
          if(v[k][j]==0) // in cazul in care elementul din dreapta este 0
          {
            v[k][j]=v[k][j-1]; // il mutam pe pozitia posterioara
            v[k][j-1]=0; // pe pozitia pe care se afla elementul diferit de 0 o facem 0
            if(v[k][j+1]==0 && hold_pos==1) // in cazul in care s-au adunat deja doua valori
            hold_pos++; 
          }
          if(v[k][j]==v[k][j-1] && stop==0) // daca avem doua casute alaturate egale si variabila stop = 0 (adica nu s-a facut nicio alipire)
          {
            hold_pos=i; // retinem pozitia
            stop++; // s-a facut o alipire
            v[k][j]*=2; // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[k][j-1]=0; // pe pozitia din stanga punem 0
            sum+=v[k][j]; // construim scorul general
          }
          if(v[k][j]==v[k][j-1] && stop==1) //daca avem doua casute alaturate egale si variabila stop = 1(adica s-a facut o alipire)
          {
            stop++; // s-a facut o alipire
            v[k][j]*=2;// tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[k][j-1]=0; // pe pozitia din stanga punem 0
            sum+=v[k][j]; // construim scorul general
          } 
      }
    }
  }
  }

  return sum;
}
int down_choose(int **v,int *vect_first,int **matrice_check,int sum) // functia calculeaza suma in cazul in care miscare s-ar face in jos
{
  int stop; // variabila de verificare
  int i,j,k; // variabila de parcurgere 
  int hold_pos; // variabila de verificare

  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j]; // umplem matrice_check cu valorile matricei principale
    }
  }


  for(k=0;k<4;k++) //parcurgem fiecare coloana
  {
  stop=0;
  hold_pos=3;
  for(i=3;i>=0;i--) //parcurgem fiecare linie
  {
    if( v[i][k]!= 0) // in cazul in care intalnim un element care nu este zero in matricea principala
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++) // pentru fiecare element care nu este zero incepem de sub acesta
      {
          if(v[j][k]==0) // in cazul in care elementul este 0
          {
            v[j][k]=v[j-1][k]; // il mutam pe acea pozitie
            v[j-1][k]=0;  // pe pozitia pe care se afla elementul diferit de 0 punem 0
            if(j<=2 && v[j+1][k]==0 && hold_pos==1) // pentru a nu ramane 0 dupa ce o alipire este facut si ne aflam pe pozitia a 2
              hold_pos++;          
          }
          if(v[j][k]==v[j-1][k] && stop==0) // daca avem doua casute alaturate egale si variabila stop = 0(adica nu s-a facut nicio alipire)
          {
            hold_pos=i; //retinem pozitia
            stop++; // s-a facut o alipire
            v[j][k]*=2;  // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[j-1][k]=0; // pe pozitia de sus punem 0
            sum+=v[j][k]; // construim scorul general
          }
          if(v[j][k]==v[j-1][k] && stop==1) //daca avem doua casute alaturate egale si variabila stop = 1(adica s-a facut o alipire)
            {
            stop++; // s-a facut o alipire
            v[j][k]*=2; // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[j-1][k]=0; // pe pozitia de sus punem 0
            sum+=v[j][k]; //construim scorul general
          } 
      }
    }
  }
  }

  return sum; //returneaza scorul
}
int up_choose(int **v,int *vect_first,int **matrice_check,int sum) // functia calculeaza suma in cazul in care miscare s-ar face in sus
{
  int stop; // variabila de verificare
  int i,j,k; // variabila de parcurgere
  int hold_pos; // variabila de verificare 

   for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j]; // umplem matrice_check cu valorile matricei principale 
    }
  }

  for(k=0;k<4;k++) //parcurgem fiecare coloana
  {
  stop=0;
  hold_pos=0;
  for(i=0;i<4;i++) // parcurgem fiecare linie
  {
    if( v[i][k]!= 0)  // in cazul in care intalnim un element care nu este zero in matricea principala
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--) // pentru fiecare element care nu este zero incepem cu pozitia de mai sus
      {
          if(v[j][k]==0) // in cazul in care elementul de mai sus este 0
          {
            v[j][k]=v[j+1][k]; // mutam elementul
            v[j+1][k]=0;   // punem 0 pe pozitia initiala

            if(j>=1 && v[j-1][k]==0 && hold_pos==2) //punem acest if pentru o verificare dupa ce prima alipire a fost facuta
              hold_pos--;          
          }
          if(v[j][k]==v[j+1][k] && stop==0)  // daca avem doua casute alaturate egale si variabila stop = 0(adica nu s-a facut nicio alipire)
          {
            hold_pos=i; // retinem pozitia
            stop++; // s-a facut o alipire
            v[j][k]*=2;  // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[j+1][k]=0; // pe pozitia de jos punem 0
            sum+=v[j][k];  // construim scorul
          }
          if(v[j][k]==v[j+1][k] && stop==1) //daca avem doua casute alaturate egale si variabila stop = 1(adica s-a facut o alipire)
          {
            stop++; // s-a facut o alipire 
            v[j][k]*=2; // tinand cont ca in acest joc sunt numai puteri a lui 2, nu trebuie neaparat sa le adunam atunci cand alipim, ci putem sa inmultim cu 2
            v[j+1][k]=0; // pe pozitia de jos punem 0
            sum+=v[j][k]; // construim scorul
          } 
      }
    }

  }
  }
  return sum; // returneaza scorul
}
void choose_alone(int **check1,int **check2,int **matrice,int *vect_first,int **matrice_check,int *sum,int *check_undo)  // functia decide care miscare este mai buna, in cazul in care utilizatorul nu executa o comanda
{
  int verifica[4]={0,0,0,0}; // vector in care retinem ce miscari sunt posibile v[0]-> miscare stanga v[1] -> miscare dreapta v[2]-> miscare jos v[3]-> miscare sus
  int i,j,k=0,l=0;
  int choose[4]={0,0,0,0}; // vector in care retinem suma obtinuta daca am face miscarea respectiva. Avem aceeasi indici pentru miscari ca mai sus
  for(i=0;i<3;i++)
    choose[i]=-1;
  for(i=0;i<4;i++)
    {
      for(j=0;j<4;j++)
        {
          check1[i][j]=matrice[i][j]; // copiem matricea principala in prima matrice de verificare
          check2[i][j]=matrice[i][j]; // copiem matricea principala in a doua matrice de verificare
        }
    }

      left_check(check1,vect_first,matrice_check); // verificam daca se poate sa facem miscarea la stanga
      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          if(check1[i][j]!=check2[i][j]) // daca se intra in acest if inseamna ca s-a putut face miscarea la stanga
            {
              verifica[l]=1;
              choose[k]= left_choose(check2,vect_first,matrice_check,0); // calculam suma daca s-ar face miscarea la stanga
              j=4; i=4; // nu mai are rost sa parcurga toate for-urile. Este indeajuns ca un singur element sa difere 
            }
        }
      }

      k++;
      l++; // incrementam pentru a trece la urmatoarea verificare de miscare

      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          check1[i][j]=matrice[i][j]; // copiem matricea principala in prima matrice de verificare
          check2[i][j]=matrice[i][j]; // copiem matricea principala in a doua matrice de verificare
        }
      }
      right_check(check1,vect_first,matrice_check); // verificam daca se poate sa facem miscarea la dreapta
      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          if(check1[i][j]!=check2[i][j]) // daca se intra in acest if inseamna ca s-a putut face miscarea la dreapta
            {
              verifica[l]=1;
              choose[k]= right_choose(check2,vect_first,matrice_check,0); // calculam suma daca s-ar face miscarea la dreapta
              j=4; i=4; // nu mai are rost sa parcurga toate for-urile. Este indeajuns ca un singur element sa difere 
            }
        }
      }


      k++;
      l++; // incrementam pentru a trece la urmatoarea verificare de miscare

      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          check1[i][j]=matrice[i][j]; // copiem matricea principala in prima matrice de verificare
          check2[i][j]=matrice[i][j]; // copiem matricea principala in a doua matrice de verificare
        }
      }
      down_check(check1,vect_first,matrice_check); // verificam daca se poate sa facem miscare in jos
      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          if(check1[i][j]!=check2[i][j]) // daca se intra in acest if inseamna ca s-a putut face miscarea in jos 
            {
              verifica[l]=1;
              choose[k]= down_choose(check2,vect_first,matrice_check,0); // calculam suma daca s-ar face miscarea in jos
              j=4; i=4; // nu mai are rost sa parcurga toate for-urile. Este indeajuns ca un singur element sa difere 
            }
        }
      }

      k++;
      l++; // incrementam pentru a trece la urmatoarea verificare de miscare

      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          check1[i][j]=matrice[i][j]; // copiem matricea principala in prima matrice de verificare
          check2[i][j]=matrice[i][j]; // copiem matricea principala in a doua matrice de verificare
        }
      }
      up_check(check1,vect_first,matrice_check); // verificam daca se poate sa facem miscare in sus
      for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          if(check1[i][j]!=check2[i][j]) // daca se intra in acest if inseamna ca s-a putut face miscarea in sus
            {
              verifica[l]=1;
              choose[k]= up_choose(check2,vect_first,matrice_check,0); // calculam suma daca s-ar face miscarea in sus
              j=4; i=4; // nu mai are rost sa parcurga toate for-urile. Este indeajuns ca un singur element sa difere 
            }
        }
      }
      int max = -1; // variabila pentru a alege choose[i] maxim
      int maxi; // variabila pentru a alege choose[i] maxim, retine pozitia 
      for(i=0;i<4;i++)
      {
        if(choose[i] > max)
          {
            max = choose[i];
            maxi = i;
          }
      }
      switch(maxi) // alege in functie de ce pozitie are valoarea maxima choose[i]
      {
        case 0: // la stanga 
        if(verifica[0]==1) //daca se poate
        {
          left(matrice,vect_first,matrice_check,sum,check_undo);
          break;
        }
        case 1: // la dreapta
        if(verifica[1]==1)
        {
          right(matrice,vect_first,matrice_check,sum,check_undo);
        break;
        }
        case 2: // in jos
        if(verifica[2]==1)
        {
          down(matrice,vect_first,matrice_check,sum,check_undo);
          break;
        }
        case 3: // in sus
        if(verifica[3]==1)
        {
          up(matrice,vect_first,matrice_check,sum,check_undo);
        break;  
        }
        
      }
}
void show_available_moves(int **check1,int **check2,int **matrice,int *vect_first,int **matrice_check) // functia arata miscarile posibile la momentul respectiv
{

  /* Pentru ca programul este repetitiv voi incerca sa explic pe scurt ce face aceasta functie, in loc sa comentez fiecare rand transformand programul 
  in unul greu de citit. Astfel: am folosit doua matrici check1 si check2, iar in prima faza am copiat matricea principala in aceaste doua matrici de
  verificare. Apoi cu matricea check1 am incercat sa verific daca se poate face miscarea la stanga/dreapta/sus/jos, iar apoi am comparat-o cu matricea
  intacta check2, identica cu matricea principala. In cazul in care am gasit cel putin un element schimbat, atunci am scris pe ecran ca miscarea este
  posibila. In caz contrat nu am scris nimic. Am introdus variabila count pentru afisarea mai eleganta a datelor despre miscari pe ecranul jocului. */

	int i,j;
	int count=1;
	mvprintw(5,55,"Available moves:");
      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		check1[i][j]=matrice[i][j];
      		check2[i][j]=matrice[i][j];
      	}
      }

      left_check(check1,vect_first,matrice_check);
      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		if(check1[i][j]!=check2[i][j])
      			{
      				mvprintw(5+count,55,"You can move to left");
      				count++;
      				j=4; i=4;
      			}
      	}
      }


     for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		check1[i][j]=matrice[i][j];
      		check2[i][j]=matrice[i][j];
      	}
      }
      right_check(check1,vect_first,matrice_check);
      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		if(check1[i][j]!=check2[i][j])
      			{
      				mvprintw(5+count,55,"You can move to right");
      				count++;
      				j=4; i=4;
      			}
      	}
      }



      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		check1[i][j]=matrice[i][j];
      		check2[i][j]=matrice[i][j];
      	}
      }
      down_check(check1,vect_first,matrice_check);
      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		if(check1[i][j]!=check2[i][j])
      			{
      				mvprintw(5+count,55,"You can move down");
      				count++;
      				j=4; i=4;
      			}
      	}
      }



      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		check1[i][j]=matrice[i][j];
      		check2[i][j]=matrice[i][j];
      	}
      }
      up_check(check1,vect_first,matrice_check);
      for(i=0;i<4;i++)
      {
      	for(j=0;j<4;j++)
      	{
      		if(check1[i][j]!=check2[i][j])
      			{
      				mvprintw(5+count,55,"You can move up");
      				count++;
      				j=4; i=4;
      			}
      	}
      }
}  
void left_check(int **v,int *vect_first,int **matrice_check) // functia verifica daca ne putem misca la stanga
{

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor left_choose si left, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.*/


  int stop;
  int i,j,k;
  int hold_pos;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }
  for(k=0;k<4;k++)
  {
  hold_pos=0;
  stop=0;
  for(i=0;i<4;i++)
  {
    if( v[k][i]!= 0)
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--)
      {
          if(v[k][j]==0)
          {
            v[k][j]=v[k][j+1];
            v[k][j+1]=0;  
            if(v[k][j-1]==0 && j==2)
              hold_pos--;          
          }
          if(v[k][j]==v[k][j+1] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[k][j]*=2;
            v[k][j+1]=0;
          }
          if(v[k][j]==v[k][j+1] && stop==1)
            {
            stop++;
            v[k][j]*=2;
            v[k][j+1]=0;
          }
      }
    }
  }
  }
  k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return ;
  }
  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void right_check(int **v,int *vect_first,int **matrice_check) // functia verifica daca ne putem misca la dreapta
{

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor right_choose si right, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.*/
  int stop;
  int i,j,k;
  int hold_pos;

  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }


  for(k=0;k<4;k++)
  {
  stop=0;
  hold_pos=3;
  for(i=3;i>=0;i--)
  {
    if( v[k][i]!= 0)
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++)
      {
          if(v[k][j]==0)
          {
            v[k][j]=v[k][j-1];
            v[k][j-1]=0;
            if(v[k][j+1]==0 && hold_pos==1)
            hold_pos++;
          }
          if(v[k][j]==v[k][j-1] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[k][j]*=2;
            v[k][j-1]=0;
          }
          if(v[k][j]==v[k][j-1] && stop==1)
          {
            stop++;
            v[k][j]*=2;
            v[k][j-1]=0;
          } 
      }
    }
  }
  }

  k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void down_check(int **v,int *vect_first,int **matrice_check) // functia verifica daca ne putem misca jos
{

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor down_choose si down, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.*/
  int stop;
  int i,j,k;
  int hold_pos;

   for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }


  for(k=0;k<4;k++)
  {
  hold_pos=3;
  stop=0;
  for(i=3;i>=0;i--)
  {
    if( v[i][k]!= 0)
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++)
      {
          if(v[j][k]==0)
          {
            v[j][k]=v[j-1][k];
            v[j-1][k]=0;  
            if(j<=2 && v[j+1][k]==0 && hold_pos==1)
              hold_pos++;          
          }
          if(v[j][k]==v[j-1][k] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[j][k]*=2;
            v[j-1][k]=0;
          }
          if(v[j][k]==v[j-1][k] && stop==1)
            {
            stop++;
            v[j][k]*=2;
            v[j-1][k]=0;
          } 
      }
    }
  }
  }
   k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void up_check(int **v,int *vect_first,int **matrice_check) // functia verifica daca ne putem misca sus
{

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor up_choose si up, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.*/
  int stop;
  int i,j,k;
  int hold_pos;

   for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }

  for(k=0;k<4;k++)
  {
  stop=0;
  hold_pos=0;
  for(i=0;i<4;i++)
  {
    if( v[i][k]!= 0)
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--)
      {
          if(v[j][k]==0)
          {
            v[j][k]=v[j+1][k];
            v[j+1][k]=0;  

            if(j>=1 && v[j-1][k]==0 && hold_pos==2)
              hold_pos--;          
          }
          if(v[j][k]==v[j+1][k] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[j][k]*=2;
            v[j+1][k]=0;
          }
          if(v[j][k]==v[j+1][k] && stop==1)
          {
            stop++;
            v[j][k]*=2;
            v[j+1][k]=0;
          } 
      }
    }

  }
  }
   k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];

} 
void left(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo) //functia de miscare la apasarea LEFT_KEY
{
  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor left_choose si left_check, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.Daca s-a schimbat si se poate efectua miscarea se va genera pe o pozitie aleatoare 2 sau 4.
  Variabila check_undo verifica daca putem reveni la miscarea anterioara, intrucat daca nu am facut nicio miscare nu putem reveni la o alta miscare */
  *check_undo = 1;
  int stop;
  int i,j,k;
  int hold_pos;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }
  for(k=0;k<4;k++)
  {
    stop=0;
  hold_pos=0;
  for(i=0;i<4;i++)
  {
    if( v[k][i]!= 0)
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--)
      {
          if(v[k][j]==0)
          {
            v[k][j]=v[k][j+1];
            v[k][j+1]=0;  
            if(v[k][j-1]==0 && j==2)
              hold_pos--;          
          }
          if(v[k][j]==v[k][j+1] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[k][j]*=2;
            v[k][j+1]=0;
            *sum+=v[k][j];
          }
          if(v[k][j]==v[k][j+1] && stop==1)
            {
            stop++;
            v[k][j]*=2;
            v[k][j+1]=0;
            *sum+=v[k][j];
          }
      }
    }
  }
  }
  k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return ;
  }
  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void right(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo) //functia de miscare la apasarea RIGHT_KEY
{

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor right_choose si right_check, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.Daca s-a schimbat si se poate efectua miscarea se va genera pe o pozitie aleatoare 2 sau 4.
  Variabila check_undo verifica daca putem reveni la miscarea anterioara, intrucat daca nu am facut nicio miscare nu putem reveni la o alta miscare .*/
  *check_undo = 1;
  int stop;
  int i,j,k;
  int hold_pos;

  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }


  for(k=0;k<4;k++)
  {
    stop=0;
  hold_pos=3;
  for(i=3;i>=0;i--)
  {
    if( v[k][i]!= 0)
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++)
      {
          if(v[k][j]==0)
          {
            v[k][j]=v[k][j-1];
            v[k][j-1]=0;
            if(v[k][j+1]==0 && hold_pos==1)
            hold_pos++;
          }
          if(v[k][j]==v[k][j-1] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[k][j]*=2;
            v[k][j-1]=0;
            *sum+=v[k][j];
          }
          if(v[k][j]==v[k][j-1] && stop==1)
          {
            stop++;
            v[k][j]*=2;
            v[k][j-1]=0;
            *sum+=v[k][j];
          } 
      }
    }
  }
  }

  k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void down(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo) //functia de miscare la apasarea DOWN_KEY
{
  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor down_choose si down_check, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.Daca s-a schimbat si se poate efectua miscarea se va genera pe o pozitie aleatoare 2 sau 4.
  Variabila check_undo verifica daca putem reveni la miscarea anterioara, intrucat daca nu am facut nicio miscare nu putem reveni la o alta miscare. */
  *check_undo = 1;
  int stop;
  int i,j,k;
  int hold_pos;

   for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }
  for(k=0;k<4;k++)
  {
    stop=0;
  hold_pos=3;
  for(i=3;i>=0;i--)
  {
    if( v[i][k]!= 0)
    {
      for(j=i+1;(j<=hold_pos && j<=3);j++)
      {
          if(v[j][k]==0)
          {
            v[j][k]=v[j-1][k];
            v[j-1][k]=0;  
            if(j<=2 && v[j+1][k]==0 && hold_pos==1)
              hold_pos++;          
          }
          if(v[j][k]==v[j-1][k] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[j][k]*=2;
            v[j-1][k]=0;
            *sum+=v[j][k];
          }
          if(v[j][k]==v[j-1][k] && stop==1)
            {
            stop++;
            v[j][k]*=2;
            v[j-1][k]=0;
            *sum+=v[j][k];
          } 
      }
    }
  }
  }
   k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void up(int **v,int *vect_first,int **matrice_check,int *sum,int *check_undo) //functia de miscare la apasarea UP_KEY
{  

  /* Pentru a nu ma repeta voi mentiona faptul ca in aceasta functie folosesc acelasi algoritm ca in cazul functiilor up_choose si up_check, insa dupa
  ce facem miscarea la stanga verificam daca s-a produs vreo schimbare prin parcuregerea matricei si cu ajutorul variabilei k. In cazul in care
  nu s-a schimbat nimic (k=16) se iese din functie.Daca s-a schimbat si se poate efectua miscarea se va genera pe o pozitie aleatoare 2 sau 4.
  Variabila check_undo verifica daca putem reveni la miscarea anterioara, intrucat daca nu am facut nicio miscare nu putem reveni la o alta miscare. */
	*check_undo = 1;
  int stop;
  int i,j,k;
  int hold_pos;

   for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      matrice_check[i][j]=v[i][j];
    }
  }

  for(k=0;k<4;k++)
  {
  hold_pos=0;
  stop=0;
  for(i=0;i<4;i++)
  {
    if( v[i][k]!= 0)
    {
      for(j=i-1;(j>=hold_pos && j>=0);j--)
      {
          if(v[j][k]==0)
          {
            v[j][k]=v[j+1][k];
            v[j+1][k]=0;  

            if(j>=1 && v[j-1][k]==0 && hold_pos==2)
              hold_pos--;          
          }
          if(v[j][k]==v[j+1][k] && stop==0)
          {
            hold_pos=i;
            stop++;
            v[j][k]*=2;
            v[j+1][k]=0;
            *sum+=v[j][k];
          }
          if(v[j][k]==v[j+1][k] && stop==1)
          {
            stop++;
            v[j][k]*=2;
            v[j+1][k]=0;
            *sum+=v[j][k];
          } 
      }
    }

  }
  }
   k=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(v[i][j]==matrice_check[i][j])
        {
          k++;
        }
    }
  }
  if(k==16)
  {
   return;
  }

  do
  {
    i=rand()%4; j=rand()%4;
  }
  while(v[i][j]!=0);
  v[i][j] = vect_first[rand()%2];
}
void game_instructions(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo,int *check_undo)  //functia arata cum instructiunile jocului
{
  erase(); // reinitializam ecranul 
  init_pair(1, COLOR_WHITE, COLOR_RED); // initializam culoarea
  bkgd(COLOR_PAIR(1)); // alegem culoarea backgroundului 
  char c; // caracterul citit de la tastatura

  // Instructiuni 
  mvprintw(5,5,"The game will give you an initial 4x4 board, totaling 16 tiles. Two tiles  of 2 or 4 will be placed at random positions on the board.");
  mvprintw(6,59,"Swipe up, down, left, and right to move the tiles across the board. The tiles will slide towards the other end, as long as there is available space.");  
  mvprintw(8,48,"When tiles of the same number   touch during a move, they will combine into one tile carrying the sum of the two  tiles.");
  mvprintw(10,8,"On every move, whether you were able to merge 2 tiles or not, a new tile of 2 or 4 will randomly appear on the board. This is how you get new tiles and  numbers in play.");
  mvprintw(12,17 ,"Continue moving the tiles across the board to increase the      numbers on the tiles. The objective is to reach get a 2048 tile on the board.   This get be achieved by combining two 1024 tiles, coming from two 512 tiles,    merged from two 256 tiles, and so on.");
  attron(A_BOLD); // Se Scrie boldat
  mvprintw(20,10,"Press Q to go back to the menu.");
  attroff(A_BOLD);
  for( ; ; )  //O bucla infinita din care se poate iesi pentru a reveni la meniu doar prin apasarea tasei Q(81)
  {
    c = getch(); // citim caracterul 
    switch(c)
    {
      case 81: // in care utilizatorul apasa pe Q
      {
        erase(); // reinitializam ecranul
        meniu(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo); //ne intoarcem la meniu
        break;
      }
        default:
        break;
    }
  }
    refresh();
}
void prim() // functie de intampinare a utilizatorului 
{
  initscr(); // initializare ecran
  start_color(); // initializam culorile
  init_pair(2,COLOR_WHITE,COLOR_RED); // initializam perechea de culori
  bkgd(COLOR_PAIR(2)); // stabilim background
  attron(COLOR_PAIR(2)); // activam perechea de culori
  curs_set(0); // dispare cursorul
  noecho(); //nu se vede pe ecran ce citim de la tastatura
  keypad(stdscr, TRUE); // activarea citire de la tastatura
  attron(A_BOLD); // scris boldat
  mvprintw(4,28,"2048 Christmas Edition 2017");
  mvprintw(12,30,"Press any key to continue");
  mvprintw(20,15,"I wish you happy holidays and a new year full of success!!");
  getch(); // asteapta pana se citeste de la tastatura
  endwin();
}
void atribuire(int **matrice_undo, int **matrice ) // atribuire matrice_undo pentru undo
{
	int i,j;
	for( i=0 ; i<4 ; i++)
	{
		for( j=0 ; j<4 ; j++)
		{
			matrice_undo[i][j] = matrice[i][j];
		}
	}
}
void meniu(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo, int *check_undo) // functia de afisare a meniului si de navigare in meniu
{
	erase(); 
	int i=1,j;
	int navigheaza=0; // variabila pentru navigarea in meniu
  //int row,col;
	char menu[4][12] = { "New Game" , "Resume Game" , "How to play" , "Quit" }; // functiile din meniu
	initscr(); // initializare ecran
	//getmaxyx(stdscr,row,col); // randuri si coloane maxime
	start_color(); //initializam culorile
  //initializam perechile de culori pe care le vom folosi pentru a deosebi numerele, insa nu avem destule culori
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_WHITE,COLOR_GREEN);
	init_pair(5,COLOR_WHITE,COLOR_YELLOW);
	init_pair(6,COLOR_WHITE,COLOR_CYAN);
	init_pair(7,COLOR_WHITE,COLOR_MAGENTA);
	init_pair(8,COLOR_WHITE,COLOR_WHITE);
  curs_set(0); // dispare cursorul
  noecho(); // nu se vede pe ecran ce citim de la tastatura
  keypad(stdscr, TRUE); // activare citire de la tastatura
	bkgd(COLOR_PAIR(1));  // stabilim background
	attron(COLOR_PAIR(1)); // activam perechea de culoare

  //Afisam meniul cu instructiunile de navigare in acesta
    attron(A_STANDOUT);
    mvprintw( 9 , 30 , "%s", menu[0]);
    attroff(A_STANDOUT);
    while( i < 4 )
    {
    	mvprintw( 9+i , 30 , "%s" , menu[i] );
    	i++;
    }
    mvprintw(16, 10, "Press on UP / DOWN keys to navigate through the menu");
    mvprintw(17, 7, "In order to select the option, please press the ENTER button");
    refresh();
    
    i=0;
    navigheaza = getch(); // Asteapta comanda de navigare in meniu
   	for( ; ; )
   	{
   		mvprintw( i+9 , 30 , "%s", menu[i]);
   		switch (navigheaza)
   		{
   			case KEY_UP:
   				i--;
   				if(i < 0)
   				{
   					i = 3;
   				}
   				break;
   			case KEY_DOWN:
   				i++;
   				if(i > 3)
   				{
   					i = 0;
   				}
   				break;
   			case 10: // Pentru ENTER(10) pentru fiecare functie din meniu programul apeleaza cate o functie, variabila start e folosita pentru a verifica daca se poate folosi functia Resume Game
   				if(strcmp(menu[i] , "New Game") == 0 && *start == 0)
   				{
   					erase();
   					new_game(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);
            break;
   				}
          else
          if(strcmp(menu[i], "New Game") == 0 && *start == 1)
          {
            erase();
            for(i=0;i<4;i++)
            {
              for(j=0;j<4;j++)
              {
                matrice[i][j]=0;
              }
            }
            srand(time(NULL));
             matrice[rand()%4][rand()%4] = vect_first[rand()%2];
           do
          {
              i=rand()%4; j=rand()%4;
           }
           while(matrice[i][j]!=0);
            matrice[i][j] = vect_first[rand()%2];
            *sum = 0;
            new_game(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);

            break;
          }
   				else 
   				if(strcmp(menu[i] , "Resume Game") == 0 && *start == 1)
   				{
            erase();
            new_game(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);
            break;
   				}
   				else
   				if(strcmp(menu[i] , "How to play") == 0)
   				{
            game_instructions(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);
            break;
   				}
   				else
   				if(strcmp(menu[i] , "Quit") == 0)
   				{
   					endwin();
   					exit(0);
   				}		
   		}
  		attron(A_STANDOUT);
        mvprintw( i+9 , 30 , "%s", menu[i]);
        attroff(A_STANDOUT);
        refresh();
        navigheaza = getch();
   	}

    endwin();
}
void show_matrix_empty() // functia de afisare a tabelei goala
{
  int i,j;
  initscr();
  start_color();
  curs_set(0);
  noecho();
    keypad(stdscr, TRUE);
    attron(COLOR_PAIR(3));
    for(j=3;j<28;j+=5)
    {
      for(i=20;i<52;i++)
      {
        mvaddch(j,i,ACS_HLINE);
      }
    }
    for(j=20;j<=52;j+=8)
    {
      for(i=3;i<23;i++)
      {
        mvaddch(i,j,ACS_VLINE);
      }
    }

    mvaddch(3,20,ACS_ULCORNER);
    mvaddch(8,20,ACS_LTEE);
    mvaddch(13,20,ACS_LTEE);
    mvaddch(18,20,ACS_LTEE);
    mvaddch(23,20,ACS_LLCORNER);
    mvaddch(3,28,ACS_TTEE);
    mvaddch(3,36,ACS_TTEE);
    mvaddch(3,44,ACS_TTEE);
    mvaddch(3,52,ACS_URCORNER);
    mvaddch(8,52,ACS_RTEE);
    mvaddch(13,52,ACS_RTEE);
    mvaddch(18,52,ACS_RTEE);
    mvaddch(23,52,ACS_LRCORNER);
    mvaddch(23,44,ACS_BTEE);
    mvaddch(23,36,ACS_BTEE);
    mvaddch(23,28,ACS_BTEE);
    mvaddch(8,28,ACS_PLUS);
    mvaddch(8,36,ACS_PLUS);
    mvaddch(8,44,ACS_PLUS);
    mvaddch(13,28,ACS_PLUS);
    mvaddch(13,36,ACS_PLUS);
    mvaddch(13,44,ACS_PLUS);
    mvaddch(18,28,ACS_PLUS);
    mvaddch(18,36,ACS_PLUS);
    mvaddch(18,44,ACS_PLUS);
    attroff(COLOR_PAIR(3));
    char timp[50];
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    strftime(timp, sizeof(timp), "%c", tm);
    mvprintw(1,55,"Current Date and Time:");
    mvprintw(2,55,"%s",timp);
    endwin();
}
void show_matrix_full(int **matrice,char *var,int *sum) // functia de afisare a tabelei cu numere
{
  int i,j,k;
  for(i=0;i<4;i++)
      {
        for(j=0;j<4;j++)
        {
          if(matrice[i][j] == 0)
          {
          	 attron(COLOR_PAIR(8));
          	mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,"       ");
            attroff(COLOR_PAIR(8));
          }
          else
          if(matrice[i][j] == 2)
          {
            attron(COLOR_PAIR(2));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(2));
          }
          else
          if (matrice[i][j] == 4)
          {
          	 attron(COLOR_PAIR(5));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(5));
          }
          else
          if (matrice[i][j] == 8)
          {
          	attron(COLOR_PAIR(7));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(7));
          }
          else
          if (matrice[i][j] == 16)
          {
          	attron(COLOR_PAIR(4));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(4));
          }
          else
          if (matrice[i][j] == 32)
          {
          	attron(COLOR_PAIR(3));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(3));
          }
          else
          if (matrice[i][j] == 64 )
           {
           	attron(COLOR_PAIR(1));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(1));
           }
           else
           if (matrice[i][j] == 128)
           {
           	attron(COLOR_PAIR(6));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(6));
           }
           else
           if (matrice[i][j] == 256)
           {
           	attron(COLOR_PAIR(4));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(5));
           }
           else
           if (matrice[i][j] == 512)
           {
           	attron(COLOR_PAIR(5));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(5));
           }
           else
           if (matrice[i][j] == 1024)
           {
           	attron(COLOR_PAIR(7));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(7));
           }
           else
           if (matrice[i][j] == 2048)
           {
           	attron(COLOR_PAIR(2));
            sprintf(var,"%d",matrice[i][j]);
            mvprintw(4+i*5,21+8*j,"       ");
            mvprintw(5+i*5,21+8*j,"       ");
            mvprintw(7+i*5,21+8*j,"       ");
            mvprintw(6+i*5,21+8*j,var);
            for(k=strlen(var);k<7;k++)
            	mvprintw(6+i*5,21+8*j+k," ");
            attroff(COLOR_PAIR(2));
           }
        }
      }
     mvprintw(1,30,"Merry Christmas!!");
     mvprintw(3,55,"Points:");
     mvprintw(4,55,"%d",*sum);
     mvprintw(18,55,"If you want to return to");
     mvprintw(19,55,"your last move press U");
     mvprintw(20,55,"If you want to go back to");
     mvprintw(21,55,"the menu press Q");
      refresh();
}
void new_game(int *vect_first,int *vect_col,int *vect_lin,char *var,int **matrice,int **matrice_check,int *sum,int **check1,int **check2,int *start,int **matrice_undo,int *check_undo) //functia pentru joc
{

  int sum_check; 
  int check=1;
  int i,j;
  int miscare;
  //int row,col;
  if(*start == 0) // daca jocul nu a inceput
  {
  srand(time(NULL)); // generare mereu de numere noi
  matrice[rand()%4][rand()%4] = vect_first[rand()%2]; // generare de numere(2 sau 4) pe pozitii aleatoare
  do
  {
    i=rand()%4; j=rand()%4; // generare de numere(2 sau 4) pe pozitii aleatoare
  }
  while(matrice[i][j]!=0);
  matrice[i][j] = vect_first[rand()%2];
  *start=1; // a pornit
  }
  for( ; ; )
    {
     show_matrix_empty(); // afiseaza matricea goala
     show_matrix_full(matrice,var,sum); // afiseaza matricea cu numere 
     show_available_moves(check1,check2,matrice,vect_first,matrice_check); //afiseaza miscarile valabile 
     halfdelay(100); // asteapta 10 secunde, in caz ca utilizatorul nu a dat nicio comanda, jocul va face cea mai buna mutare automata
     miscare = getch(); // asteapta comanda de la utilizatator
     if(miscare!=ERROR) // daca utilizatorul da o comanda
      {
        switch(miscare) /* in functie de comanda respectiva, programul executa o miscare la stanga, la dreapta, in sus, in jos
        				 si in caz ca utilizatorul apasa Q se revine la meniu, iar daca utilizatorul apasa U ( UNDO ) se revine
        				 la miscarea anterioara */
      {

        case KEY_LEFT:
          erase();
          show_matrix_empty();
          atribuire(matrice_undo,matrice);
          left(matrice,vect_first,matrice_check,sum,check_undo);
          show_matrix_full(matrice,var,sum);
          break;
        case KEY_RIGHT:
          erase();
          show_matrix_empty();
          atribuire(matrice_undo,matrice);
          right(matrice,vect_first,matrice_check,sum,check_undo);
          show_matrix_full(matrice,var,sum);
          break;
        case KEY_DOWN:
          erase();
          show_matrix_empty();
          atribuire(matrice_undo,matrice);
          down(matrice,vect_first,matrice_check,sum,check_undo);
          show_matrix_full(matrice,var,sum);
          break;
        case KEY_UP:
          erase();
          show_matrix_empty();
          atribuire(matrice_undo,matrice);
          up(matrice,vect_first,matrice_check,sum,check_undo);
          show_matrix_full(matrice,var,sum);
          break;
        case 81:
          erase();
          meniu(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);
          break;
        case 85:
         if(*check_undo == 1)
          {
          erase();
          new_game(vect_first,vect_col,vect_lin,var,matrice_undo,matrice_check,sum,check1,check2,start,matrice,check_undo);
      	  }
          break;
      }
    }
    else // daca utilizatorul nu da o comanda 
    {
      erase();
      show_matrix_empty();
      atribuire(matrice_undo,matrice);
      choose_alone(check1,check2,matrice,vect_first,matrice_check,sum,check_undo); // se construieste matricea cea mai buna
      show_matrix_full(matrice,var,sum); // se afiseaza
    } 
    refresh();

    // Folosim variabilele sum_check si check pentru a ne da seama daca jocul s-a terminat
    sum_check = *sum;
     check = 1;
   for(i=0;i<4;i++)
    {
      for(j=0;j<4;j++)
      {
        if(matrice[i][j]==0)
          check = 0;
      }
    }
    if ( (check ==1) && (sum_check == left_choose(check2,vect_first,matrice_check,sum_check) ) && (sum_check == right_choose(check2,vect_first,matrice_check,sum_check) ) && (sum_check == down_choose(check2,vect_first,matrice_check,sum_check) ) && (sum_check == up_choose(check2,vect_first,matrice_check,sum_check) ))
    {
      halfdelay(50);
      erase();
      attron(COLOR_PAIR(2));
      attron(A_BOLD);
      bkgd(COLOR_PAIR(2));
      mvprintw(12,30,"GAME OVER !!");
      mvprintw(13,20,"...but i still wish you happy holidays!!");
      mvprintw(14,25,"Press any key to exit");
      getch();
      endwin();
      exit(0);
    }
    for(i=0;i<4;i++)
    {
    	for(j=0;j<4;j++)
    	{
    		if(matrice[i][j] == 2048)
    		{
    			erase();
    			attron(COLOR_PAIR(2));
      			attron(A_BOLD);
      			bkgd(COLOR_PAIR(2));
      			mvprintw(12,23,"Congratulations ! YOU win !");
      			mvprintw(13,25,"Press any key to exit");
      			getch();
      			endwin();
      			exit(0);
    		}
    	}
    }
    }

    endwin();
}
int main(int argc, char *argv[])
{
  int i;
  int *check_undo;
  check_undo=(int *)malloc(sizeof(int));
  *check_undo=0;
  int *vect_first;
  vect_first=(int *)malloc(2*sizeof(int)); vect_first[0]=2; vect_first[1]=4; //punem 2 sau 4 la inceput
  int *vect_col;
  vect_col=(int *)malloc(4*sizeof(int));  vect_col[0]=21; vect_col[1]=29; vect_col[2]=37; vect_col[3]=45;  // de unde incepe pe sdtscr coloana
  int *vect_lin;
  vect_lin=(int *)malloc(4*sizeof(int)); vect_lin[0]=6; vect_lin[1]=11; vect_lin[2]=16; vect_lin[3]=21; // de unde incepe pe sdtscr coloana
  char *var;
  var=(char *)malloc(4*sizeof(char)); // ne ajuta sa scriem pe stdscr
  int **matrice; // matricea principala
  matrice = (int **)malloc(4 * sizeof(int *)); 
  for(i=0;i<4;i++)
  {
    matrice[i]= (int *)malloc(4 * sizeof(int ));
  }
  int **matrice_check; // matricea de verificare
  matrice_check = (int **)malloc(4 * sizeof(int *));
  for(i=0;i<4;i++)
  {
    matrice_check[i]= (int *)malloc(4 * sizeof(int ));
  }
  int *sum; // scorul general
  sum=(int *)malloc(sizeof(int));
  *sum=0;
  int **check1; //matrice verificare 1
	check1=(int **)malloc(4*sizeof(int *));
	for(i=0;i<4;i++)
		check1[i]=(int *)malloc(4*sizeof(int));
	 int **check2; // matrice verificare 2
	check2=(int **)malloc(4*sizeof(int *));
	for(i=0;i<4;i++)
		check2[i]=(int *)malloc(4*sizeof(int));
  int *start = (int *)malloc(sizeof(int)); // variabila pentru a verifica daca am inceput sau nu jocul
  *start=0;
  prim();
  int **matrice_undo;
  matrice_undo = (int **)malloc(4*sizeof(int *));
  for(i=0;i<4;i++)
  {
  	matrice_undo[i]=(int *)malloc(4*sizeof(int ));
  }

  meniu(vect_first,vect_col,vect_lin,var,matrice,matrice_check,sum,check1,check2,start,matrice_undo,check_undo);



  // Eliberarea de memorie

  free(vect_first);
  free(vect_col);
  free(vect_lin);
  free(var);
  for(i=0;i<4;i++)
  	free(matrice[i]);
  free(matrice);
  for(i=0;i<4;i++)
  	free(matrice_check[i]);
  free(matrice_check);
  free(sum);
  for(i=0;i<4;i++)
  	free(check1[i]);
  free(check1);
  for(i=0;i<4;i++)
  	free(check2[i]);
  free(check2);
  free(start);
  free(check_undo);
  for(i=0;i<4;i++)
  	free(matrice_undo[i]);
  free(matrice_undo);

  return 0;
}
