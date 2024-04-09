#include <stdio.h>
#include <ctype.h>

int AFD(char* buffer);

int main(){
    char* buffer = "{{{{{+2,5+5}}}}}";
    int resultado = AFD(buffer);
    printf("%d",resultado);
}

int AFD(char* buffer){
    int contador = 0;
q0:
    while(*buffer != '{'){
        buffer++;

        if(*buffer == '{'){
            buffer++;
            contador++;
            goto q1;
        }
    }
q1:
    while(*buffer == '{'){
        contador++;
        buffer++;

        if(*buffer != '{'){
            goto q2;
        }
    }
q2:
    if(*buffer == '}'){
        for(int i = 0;i<contador;i++){
            buffer++;

            if(*buffer == '\0'){
            return contador;
        }
        }
        if(*buffer == '\0'){
            return contador;
        }
    }
    else{
        buffer++;
        goto q2;
    }
    return 0;
}