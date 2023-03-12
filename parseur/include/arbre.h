#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file arbre.h 
 * @brief Définition de notre structure qui va implémenter notre arbre
 * @author VINCENT MICHEL RENIER 
 * @version 1.0
 */
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
void Supprimer_arbre(Noeud* noeud);