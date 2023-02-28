#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

/* Briques de base : */

int Digit(char* message){
  int retourner=1;

  if (*message >= 0x30 && *message <= 0x39){
    retourner=0;
  }
  return retourner;
}

int Htab(char* message){
  int retourner=1;

  if (*message==0x09){
    retourner=0;
  }
  return retourner;
}

int Lf(char* message){
  int retourner=1;

  if (*message==0x0A){
    retourner=0;
  }
  return retourner;
}

int Sp(char* message){
  int retourner=1;

  if (*message==0x20){
    retourner=0;
  }
  return retourner;
}

/* Fonctions plus "Haut niveau" */

int Nombre (char* message){
  int resultat=1;
  int retourner=1;

  resultat = Digit(message);
  while (!resultat){
    resultat=Digit(message);
  }
  return retourner;
}

int Ponct(char* message){
  int retourner=1;

  if (*message==',' || *message=='.' || *message=='!' || *message=='?' || *message==':'){
    retourner=0;
  }
  return retourner;
}

int separateur(char* message){
  int retourner=1;

  if (!Sp(message) || !Htab(message) || *message=='-' || *message=='_'){
    retourner=0;
  }
  return retourner;
}

int fin(char* message){
  int retourner=0;
  int index=0;
  char fin[4]="fin";
  
  for (index=0; index<3; index++){
    if ((*message+index)!=(*fin+index)){
      retourner=1;
    }
  }
  return retourner;
}