#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "arbre.h"

/* 

Pour toutes les fonctions dans ce fichier, je prends la convention suivante :
Pour isPere, si on a la valeur 1, celà signifie qu'il n'a pas de fils
Si la valeur vaut 0, il a un fils

Ainsi nous pouvons utiliser les fonctions avec ou sans fils.

*/

int Digit(char* message, Noeud* noeud, int isPere){
  Noeud* digit;
  int retourner=1;

  if (*message >= 0x30 && *message <= 0x39){
    retourner=0;
    if (isPere){
      digit=Creer_fils(noeud);
    }
    else {
      digit=Creer_frere(noeud);
    }
    Set_noeud(digit, "__digit", message, 1);
  }
  return retourner;
}

int Htab(char* message, Noeud* noeud, int isPere){
  Noeud* htab;
  int retourner=1;

  if (*message==0x09){
    retourner=0;
    if (isPere){
      htab=Creer_fils(noeud);
    }
    else {
      htab=Creer_frere(noeud);
    }
    Set_noeud(htab, "__htab", message, 1);
  }
  return retourner;
}

int Lf(char* message, Noeud* noeud, int isPere){
  Noeud* lf;
  int retourner=1;

  if (*message==0x0A){
    retourner=0;
    if (isPere){
      lf=Creer_fils(noeud);
    }
    else {
      lf=Creer_frere(noeud);
    }
    Set_noeud(lf, "__lf", message, 1);
  }
  return retourner;
}

int Sp(char* message, Noeud* noeud, int isPere){
  Noeud* sp;
  int retourner=1;

  if (*message==0x20){
    retourner=0;
    if (isPere){
      sp=Creer_fils(noeud);
    }
    else {
      sp=Creer_frere(noeud);
    }
    Set_noeud(sp, "__sp", message, 1);
  }
  return retourner;
}

/* Fonctions plus "Haut niveau" */

int Nombre (char* message, Noeud* noeud){
  Noeud* nombre=Creer_frere(noeud);
  Noeud* temp;
  int retourner=0;
  Set_noeud(nombre, "nombre", message, 0);
  if (Digit(message, nombre, 1)){
    retourner=1;
    free(nombre); //Si ce n'est pas un nombre, on efface tout de suite le noeud 
    noeud->frere=NULL;
  }
  else {
    temp=nombre->fils;
    nombre->taille=(nombre->taille)+1;
    message++;
    while (!Digit(message, temp, 0)){
      message++;
      nombre->taille=(nombre->taille)+1;
      temp=temp->frere;
    }
  }
  return retourner;
}

int Ponct(char* message, Noeud* noeud, int IsPere){
  Noeud* ponct;
  int retourner=1;

  if (*message==',' || *message=='.' || *message=='!' || *message=='?' || *message==':'){
    retourner=0;
    if (IsPere){
      ponct=Creer_fils(noeud);
    }
    else {
      ponct=Creer_frere(noeud);
    }
    Set_noeud(ponct, "ponct", message, 1);

  }
  return retourner;
}

int Separateur(char* message, Noeud* noeud, int IsPere){
  int retourner=1;
  Noeud* sep;
  if (IsPere){
    sep=Creer_fils(noeud);
  }
  else {
    sep=Creer_frere(noeud);
  }

  Set_noeud(sep, "separateur", message, 0);
  if (!Sp(message, sep, 1) || !Htab(message, sep, 1) || *message=='-' || *message=='_'){
    retourner=0;
    sep->taille=sep->taille+1;
  }
  else {
    free(sep);
    if (IsPere){
      noeud->fils=NULL;
    }
    else {
      noeud->frere=NULL;
    }
  }
  return retourner;
}

int Fin(char* message, Noeud* noeud, int isPere){
  int retourner=0;
  int index=0;
  char str[4]="fin";
  Noeud* fin;

  for (index=0; index<3; index++){
    if ((*message+index)!=(*str+index)){
      retourner=1;
    }
    else {
      if (isPere){
        fin=Creer_fils(noeud);
      } 
      else {
        fin=Creer_frere(noeud);
      }
      Set_noeud(fin, "__fin", message, 1);
    }
  }
  return retourner;
}