#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"
#include <ctype.h>

int Test_dquote(char *message,Noeud *noeud);
int Test_cookie_octet(char *message,Noeud *noeud);
int Test_vchar(char *message,Noeud *noeud);
int Test_obs_text(char *message,Noeud *noeud);
int Test_sub_delims(char *message,Noeud *noeud);
int Test_Alpha(char *message,Noeud *noeud);
int Test_digit(char *message,Noeud * noeud);
int Test_expect(char *message,Noeud *noeud);
int Test_htab(char *message,Noeud * noeud);
int Test_octet(char *message,Noeud *noeud);
int Test_crlf(char *message,Noeud *noeud);
int Test_ows(char *message,Noeud *noeud);
int Test_bws(char *message,Noeud *noeud);
int Test_tchar(char *message, Noeud *noeud);
int Test_quoted_pair(char *message,Noeud *noeud);
int Test_qdtext(char *message,Noeud *noeud);
int Test_dec_octet(char *message,Noeud *noeud);
int Test_ipv4address(char *message,Noeud *noeud);