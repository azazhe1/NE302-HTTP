#ifndef _ARBRE_
#define _ARBRE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Noeud{
    char *etiquette;
    char *valeur;

    int taille;
    int niveau;

    struct Noeud* fils;
    struct Noeud* frere;



}Noeud;

Noeud* Creer_Noeud();
Noeud *Creer_fils(Noeud* pere);
Noeud *Creer_frere(Noeud* grand_frere);
void Set_noeud(Noeud* noeud, char* etiquette_noeud, char* valeur_noeud, int taille_valeur);
void Afficher_noeud(Noeud* noeud);
void Supprimer_arbre(Noeud* pere, Noeud* noeud, int level, int Is_pere);

#endif
