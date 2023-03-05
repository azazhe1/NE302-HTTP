#include "grammairev2.h"



int main(int argc, char **argv){
    FILE *fp;
    char message[1000];
    if(argc!=2){
        printf("Usage: abnf <file>\n");
        exit(EXIT_FAILURE);
    }
    fp=fopen(argv[1],"r");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%[^\n]%*c\n",message);    
    strcat(message,"\n");
    Noeud *Message = Creer_Noeud();
    Set_noeud(Message,"message",message,strlen(message));
    if(Test_message(message,Message)){
        printf("remaining ##\n");
        Afficher_noeud(Message);
    }
    Supprimer_arbre(Message);

}


//message = debut 2*( mot ponct /nombre separateur ) [ponct] fin LF
int Test_message(char *message,Noeud *Message){
    Noeud * fils;
    Noeud * frere_1;
    Noeud * frere_2;
    Noeud * frere_3;
    Noeud * frere_4;
    int taille =0;
    int fin=1;
    //debut
    fils=Creer_fils(Message);
    if(Test_debut(message,fils)){
        message = message +5;
    }else{
        free(fils);
        Message->fils = NULL;
        return 0;
    }
    
    frere_1 = Creer_frere(fils);
    frere_2=frere_1;
    while(fin){
        if(Test_mot(message,frere_2)){//mot
            message = message + frere_2->taille;
            frere_1=frere_2;
            frere_2=Creer_frere(frere_2);
            if(Test_ponct(message,frere_2)){
                Set_noeud(frere_2,"ponct",message,1);
                message++;
            }else{
                Supprimer_arbre(fils);
                Message->fils=NULL;
                return 0;
            }
            frere_1=frere_2;
            frere_2=Creer_frere(frere_2);
            taille++;
        }else if(Test_nombre(message,frere_2)){//nombre
            message = message +frere_2->taille;
            frere_1=frere_2;
            frere_2=Creer_frere(frere_2);
            if(Test_separateur(message,frere_2)){
                Set_noeud(frere_2,"separateur",message,1);
                message++;
            }else{
                Supprimer_arbre(fils);
                Message->fils=NULL;
                return 0;
            }
            frere_1=frere_2;
            frere_2=Creer_frere(frere_2);
            taille++;
        }else{
            Supprimer_arbre(frere_2);
            frere_1->frere=NULL;
            fin=0;
        }
    }
    if(taille<2){
        Supprimer_arbre(fils);
        Message->fils=NULL;
        return 0;
    }
    frere_2=Creer_frere(frere_1);
    if(Test_ponct(message,frere_2)){
        message++;
        frere_3=Creer_frere(frere_2);
        if(Test_fin(message,frere_3)){
            message = message +3;
        }else{
            Supprimer_arbre(fils);
            Message->fils=NULL;
            return 0;
        }
        frere_4=Creer_frere(frere_3);
        if(Test_lf(message,frere_4)==0){
            Supprimer_arbre(fils);
            Message->fils=NULL;
            return 0;
        }
    }else{
        
        if(Test_fin(message,frere_2)){
            message = message +3;
        }else{
            Supprimer_arbre(fils);
            Message->fils=NULL;
            return 0;
        }
        frere_3=Creer_frere(frere_2);
        if(Test_lf(message,frere_3)==0){
            Supprimer_arbre(fils);
            Message->fils=NULL;
            return 0;
        }
    }
    return 1;   
}

int Test_fin(char *message,Noeud *noeud){
    int resultat=1;
    char *fin="fin";
    Noeud *fils;
    for(int i=0;i<3;i++){
        if( tolower(*(message+i)) != *(fin+i) ){
            resultat = 0;
        }
    }
    if(resultat == 1){
        
        fils=Creer_fils(noeud);
        Set_noeud(fils,"__istring",message,3);
    }
    Set_noeud(noeud,"fin",message,3);
    return resultat;
}

int Test_debut(char *message,Noeud *noeud){
    int resultat=1;
    char *debut="start";
    Noeud *fils;
    for(int i=0;i<5;i++){
        if( tolower(*(message+i)) != *(debut+i) ){
            resultat = 0;
        }
    }
    if(resultat == 1){
        fils=Creer_fils(noeud);
        Set_noeud(fils,"__istring",message,5);
    }
    Set_noeud(noeud,"debut",message,5);
    return resultat;
}

int Test_mot(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille_mot= 0;
    Set_noeud(noeud,"mot",message,taille_mot);
    while(Test_Alpha(message,frere)){
        message = message+1;
        fils=frere;
        frere = Creer_frere(frere);
        taille_mot++;
    }
    if(taille_mot<1){
        free(fils);
        noeud->fils=NULL;
        return 0;
    }else{
        if(Test_separateur(message,frere)){
            message = message+1;
            taille_mot++;
            noeud->taille=taille_mot;
        }else{
            Supprimer_arbre(noeud->fils);
            return 0;
        }
    }

    return 1;
}

int Test_nombre(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille_mot= 0;
    Set_noeud(noeud,"nombre",message,taille_mot);
    while(Test_digit(message,frere)){
        
        message = message+1;
        fils=frere;
        frere = Creer_frere(frere);
        taille_mot++;
    }
    if(taille_mot<1){
        free(fils);
        noeud->fils=NULL;
        return 0;
    }else{
        free(frere);
        fils->frere=NULL;
        noeud->taille=taille_mot;
    }

    return 1;
}

int Test_digit(char *message,Noeud * noeud){
    int resultat = 0;
    
    if((*message>=0x30)&&(*message<=0x39)){
        Set_noeud(noeud,"__digit",message,1);
        resultat = 1;
    }
    return resultat;
}

int Test_Alpha(char *message,Noeud *noeud){
    int resultat=0;
    
    if(((*message>=0x61)&&(*message<=0x7A))||((*message>=0x41)&&(*message<=0x5A))){
        Set_noeud(noeud,"__alpha",message,1);
        resultat =1;
    }
    return resultat;
}

int Test_separateur(char *message, Noeud *noeud){
    int resultat = 0;
    Noeud *fils=Creer_fils(noeud);
    if(Test_sp(message,fils)){
        resultat=1;
        Set_noeud(noeud,"separateur",message,1);
    }else if(Test_htab(message,fils)){
        resultat=1;
        Set_noeud(noeud,"separateur",message,1);
    }else if((*message=='-')||(*message=='_')){
        
        resultat=1;
        Set_noeud(fils,"__icar",message,1);
        Set_noeud(noeud,"separateur",message,1);
    }else{
        free(fils);
        noeud->fils=NULL;
    }
    return resultat;
}

int Test_sp(char *message,Noeud * noeud){
    int resultat=0;
    
    if(*message==0x20){
        resultat=1;
        Set_noeud(noeud,"__sp",message,1);
    }
    return resultat;
}

int Test_htab(char *message,Noeud * noeud){
    int resultat=0;
    
    if(*message==0x09){
        resultat=1;
        Set_noeud(noeud,"__htab",message,1);
    }
    return resultat;
}

int Test_ponct(char *message,Noeud* noeud){
    int resultat =0;
    Noeud * fils;
    
    if((*message==',')||(*message=='.')||(*message=='!')||(*message=='?')||(*message==':')){
        Set_noeud(noeud,"ponct",message,1);
        fils=Creer_fils(noeud);
        Set_noeud(fils,"__icar",message,1);
        resultat =1;
    }
    
    return resultat;
} 

int Test_lf(char *message,Noeud *noeud){
    int resultat=0;
    
    if(*message==0x0A){
        resultat=1;
        Set_noeud(noeud,"__lf","\n",0);
    }
    return resultat;
}