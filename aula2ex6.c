#include <stdio.h>
#include <ctype.h>

char*  entrada = "int main(){ //comentario 1\n"
                "printf();\n"
                "} //fim de programa";

void converte_comentario();

int main(){
    converte_comentario();
}

void converte_comentario(){
    int dentroComentario = 0;
q0:
    while(*entrada != '/'){
        putchar(*entrada);
        entrada++;

        if(*entrada == '/'){
            putchar(*entrada);
            entrada++;
            goto q1;
        }

        if(*entrada == '\0'){
            return;
        }
    }

q1:
    if(*entrada == '/'){
        putchar(*entrada);
        entrada++;
        goto q2;
    }
    else{
        putchar(*entrada);
        entrada++;
        goto q0;
    }
q2:
    while(*entrada != '\n'){
        putchar(toupper(*entrada));
        entrada++;

        if(*entrada == '\n'){
            entrada++;
            goto q0;
        }

        if(*entrada == '\0'){
            return;
        }
    }
}