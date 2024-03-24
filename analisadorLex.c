#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum{
    ERRO,
    BOOL,
    ELSE,
    FALSE,
    IF,
    INT,
    MAIN,
    PRINTF,
    SCANF,
    TRUE,
    VOID,
    WHILE,
    IDENTIFICADOR,
    NUMERO,
    EOS
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo_ID[16];
}TInfoAtomo;

char *strAtomo[]={"Erro Lexico","BOOL","ELSE","FALSE","IF","INT","MAIN","PRINTF","SCANF","TRUE","VOID", "WHILE", "IDENTIFICADOR","NUMERO","Fim de buffer"};

int linha = 1;
char *buffer = "int\n"
                "bool\n"
                "   var   \n"
                "\n"
               "";

// definicao de funcoes
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TAtomo reconhece_num();
TInfoAtomo reconhece_palavra_reservada();

int main(void){
    TInfoAtomo infoAtomo;
    printf("Analisando:\n%s\n", buffer);
    while(1){
        infoAtomo = obter_atomo();
        printf("%d# %s ",infoAtomo.linha, strAtomo[infoAtomo.atomo]);
        if( infoAtomo.atomo == IDENTIFICADOR)
            printf("| %s",infoAtomo.atributo_ID);
        printf("\n");
        if( infoAtomo.atomo == EOS || infoAtomo.atomo == ERRO )
            break;
        
    }    

}
TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo=ERRO;
    // ignora delimitadores
    while(*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r'){
        if(*buffer=='\n')
            linha++;

        buffer++;
    }
    // Analisador Léxico: Analisar o alfabeto 
    //1 caso: quando comecar com caractere -> funcao de palavras reservadas
    if(islower(*buffer)){
        infoAtomo = reconhece_palavra_reservada();
    }
    //2 caso: quando comecar com _ -> funcao de identificadores
    else if(isdigit(*buffer)){
        infoAtomo.atomo = reconhece_num();
    }
    //3 caso: quando comecar com numero -> funcao de numeros
    
    
    else if(*buffer == '\0')
        infoAtomo.atomo = EOS;
    
    infoAtomo.linha = linha;
    return infoAtomo;
}

TInfoAtomo reconhece_palavra_reservada(){
    TInfoAtomo infoAtomo;
    char string[15] = "";

q0:
    if(islower(*buffer)){
        strncat(string, buffer, 1);
        buffer++;
        goto q0;
    }
    goto q1;
    
q1:
    printf("String:%s",string);
    printf("\n");
    //Comparacao entre duas strings
    if (strcmp(string,"bool") == 0){
        infoAtomo.atomo = BOOL;
        //Limpa o array
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"else") == 0){
        infoAtomo.atomo = ELSE;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"false") == 0){
        infoAtomo.atomo = FALSE;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"if") == 0){
        infoAtomo.atomo = IF;
        strcpy(string, "");
        return infoAtomo;
    }
    else if(strcmp(string,"int") == 0){
        infoAtomo.atomo = INT;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"main") == 0){
        infoAtomo.atomo = MAIN;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"printf") == 0){
        infoAtomo.atomo = PRINTF;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"scanf") == 0){
        infoAtomo.atomo = SCANF;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"true") == 0){
        infoAtomo.atomo = TRUE;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"void") == 0){
        infoAtomo.atomo = VOID;
        strcpy(string, "");
        return infoAtomo;
    }
    else if (strcmp(string,"while") == 0){
        infoAtomo.atomo = WHILE;
        strcpy(string, "");
        return infoAtomo;
    }
        
}

TInfoAtomo reconhece_id(){
    TInfoAtomo infoAtomo;
    //Marca inicio do buffer
    char *iniLexema;
    iniLexema = buffer;
q0:
    if(islower(*buffer)){
        buffer++;
        goto q1;
    }
    infoAtomo.atomo = ERRO;
    return infoAtomo;
q1:
    if(islower(*buffer) || isdigit(*buffer)){
        buffer++;
        goto q1;
    }

    if(isupper(*buffer)){
        infoAtomo.atomo = ERRO;
        return infoAtomo;
    }
    goto q2;
q2:
    // recortar do buffer o lexema.

    if( buffer-iniLexema <= 15){
        // referencia:https://cplusplus.com/reference/cstring/strncpy/
        strncpy(infoAtomo.atributo_ID,iniLexema,buffer-iniLexema);
        infoAtomo.atributo_ID[buffer-iniLexema]='\0';// finaliza string
        infoAtomo.atomo = IDENTIFICADOR;
    }
    else
        infoAtomo.atomo = ERRO;

    return infoAtomo;

}

TAtomo reconhece_num(){
q0:
    if(isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    return ERRO; // [outro]
    
q1:
    if(isdigit(*buffer)){ 
        buffer++;
        goto q1;
    }
    
    if(*buffer == '.'){
        buffer++;
        goto q2;
    }
    return ERRO; // [outro]
q2:
    if(isdigit(*buffer)){
        buffer++;
        goto q3;
    }
    return ERRO; // [outro]
q3:
    if(isdigit(*buffer)){
        buffer++;
        goto q3;
    }
    if(isalpha(*buffer))
        return ERRO;
    
//    goto q4;
//q4:
    // aqui recortar e converter a sequencia de digito para float.
    return NUMERO;

}