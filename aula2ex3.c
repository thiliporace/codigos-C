#include <stdio.h>
#include <ctype.h>

int AFD(char* entrada);

int main(){
    char*  entrada = "a9_9";
    int resultado = AFD(entrada);
    printf("%d",resultado);
}

int AFD(char* entrada){
q0:
    if(islower(*entrada) || isupper(*entrada)){
        entrada++;
        goto q1;
    }
q1:
    if(islower(*entrada) || isupper(*entrada) || isdigit(*entrada)){
        entrada++;
        goto q1;
    }
    else if (*entrada == '_'){
        entrada++;
        goto q3;
    }
    return 0;
q2:
    if(*entrada == '_'){
        entrada++;
        goto q3;
    }
q3:
    if(islower(*entrada) || isupper(*entrada)){
        entrada++;
        if(isdigit(*entrada)){
            entrada++;
            goto q3;
        }
        return 0;
        }
    else if(*entrada == '\0'){
        return 1;
    }
}