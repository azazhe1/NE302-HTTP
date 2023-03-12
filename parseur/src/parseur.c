#include "parseur.h"

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
    //fscanf(fp,"%[^\n]%*c\n",message);
    //printf("%s\n",message);
    //printf("test : %c\n",0x80);
    fclose(fp);
    strcpy(message,"");
    char *expect = "vA1.-";
    Noeud * noeud =Creer_Noeud();
    strcat(message,expect);
    
    /*
    Test_expect(expect,noeud);
    Noeud *frere = Creer_frere(noeud);
    //message ++;
    expect =expect +noeud->taille;
    Test_bws(expect,frere);
    expect++;
    frere = Creer_frere(frere);
    if(Test_quoted_pair(expect,frere)){
        Afficher_noeud(noeud);
    }else{
        printf("pas bon\n");
    }
    
    */
    if(Test_IPvFutur(expect,noeud)){
        Afficher_noeud(noeud);
    }else{
        printf("pas bon\n");
    }
    Supprimer_arbre(noeud);
}

/**
 * @brief dquote = %x22
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_dquote(char *message,Noeud *noeud){
    if(*message == 0x22){
        Set_noeud(noeud,"__dquote",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_cookie_octet(char *message,Noeud *noeud){
    if( (*message==0x21) || ((*message>=0x23)&&(*message<=0x2B)) || ((*message>=0x2D)&&(*message<=0x3A)) || ((*message>=0x3C)&&(*message<=0x5B)) || ((*message>=0x5D)&&(*message<=0x7E)) ){
        Set_noeud(noeud,"__cookie_octet",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief vchar = %x21-7E
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_vchar(char *message,Noeud *noeud){
    if((*message>=0x21)&&(*message<=0x7E)){
        Set_noeud(noeud,"__vchar",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief obs-text = %x80-FF
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_obs_text(char *message,Noeud *noeud){
    if( ((unsigned char)(*message)>=0x80) && ((unsigned char)(*message)<=0xFF) ){
        Set_noeud(noeud,"__obs_text",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_sub_delims(char *message,Noeud *noeud){
    if( (*message == '!') || (*message == '$') || (*message == '&') || (*message == '\'') || (*message == '(') || (*message == ')') || (*message == '*') || (*message == '+') || (*message == ',') || (*message == ';') || (*message == '=') ){
        Set_noeud(noeud,"__sub_delims",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief ALPHA = %x41-5A / %x61-7A   ; A-Z / a-z
 * 
 * @param message 
 * @param noeud
 *  
 * @return int 
 */
