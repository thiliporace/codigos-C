#include <stdio.h>
#include <stdlib.h>

//char *buffer = "+*aba";
char *buffer;
char lookahead;
void consome(char atomo);

void S();
void A();
void B();

char *buffer=
            //"var1_21 == \n"
             //"  \t    \n"
             //"ab12_1 =  \n"
             //" +1E3\n"
             //" VI\n"
             //"100. \n"
             "acadbeadb";

int main(){
    
    lookahead = *buffer; //obter_atomo()
    printf("Analisando: %s\n", buffer);

    A();
    if (*buffer == '\0')
        printf("Analise sintatica terminada com sucesso.\n");
    else
        printf("Analise sintatica terminada com ERRO.\n");

}

void S(){
    if(lookahead == 'b' || lookahead == 'c'){
        consome('a');
        A();
        B();
    }
    else if(lookahead == 'd' || lookahead == 'e'){
        consome('a');
        B();
        A();
    }
    return;
}

void A(){
    if (lookahead == 'b'){
        consome('b');
    }
    else if (lookahead == 'c'){
        consome('c');
        S();
    }
    return;
}

void B(){
    if (lookahead == 'd'){
        consome('d');
    }
    else if (lookahead == 'e'){
        consome('e');
        S();
    }
    return;
}

void consome( char atomo ){
    if( lookahead == atomo )
        lookahead = *buffer++; // obter_atomo();
    else{
        printf("erro sintatico: esperado [%c] encontrado[%c]\n",atomo,lookahead);
        exit(1);
 }
}