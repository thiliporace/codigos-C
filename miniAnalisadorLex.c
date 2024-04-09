#include <stdio.h>
#include <ctype.h> // isdigit

typedef enum{
    ERRO,
    IDENTIFICADOR,
    NUMERO,
    OP_ADICAO,
    OP_SUBTRACAO,
    OP_ATRIBUICAO,
    OP_IGUALDADE,
    EOS
}TAtomo;

// string para mensagem do atomo
char *strAtomo[] = {"ERRO",
                     "IDENTIFICADOR",
                     "NUMERO",
                     "OP_ADICAO",
                     "OP_SUBTRACAO",
                     "OP_ATRIBUICAO",
                     "OP_IGUALDADE",
                     "EOS"};
// linha informacao global
int linha = 1;

//Romano
int contador = 0;

char *buffer="var1_21 == \n"
             "  \t    \n"
             "ab12_1 =  \n"
             //" +1E3\n"
             " VI\n"
             //"100. \n"
             "A0 ";

TAtomo obter_atomo(void); 
TAtomo reconhece_id(void);
TAtomo reconhece_num(void);
TAtomo reconhece_atribuicao();
TAtomo reconhece_romano();

int main(){
    TAtomo atomo;
    printf("Analisando:\n %s \n",buffer);
    printf("============\n");
    
    while(1){
        atomo = obter_atomo();
        
        if (atomo == NUMERO){
            printf("%d# %s | valor: %d\n", linha, strAtomo[atomo],contador);
        }
        else{
            printf("%d# %s\n", linha, strAtomo[atomo]);
        }
        
        if(atomo == EOS){
            printf("fim de analise\n");
            break;
        }
        if(atomo == ERRO )
            break;          
    }
    return 0;
}
TAtomo obter_atomo(void){
    TAtomo atomo_retorno;
    
    atomo_retorno = ERRO;
    // descartar caracteres delimitadores
    while(*buffer == '\n'  || *buffer == '\r' || *buffer == ' ' || *buffer == '\t' ){
        if(*buffer == '\n') // conta as linhas
            linha++;
        buffer++;
    }
    // https://cplusplus.com/reference/cctype/islower/
    if(islower(*buffer)){
        atomo_retorno = reconhece_id();
    }
    else if(isdigit(*buffer)){
        atomo_retorno = reconhece_num();
    }
    else if(*buffer == '+' || *buffer == '-'){
        atomo_retorno = reconhece_num();
    }
    else if(*buffer == 'I' || 'V' || 'X' || 'L'){
        atomo_retorno = reconheec_romano();
    }
    else if(*buffer == '='){
        atomo_retorno = reconhece_atribuicao();
    }
    else if (*buffer == '\0')
        atomo_retorno = EOS;

    return atomo_retorno;
}

TAtomo reconhece_atribuicao(){
q0:
    if (*buffer == '='){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '='){
        buffer++;
        return OP_IGUALDADE;
    }
    else{
        buffer++;
        return OP_ATRIBUICAO;
    }
}

TAtomo reconhece_id(void){
q0:
    if(islower(*buffer)){
        buffer++;
        goto q1;
    }
    return ERRO;
q1:
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    else if(*buffer == '_'){
        buffer++;
        goto q2;
    }
    return ERRO;
q2:
    if(isalpha(*buffer) || isdigit(*buffer)){
        buffer++;
        goto q2;
    }
    else{
        return IDENTIFICADOR;
    }
    return ERRO;
}

// TAtomo reconhece_num(void){
// q0:
//     if(*buffer == '+' || *buffer == '-'){
//         buffer++;
//         goto q1;
//     }
//     else if(isdigit(*buffer)){
//         buffer++;
//         goto q2;
//     }
//     return ERRO;
// q1:
//     if(isdigit(*buffer)){
//         buffer++;
//         goto q2;
//     }
//     else if(*buffer == '+'){
//         buffer++;

//     }
//     else if(*buffer == '-'){
//         buffer++;

//     }
//     return ERRO;
// q2:
//     if(*buffer == '.'){
//         buffer++;

//         if(isdigit(*buffer)){
//             buffer++;
//             goto q3;
//         }
//     }
//     else if(*buffer == 'E'){
//         //buffer++;
//         goto q3;
//     }
//     return ERRO;
// q3:
//     if(*buffer == 'E'){
//         buffer++;

//         if(*buffer == '+' || *buffer == '-'){
//             buffer++;
//             goto q4;
//         }
//         else if(isdigit(*buffer)){
//             goto q4;
//         }
//     }
//     else{
//         return NUMERO;
//     }
// q4:
//     if(isdigit(*buffer)){
//         buffer++;
//         return NUMERO;
//     }
//     return ERRO;
// }

TAtomo reconhece_romano(){
q0:
    if(*buffer == 'I'){
        buffer++;
        contador++;
        goto q1;
    }
    else if(*buffer == 'V'){
        buffer++;
        contador += 5;
        goto q2;
    }
    else if(*buffer == 'X'){
        buffer++;
        contador += 5;
        goto q2;
    }
q1:
    if(*buffer == 'I'){
        while(*buffer == 'I'){
            buffer++;
            contador++;

            if(*buffer == 'V' || *buffer == 'X'){
                return ERRO;
            }

            if(*buffer != 'I'){
                return NUMERO;
            }
        }
    }
    else if(*buffer == 'X'){
        contador += 8;
        buffer++;
        return NUMERO;
    }
    else if(*buffer == 'V'){

    }
q2:
    
}