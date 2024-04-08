#include <stdio.h>
#include <ctype.h>

int AFD(char* entrada);

int main(){
    char*  entrada = "var1";
    int resultado = AFD(entrada);
    printf("%d",resultado);
}

int AFD(char* entrada){
q0:
    if(isalpha(*entrada)){
        entrada++;
        goto q1;
    }
    return 0;
q1:
    if(isalpha(*entrada) || isdigit(*entrada)){
        entrada++;
        goto q1;
    }
    else if (*entrada == '_'){
        entrada++;
        goto q3;
    }
    return 0;
q3:
    if(isalpha(*entrada) || isdigit(*entrada)){
        entrada++;
        goto q3;
        }
    else if(*entrada == '\0'){
        return 1;
    }
    return 0;
}