#include <stdio.h>
#include <stdlib.h>

//S -> a,b,c,d A -> a, c B -> b, d C -> c

//char *buffer = "+*aba";
char *buffer;
char lookahead;
void consome(char atomo);

void S();
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
             "abaddc";

int main(){
    
    lookahead = *buffer; //obter_atomo()
    printf("Analisando: %s\n", buffer);

    S();
    if (*buffer == '\0')
        printf("Analise sintatica terminada com sucesso.\n");
    else
        printf("Analise sintatica terminada com ERRO.\n");

}

void S(){
    A();
    B();
    C();
    D();
    consome('d');
}

void A(){
    if (lookahead == 'a'){
        consome('a');
        A();
    }
}

void B(){
    if (lookahead == 'b'){
        consome('b');
        C();
    }
}

void C(){
    if (lookahead == 'c'){
        consome('c');
        D();
    }
}

void D(){
    consome('e');
}

void consome( char atomo ){
    if( lookahead == atomo )
        lookahead = *buffer++; // obter_atomo();
    else{
        printf("erro sintatico: esperado [%c] encontrado[%c]\n",atomo,lookahead);
        exit(1);
 }
}