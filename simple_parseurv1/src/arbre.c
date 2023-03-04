#include "arbre.h"

//Pour supprimer les noeud il faut que ce soit les fonction qui les gères

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

Noeud *Creer_fils(Noeud* pere){
    Noeud* nouveau = Creer_Noeud();
    pere->fils = nouveau;
    nouveau->niveau=pere->niveau +1;

    return nouveau;
}
Noeud *Creer_frere(Noeud* grand_frere){
    Noeud* nouveau = Creer_Noeud();
    grand_frere->frere = nouveau;
    nouveau->niveau=grand_frere->niveau;

    return nouveau;
}


void Set_noeud(Noeud* noeud, char* etiquette_noeud, char* valeur_noeud, int taille_valeur){
    noeud->etiquette=etiquette_noeud;
    noeud->valeur=valeur_noeud;
    noeud->taille=taille_valeur;

}

void Afficher_noeud(Noeud* noeud){//Prend en argument le Noeud à afficher
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

void Supprimer_arbre(Noeud* noeud){//Prend en argument soit le pere(Is_pere =1)/soit le grand_frere(Is_pere=0) , le noeud a supp, le level du noeud a supprimer

    if(noeud->fils!=NULL){
        Supprimer_arbre(noeud->fils);
    }
    if(noeud->frere!=NULL){
        
        Supprimer_arbre(noeud->frere);
    }
    free(noeud);
}
/*
int main(){
    Noeud* head=Creer_Noeud(); 
    Set_noeud(head,"message","startVKiMupi-.4 LCTKq-.fin",strlen("startVKiMupi-.4 LCTKq-.fin"));

    Noeud* fils=Creer_fils(head);
    Set_noeud(fils,"debut","startVKiMupi-.4 LCTKq-.fin",5);

    Noeud * frere = Creer_frere(fils);
    Set_noeud(frere,"mot","VKiMupi-.4 LCTKq-.fin",8);

    Noeud* fils_1 = Creer_fils(frere);
    Set_noeud(fils_1,"__alpha","VKiMupi-.4 LCTKq-.fin",1);

    Noeud* frere_1 = Creer_frere(fils_1);
    Set_noeud(frere_1,"__alpha","KiMupi-.4 LCTKq-.fin",1);

    Noeud* frere_2 = Creer_frere(frere_1);
    Set_noeud(frere_2,"__alpha","iMupi-.4 LCTKq-.fin",1);

    Noeud* frere_3 = Creer_frere(frere_2);
    Set_noeud(frere_3,"__alpha","Mupi-.4 LCTKq-.fin",1);

    Noeud* frere_4 = Creer_frere(frere_3);
    Set_noeud(frere_4,"__alpha","upi-.4 LCTKq-.fin",1);

    Noeud* frere_5 = Creer_frere(frere_4);
    Set_noeud(frere_5,"__alpha","pi-.4 LCTKq-.fin",1);

    Noeud* frere_6 = Creer_frere(frere_5);
    Set_noeud(frere_6,"__alpha","i-.4 LCTKq-.fin",1);

    Noeud* frere_7 = Creer_frere(frere_6);
    Set_noeud(frere_7,"__alpha","-.4 LCTKq-.fin",1);

    Afficher_noeud(head);
    
    Supprimer_arbre(fils,fils->frere,fils->niveau,0);
    Supprimer_arbre(head,head->fils,head->niveau+1,1);
    free(head);
    
    //free(fils);
    //free(frere);
    //free(fils_1);
    //free(frere_1);
    //free(frere_2);
    //free(frere_3);
    //free(frere_4);
    //free(frere_5);
    //free(frere_6);
    //free(frere_7);
    
}*/
