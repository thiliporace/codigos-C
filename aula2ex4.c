#include <stdio.h>
#include <ctype.h>

int AFD(char* entrada);

int main(){
    char*  entrada = "+2,5+5";
    int resultado = AFD(entrada);
    printf("%d",resultado);
}

int AFD(char* entrada){
q0:
    if(*entrada == '+' || *entrada == '-'){
        entrada++;
        goto q1;
    }
    else if(isdigit(*entrada)){
        entrada++;
        goto q2;
    }
q1:
    if(isdigit(*entrada)){
        entrada++;
        goto q2;
    }
q2:
    if(*entrada == ','){
        entrada++;
        if(isdigit(*entrada)){
            entrada++;
            goto q3;
        }
    }
    return 0;
q3:
    if(isdigit(*entrada) || *entrada == '+' || *entrada == '-'){
        entrada++;
        goto q4;
    }
q4:
    if(isdigit(*entrada)){
        entrada++;
        goto q4;
    }
    return 1;
}