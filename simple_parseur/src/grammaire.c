#include "arbre.h"
#include "fonctions.h"

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
    int resultat =0;
    Set_noeud(mot,"mot",message,0);
    if(Alpha(message,mot,1)){
        free(mot);//Si ce n'est pas un mot, on efface tout de suite le noeud
        noeud->frere=NULL;
        resultat =1;
    }else{
        temp=mot->fils;
        message++;
        mot->taille=(mot->taille)+1;
        while(Alpha(message,temp,0)==0){
            message++;
            mot->taille=(mot->taille)+1;
            temp=temp->frere;
        }
        Separateur(message, mot, 0); // On traite également le séparateur
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
        message = message + Message->fils->frere->taille+1;
        Ponct(message,Message->fils->frere->frere,0);
        message = message + Message->fils->frere->taille;
        Mot(message,Message->fils->frere->frere->frere);
        Afficher_noeud(Message);
    }
    //Problème de suppression si le noeud n'est pas existant
    //Noter le fait qu'un passage par Mot crée désormais 2 frères (Alpha et Séparateur)
    Supprimer_arbre(Message->fils->frere->frere->frere->frere,Message->fils->frere->frere->frere->frere->frere,1,0);
    Supprimer_arbre(Message->fils->frere->frere->frere,Message->fils->frere->frere->frere->frere,1,0);
    Supprimer_arbre(Message->fils->frere->frere,Message->fils->frere->frere->frere,1,0);
    Supprimer_arbre(Message->fils->frere,Message->fils->frere->frere,1,0);
    Supprimer_arbre(Message->fils,Message->fils->frere,1,1);
    Supprimer_arbre(Message,Message->fils,1,1);
    free(Message);

}


int main(){
    //char *message ="startVKiMupi-.4 LCTKq-.fin";
    char *message ="startO ,DCvWahPeh	.q .UC-,Ka-:itN	:!fin"; //test3.txt
    Test_message(message);

}