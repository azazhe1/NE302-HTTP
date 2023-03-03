#ifndef _FONCTIONS_
#define _FONCTIONS_

#include "arbre.h"

int Digit(char* message, Noeud* noeud, int isPere);
int Htab(char* message, Noeud* noeud, int isPere);
int Lf(char* message, Noeud* noeud, int isPere);
int Sp(char* message, Noeud* noeud, int isPere);
int Nombre (char* message, Noeud* noeud);
int Ponct(char* message, Noeud* noeud, int IsPere);
int Separateur(char* message, Noeud* noeud, int IsPere);
int Fin(char* message, Noeud* noeud, int isPere);

#endif