int Test_Alpha(char *message,Noeud *noeud){
    if( ((*message>=0x61)&&(*message<=0x7A)) || ((*message>=0x41)&&(*message<=0x5A)) ){
        Set_noeud(noeud,"__alpha",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief DIGIT =  %x30-39
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_digit(char *message,Noeud * noeud){
    if( (*message>=0x30)&&(*message<=0x39) ){
        Set_noeud(noeud,"__digit",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief Expect = "100-continue"
 * 
 * @param message 
 * @param noeud 
 * @return int 
 */
int Test_expect(char *message,Noeud *noeud){
    char *expect = "100-continue";
    for(int i=0;i<12;i++){
        if(tolower(*(message+i)) != *(expect+i) ){
            return 0;
        }
    }
    Set_noeud(noeud,"__expect",message,12);
    return 1;
}

/**
 * @brief HTAB = %x09
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_htab(char *message,Noeud * noeud){
    if(*message==0x09){
        Set_noeud(noeud,"__htab",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief OCTET = %x00-FF
 * 
 * @param messagte 
 * @param noeud
 * 
 * @return int 
 */
int Test_octet(char *message,Noeud *noeud){
    if((*message>=0x00)&&((unsigned char)(*message)<=0xFF)){
        Set_noeud(noeud,"__octet",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief SP = %0x20
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_sp(char *message,Noeud * noeud){
    if(*message==0x20){
        Set_noeud(noeud,"__sp",message,1);
        return 1;
    }
    return 0;
}

/**
 * @brief CRLF = CR LF ; %x0D & %x0A
 * 
 * @param message 
 * @param noeud 
 * @return int 
 */
int Test_crlf(char *message,Noeud *noeud){
    message = message +12;
    if(*message!=0x0D){
        return 0;
    }
    message++;
    if(*message!=0x0A){
        return 0;
    }
    message--;
    Set_noeud(noeud,"__crlf",message,2);
    return 1;
}

/**
 * @brief OWS = *( SP / HTAB )
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_ows(char *message,Noeud *noeud){
    Noeud *fils=Creer_fils(noeud);
    Noeud *frere = fils;
    int fin = 1;
    int taille_mot = 0;
    Set_noeud(noeud,"ows",message,taille_mot);
    while(fin){
        if(Test_sp(message,frere)){
            taille_mot++;
            message++;
            fils = frere;
            frere = Creer_frere(frere);
        }else if(Test_htab(message,frere)){
            taille_mot++;
            message++;
            fils = frere;
            frere = Creer_frere(frere);
        }else{
            fin = 0;
        }
    }
    if(taille_mot<1){
        Supprimer_arbre(fils);
        noeud->fils = NULL;
        return 0;
    }
    Supprimer_arbre(frere);
    fils->frere = NULL;
    noeud->taille = taille_mot;
    return 1;
}

/**
 * @brief BWS = OWS
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_bws(char *message,Noeud *noeud){
    
    Noeud *fils=Creer_fils(noeud);
    if(!Test_ows(message,fils)){
        Supprimer_arbre(fils);
        noeud->fils = NULL;
        return 0;
    }
    Set_noeud(noeud,"bws",message,fils->taille);
    return 1;
}

/**
 * @brief tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
 * 
 * @param message 
 * @param noeud 
 * @return int 
 */
int Test_tchar(char *message, Noeud *noeud){
    Noeud *fils;
    if( (*message == '!') || (*message == '#') || (*message == '$') || (*message == '%') || (*message == '&') || (*message == '\'') || (*message == '*') || (*message == '+') || (*message == '-') || (*message == '.') || (*message == '^') | (*message == '_') | (*message == '`') | (*message == '|') | (*message == '~') ){
        Set_noeud(noeud,"tchar",message,1);
        return 1;
    }
    fils = Creer_fils(noeud);
    if( Test_digit(message,fils) || Test_Alpha(message,fils) ){
        Set_noeud(noeud,"tchar",message,1);
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_quoted_pair(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere;
    Set_noeud(noeud,"quoted_pair",message,0);
    if(*message!='\\'){
        Supprimer_arbre(fils);
        noeud->fils = NULL;
        return 0;
    }
    Set_noeud(fils,"__icar",message,1);
    message++;
    frere = Creer_frere(fils);
    if(Test_htab(message,frere) || Test_sp(message,frere) || Test_vchar(message,frere) || Test_obs_text(message,frere)){
        noeud->taille = 2;
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief qdtext = HTAB / SP / "!"" / %x23-5B / %x5D-7E / obs-text
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_qdtext(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Set_noeud(noeud,"qdtext",message,0);
    if(Test_htab(message,fils) || Test_sp(message,fils) || Test_obs_text(message,fils)){
        noeud->taille = 1;
        return 1;
    }
    if( ((*message>=0x23)&&(*message<=0x5B)) || ((*message>=0x5D)&&(*message<=0x7E)) || (*message=='!') ){
        Set_noeud(fils,"__icar",message,1);
        noeud->taille = 1;
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief dec-octet = "25" %x30-35 ; 250-255 / "2" %x30-34 DIGIT     ; 200-249 / "1" 2DIGIT            ; 100-199 / %x31-39 DIGIT         ; 10-99 / DIGIT                 ; 0-9
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_dec_octet(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere;
    if((*message =='2')&&(*(message+1)=='5')){
        if(*(message+2)>=0x30 && *(message+2)<=0x35){
            Set_noeud(fils,"__digit",message,1);
            fils = Creer_frere(fils);
            Set_noeud(fils,"__digit",message+1,1);
            fils = Creer_frere(fils);
            Set_noeud(fils,"__digit",message+2,1);
            Set_noeud(noeud,"dec_octet",message,3);
            
            return 1;
        }
    }
    if(*message == '2'){
        if(*(message+1)>=0x30 && *(message+1)<=0x34){
            frere =Creer_frere(fils);
            if(Test_digit(message+1,frere)){
                Set_noeud(fils,"__digit",message,1);
                fils = Creer_frere(fils);
                Set_noeud(fils,"__digit",message+1,1);
                fils->frere = frere;
                Set_noeud(noeud,"dec_octet",message,3);
                
                return 1;
            }else{
                Supprimer_arbre(frere);
                fils->frere = NULL;
            }
        }
    }
    if(*message == '1'){
        frere = Creer_frere(fils);
        if(Test_digit(message+1,frere)){
            frere = Creer_frere(frere);
            if(Test_digit(message+2,frere)){
                Set_noeud(fils,"__digit",message,1);
                Set_noeud(noeud,"dec_octet",message,3);
                return 1;
            }else{
                Supprimer_arbre(fils->frere);
                fils->frere = NULL;
                
            }
        }else{
            Supprimer_arbre(frere);
            fils->frere = NULL;
        }
    }
    if((*message>=0x31)&&(*message<=0x39)){
        frere = Creer_frere(fils);
        if(Test_digit(message+1,frere)){
            Set_noeud(fils,"__digit",message,1);
            Set_noeud(noeud,"dec_octet",message,2);
            return 1;
        }else{
            Supprimer_arbre(frere);
            fils->frere = NULL;
        }
    }
    if(Test_digit(message,fils)){
        Set_noeud(noeud,"dec_octet",message,1);
        
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief ipv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_ipv4address(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    int taille = 0;
    Set_noeud(noeud,"ipv4address",message,0);
    if(!Test_dec_octet(message,fils)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    taille+=fils->taille;
    message+=fils->taille;
    if(*message != '.'){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    fils = Creer_frere(fils);
    Set_noeud(fils,"__icar",message,1);
    message++;
    taille++;
    fils = Creer_frere(fils);
    if(!Test_dec_octet(message,fils)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    taille+=fils->taille;
    message+=fils->taille;
    if(*message != '.'){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    fils = Creer_frere(fils);
    Set_noeud(fils,"__icar",message,1);
    message++;
    taille++;
    fils = Creer_frere(fils);
    if(!Test_dec_octet(message,fils)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    taille+=fils->taille;
    message+=fils->taille;
    if(*message != '.'){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    fils = Creer_frere(fils);
    Set_noeud(fils,"__icar",message,1);
    taille++;
    message++;
    fils = Creer_frere(fils);
    if(!Test_dec_octet(message,fils)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL; 
        return 0;
    }
    taille+=fils->taille;
    noeud->taille = taille;
    return 1;
}

/**
 * @brief HEXDIG = DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_hexdig(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    if(Test_digit(message,fils)){
        Set_noeud(noeud,"hexdig",message,1);
        return 1;
    }else if((*message>=0x41)&&(*message<=0x46)){
        Set_noeud(fils,"__icar",message,1);
        Set_noeud(noeud,"hexdig",message,1);
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief h16 = 1*4HEXDIG
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_h16(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere=fils;
    int fin =1;
    int taille = -1;
    Set_noeud(noeud,"h16",message,0);
    while(fin){
        for(int i=0;i<4;i++){
            if(!Test_hexdig(message,frere)){
                fin = 0;
                break;
            }
            fils = frere;
            message++;
            frere = Creer_frere(frere);
        }
        taille++;
    }
    if(taille <1){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    Supprimer_arbre(frere);
    fils->frere = NULL;
    noeud->taille = 4*taille;

    return 1;
}

/**
 * @brief ls32 = ( h16 ":" h16 ) / ipv4address
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_ls32(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    int taille = 0;
    Set_noeud(noeud,"ls32",message,0);
    if(Test_h16(message,fils)){
        message+=fils->taille;
        taille+=fils->taille;
        if(*message != ':'){
            Supprimer_arbre(noeud->fils);
            noeud->fils = NULL;
            return 0;
        }
        taille++;
        fils = Creer_frere(fils);
        Set_noeud(fils,"__icar",message,1);
        message++;
        fils = Creer_frere(fils);
        if(Test_h16(message,fils)){
            noeud->taille = taille + fils->taille;
            return 1;
        }
    }
    Supprimer_arbre(noeud->fils);
    fils = Creer_fils(noeud);
    if(Test_ipv4address(message,fils)){
        noeud->taille = fils->taille;
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief token = 1*tchar
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_token(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille = 0;

    Set_noeud(noeud,"token",message,0);
    while(Test_tchar(message,frere)){
        taille+=fils->taille;
        message+=fils->taille;
        fils = frere;
        frere = Creer_frere(frere);
    }
    Supprimer_arbre(frere);
    fils->frere = NULL;
    if(taille < 1){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    noeud->taille = taille;
    return 1;
}

/**
 * @brief cookie-name = token
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_cookie_name(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    if(Test_token(message,fils)){
        Set_noeud(noeud,"cookie-name",message,fils->taille);
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief cookie-value = ( DQUOTE *cookie-octet DQUOTE ) / *cookie-octet
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_cookie_value(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille = 0;
    Set_noeud(noeud,"cookie-value",message,0);
    if(Test_dquote(message,fils)){
        taille++;
        message++;
        frere = Creer_frere(fils);
        while(Test_cookie_octet(message,frere)){
            taille+=fils->taille;
            message+=fils->taille;
            fils = frere;
            frere = Creer_frere(frere);
        }
        if(!Test_dquote(message,frere)){
            Supprimer_arbre(noeud->fils);
            noeud->fils = NULL;
            return 0;
        }
        taille++;
        noeud->taille = taille;
        return 1;
    }
    while(Test_cookie_octet(message,frere)){
        taille+=fils->taille;
        message+=fils->taille;
        fils = frere;
        frere = Creer_frere(frere);
    }
    if(taille < 1){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    Supprimer_arbre(frere);
    fils->frere = NULL;
    noeud->taille = taille;
    return 1;
}

/**
 * @brief unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
int Test_unreserved(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    if(Test_Alpha(message,fils)){
        Set_noeud(noeud,"unreserved",message,1);
        return 1;
    }else if (Test_digit(message,fils)){
        Set_noeud(noeud,"unreserved",message,1);
        return 1;
    }else if((*message == '-') || (*message == '.') || (*message == '_') || (*message == '~')){
        Set_noeud(noeud,"unreserved",message,1);
        Set_noeud(fils,"__icar",message,1);
        return 1;
    }
    Supprimer_arbre(fils);
    noeud->fils = NULL;
    return 0;
}

/**
 * @brief IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
 * 
 * @param message 
 * @param noeud 
 * 
 * @return int 
 */
int Test_IPvFutur(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere;
    int taille = 0;
    int fin = 1;
    int taile_2=0;
    Set_noeud(noeud,"IPvFutur",message,0);
    if(*message != 'v'){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    Set_noeud(fils,"__icar",message,1);
    taille++;
    message++;
    fils = Creer_frere(fils);
    frere = fils;
    while(Test_hexdig(message,frere)){
        taille++;
        message++;
        fils = frere;
        frere = Creer_frere(frere);
    }
    if(taille < 1){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    if(*message != '.'){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    Set_noeud(fils,"__icar",message,1);
    taille++;
    message++;
    fils = Creer_frere(fils);
    frere = fils;
    while(fin){
        if(Test_unreserved(message,frere)){
            taille++;
            taile_2++;
            message+=fils->taille;
            fils = frere;
            frere = Creer_frere(frere);
        }else if(Test_sub_delims(message,frere)){
            taille+=fils->taille;
            taile_2++;
            message+=fils->taille;
            fils = frere;
            frere = Creer_frere(frere);
        }else if(*message == ':'){
            Set_noeud(fils,"__icar",message,1);
            taille++;
            taile_2++;
            message++;
            fils = Creer_frere(fils);
            frere = fils;
        }else{
            fin = 0;
        }
    }
    Supprimer_arbre(frere);
    fils->frere = NULL;
    if(taile_2 < 1){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    noeud->taille = taille;
    return 1;
}


/**
 * @brief quoted-string = DQUOTE *( qdtext / quoted-pair ) DQUOTE
 * 
 * @param message 
 * @param noeud
 * 
 * @return int 
 */
//[PAS FINI]
int Test_quoted_string(char *message,Noeud *noeud){
    Noeud *fils = Creer_fils(noeud);
    Noeud *frere = fils;
    int taille = 0;
    int fin = 1;
    Set_noeud(noeud,"quoted-string",message,0);
    if(!Test_dquote(message,fils)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    taille++;
    message++;
    fils = Creer_frere(fils);
    while(fin){
        if(Test_qdtext(message,frere)){
            taille+=fils->taille;
            message+=fils->taille;
            fils = frere;
            frere = Creer_frere(frere);
        }else if(Test_quoted_pair(message,frere)){
            taille+=fils->taille;
            message+=fils->taille;
            fils = frere;
            frere = Creer_frere(frere);
        }else{
            fin = 0;
        }
    }
    if(!Test_dquote(message,frere)){
        Supprimer_arbre(noeud->fils);
        noeud->fils = NULL;
        return 0;
    }
    taille++;
    noeud->taille = taille;
    return 1;
}