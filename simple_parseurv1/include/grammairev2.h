#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

int Test_message(char *message,Noeud *Message);
int Test_debut(char *message,Noeud *noeud);
int Test_mot(char *message,Noeud *noeud);
int Test_Alpha(char *message,Noeud *noeud);
int Test_ponct(char *message,Noeud* noeud);
int Test_separateur(char *message, Noeud *noeud);
int Test_htab(char *message,Noeud * noeud);
int Test_sp(char *message,Noeud * noeud);
int Test_nombre(char *message,Noeud *noeud);
int Test_digit(char *message,Noeud * noeud);
int Test_fin(char *message,Noeud *noeud);
int Test_lf(char *message,Noeud *noeud);
//int Alpha(char *message, Noeud* noeud, int Is_pere);
//int Mot(char *message, Noeud *noeud);