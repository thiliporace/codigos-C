#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//S -> a,b,c,d A -> a, c B -> b, d C -> c

//char *buffer = "+*aba";
char *buffer;
char lookahead;
void consome(char atomo);

void expressao();
void termo();
void fator();
void C();
void E();
void L();

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

void expressao(){
    if(lookahead == '+' || lookahead == '-' || isdigit(lookahead)){
        if(lookahead == '+'){
            consome('+');
        }
        else if(lookahead == '-'){
            consome('-');
        }

        termo();

        while(lookahead == '+' || lookahead == '-'){
            if(lookahead == '+'){
                consome('+');
            }
            else if(lookahead == '-'){
                consome('-');
            }
            termo();
        }
    }
}

void termo(){
    if(isdigit(lookahead)){
        fator();
         while(lookahead == '*' || lookahead == '/'){
            if(lookahead == '*'){
                consome('*');
            }
            else if(lookahead == '/'){
                consome('/');
            }
            fator();
        }
    }
}

void fator(){
    if(isdigit(lookahead)){
        consome(lookahead);
    }
    else if(lookahead == '('){
        consome('(');
        expressao();
        consome(')');
    }
}



void consome( char atomo ){
    if( lookahead == atomo )
        lookahead = *buffer++; // obter_atomo();
    else{
        printf("erro sintatico: esperado [%c] encontrado[%c]\n",atomo,lookahead);
        exit(1);
 }
}