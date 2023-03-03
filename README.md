# NE302-HTTP
HTTP-Serveur

Notes de changements :

Fonctions.c contient toutes les fonctions ,incluant la structure Noeud ,non traitées dans grammaire.c (exemple : Nombre, Lf ...) .
Changements effectués sur les fonctions Mot et Test_message dans grammaire.c, les changements ont étés commentés pour la compréhension de leur utilité.


Pour exécuter le code :
valgrind --track-origins=yes -s --leak-check=full --show-leak-kinds=all  ./main
