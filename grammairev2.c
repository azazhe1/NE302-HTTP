#include "grammairev2.h"

//message = debut 2*( mot ponct /nombre separateur ) [ponct] fin LF
int Test_message(char *message,Noeud *Message){
    Noeud * fils;
    Noeud * frere_1;
    Noeud * frere_2;
    Noeud * frere_3;
    Noeud * frere_4;
    Noeud * frere_5;
    
    //debut
    fils=Creer_fils(Message);
    if(Test_debut(message,fils)){
        message = message +5;
    }else{
        free(fils);
        Message->fils = NULL;
        return 0;
    }
    //mot
    frere_1 = Creer_frere(fils);
    if(Test_mot(message,frere_1)){
        message = message +frere_1->taille;
    }else{
        free(frere_1);
        fils->frere=NULL;
        return 0;
    }

    
    
    return 1;   
}

int Test_debut(char *message,Noeud *noeud){
    int resultat=1;
    char *debut="start";
    for(int i=0;i<5;i++){
        if(*(message+i)!=*(debut+i)){
            resultat = 0;
        }
    }
    Set_noeud(noeud,"debut",message,5);
    return resultat;
}

int Test_mot(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille_mot= 0;
    while(Test_Alpha(message,frere)){
        message = message+1;
        fils=frere;
        frere = Creer_frere(frere);
        taille_mot++;
    }
    if(taille_mot<1){
        free(fils);
        return 0;
    }else{
        //Faire ponct avant!!!

        free(frere);
        fils->frere=NULL;
        Set_noeud(noeud,"mot",message-taille_mot,taille_mot);
    }

    return 1;
}

int Test_Alpha(char *message,Noeud *noeud){
    int resultat=0;
    if(((*message>=0x61)&&(*message<=0x7A))||((*message>=0x41)&&(*message<=0x5A))){
        Set_noeud(noeud,"__alpha",message,1);
        resultat =1;
    }
    return resultat;
}

int Test_ponct(char *message,Noeud noeud){
    int resultat =0;

} 

int main(){
    char *message ="starta";
    Noeud *Message = Creer_Noeud();
    Set_noeud(Message,"message",message,strlen(message));
    if(Test_message(message,Message)){
        Afficher_noeud(Message);
    }
    Supprimer_arbre(Message);

}