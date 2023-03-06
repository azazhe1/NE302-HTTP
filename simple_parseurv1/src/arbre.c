#include "arbre.h"

/**
 * @file arbre.c
 * @brief Gère la création et la suppression d'arbre, \n
 * la création de fils et frère et affiche un arbre à parir d'un noeud.  
 * @author VINCENT MICHEL RENIER 
 * @version 1.0
 */

/**
 * @brief Créer un noeud
 * 
 * @return \b Noeud* retourne notre noeud 
 */
Noeud* Creer_Noeud(){
    Noeud* nouveau= (Noeud*)malloc(sizeof(Noeud));
    nouveau->etiquette=NULL;
    nouveau->valeur=NULL;
    nouveau->taille=0;
    nouveau->niveau=0;
    nouveau->fils=NULL;
    nouveau->frere=NULL;

    return nouveau;
    
}

/**
 * @brief créer un fils à un noeud donné
 * 
 * @param pere: le père de notre futur noeud
 * 
 * @return \b Noeud* retourne le fils
 */
Noeud *Creer_fils(Noeud* pere){
    Noeud* nouveau = Creer_Noeud();
    pere->fils = nouveau;
    nouveau->niveau=pere->niveau +1;

    return nouveau;
}

/**
 * @brief créer un frère à un noeud donné
 * 
 * @param grand_frere: le frère de notre futur noeud
 * 
 * @return \b Noeud* retourne le frère
 */
Noeud *Creer_frere(Noeud* grand_frere){
    Noeud* nouveau = Creer_Noeud();
    grand_frere->frere = nouveau;
    nouveau->niveau=grand_frere->niveau;

    return nouveau;
}

/**
 * @brief Moddifie les valeurs d'un noeud, lui associe son etiquette, le pointeur vers le string associé et la taille du string 
 * 
 * @param noeud: le noeud à modifier 
 * @param etiquette_noeud: l'etiquette à associer 
 * @param valeur_noeud: le pointeur vers le string à lire 
 * @param taille_valeur: la taille du string 
 */
void Set_noeud(Noeud *noeud, char* etiquette_noeud, char* valeur_noeud, int taille_valeur){
    noeud->etiquette=etiquette_noeud;
    noeud->valeur=valeur_noeud;
    noeud->taille=taille_valeur;

}

/**
 * @brief Affiche récursivement tout un arbre à partir d'un noeud
 * 
 * @param noeud: le sommet de l'arbre à partir du quel on doit afficher
 */
void Afficher_noeud(Noeud* noeud){
    for(int i =0;i<noeud->niveau;i++){
        printf("\t");
    }
    printf("%s: ",noeud->etiquette);

    for(int i=0;i<(noeud->taille);i++){
        printf("%c",*(noeud->valeur+i));
    }
    printf("\n");

    if((noeud->fils)!=NULL){
        Afficher_noeud(noeud->fils);
    }
    if((noeud->frere)!=NULL){
        Afficher_noeud(noeud->frere);
    }
}

/**
 * @brief Supprime récursivement un tout un arbre à partir d'un noeud
 * 
 * @param noeud: le sommet de l'arbre à partir du quel on doit supprimer
 */
void Supprimer_arbre(Noeud* noeud){

    if(noeud->fils!=NULL){
        Supprimer_arbre(noeud->fils);
    }
    if(noeud->frere!=NULL){
        
        Supprimer_arbre(noeud->frere);
    }
    free(noeud);
}

