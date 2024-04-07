#include <stdio.h>
#include <ctype.h>

int AFD(char* entrada);

int main(){
    char*  entrada = "abbabba";
    int resultado = AFD(entrada);
    printf("%d",resultado);
}

int AFD(char* entrada){
q0:
    if(*entrada == 'a'){
        entrada++;
        goto q1;
    }
    else if(*entrada == 'b'){
        entrada++;
        goto q3;
    }
    return 0;
q1:
    if(*entrada == 'a'){
        entrada++;
        goto q2;
    }
    else if(*entrada == 'b'){
        entrada++;
        goto q3;
    }
    return 0;
q2:
    if(*entrada == 'a'){
        entrada++;
        goto q2;
    }
    else if(*entrada == 'b'){
        entrada++;
        goto q3;
    }
    return 1;
q3:
    if(*entrada == 'a'){
        entrada++;
        goto q1;
    }
    else if(*entrada == 'b'){
        entrada++;
        goto q4;
    }
    return 0;
q4:
    if(*entrada == 'a'){
        entrada++;
        goto q1;
    }
    else if(*entrada == 'b'){
        entrada++;
        goto q4;
    }
    return 1;
}