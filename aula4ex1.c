#include <stdio.h>
#include <stdlib.h>

//char *buffer = "+*aba";
char *buffer;
char lookahead;
void consome(char atomo);

void A();
void B();
void C();
void D();

char *buffer=
            //"var1_21 == \n"
             //"  \t    \n"
             //"ab12_1 =  \n"
             //" +1E3\n"
             //" VI\n"
             //"100. \n"
             "bcabcbb";

int main(){
    
    lookahead = *buffer; //obter_atomo()
    printf("Analisando: %s\n", buffer);

    A();
    if (*buffer == '\0')
        printf("Analise sintatica terminada com sucesso.\n");
    else
        printf("Analise sintatica terminada com ERRO.\n");

}

void A(){
    consome('b');
    B();
    consome('b');
}

void B(){
    if (lookahead == 'c'){
        consome('c');
        C();
    }
    else if (lookahead == 'e'){
        consome('e');
        D();
    }
}

void C(){
    consome('a');
    A();
}

void D(){
    consome('d');
    consome('a');
}

void consome( char atomo ){
    if( lookahead == atomo ){
        lookahead = *buffer++; // obter_atomo();
        printf("%s ",atomo);
    }
    else{
        printf("erro sintatico: esperado [%c] encontrado[%c]\n",atomo,lookahead);
        exit(1);
 }
}