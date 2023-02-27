#include "arbre.h"

int Alpha(char *message, Noeud* noeud, int Is_pere){
    Noeud *alpha;
    int resultat=1;
    if((*message>=0x41)&&(*message<=0x5A)){
        if(Is_pere){
            alpha=Creer_fils(noeud);
        }else{
            alpha=Creer_frere(noeud);
        }
        Set_noeud(alpha,"__alpha",message,1);
        resultat =0;
    }else if((*message>=0x61)&&(*message<=0x7A)){
        if(Is_pere){
            alpha=Creer_fils(noeud);
        }else{
            alpha=Creer_frere(noeud);
        }
        Set_noeud(alpha,"__alpha",message,1);
        resultat =0;
    }
    return resultat;
}

int Mot(char *message, Noeud *noeud){
    Noeud *mot=Creer_frere(noeud);
    Noeud *temp;
    Noeud *avant;
    int resultat =0;
    Set_noeud(mot,"mot",message,0);
    if(Alpha(message,mot,1)){
        resultat =1;
    }else{
        temp=mot->fils;
        message++;
        avant=temp;
        mot->taille=(mot->taille)+1;
        while(Alpha(message,temp,0)==0){
            message++;
            mot->taille=(mot->taille)+1;
            avant=temp;
            temp=temp->frere;
        }
        avant->frere=NULL;
    }
    return resultat;
}

int Test_debut(char *message,Noeud *noeud){
    char *p="start";
    int resultat =0;
    Noeud *debut;
    debut=Creer_fils(noeud);
    Set_noeud(debut,"debut",message,5);
    for(int i=0;i<5;i++){
        if(*(p+i)!=*(message+i)){
            resultat = 1;
        }
    }
    
    return resultat;

}

void Test_message(char *message){
    Noeud *Message = Creer_Noeud();
    Set_noeud(Message,"message",message,strlen(message));
    if(Test_debut(Message->valeur,Message)){
        printf("None\n");
    }else{
        message = message + Message->fils->taille;
        Mot(message,Message->fils);
        Afficher_noeud(Message);
    }
    
    Supprimer_arbre(Message->fils,Message->fils->frere,1,0);
    Supprimer_arbre(Message,Message->fils,1,1);
    free(Message);

}


int main(){
    char *message ="startVKiMupi-.4 LCTKq-.fin";
    Test_message(message);

}