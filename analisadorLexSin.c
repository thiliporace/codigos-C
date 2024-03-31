#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
    ATRIBUICAO,
    COMPARACAO,
    SOMA,
    SUBTRACAO,
    DIVISAO,
    MULTIPLICACAO,
    MAIOR,
    MENOR,
    MAIOR_IGUAL,
    MENOR_IGUAL,
    ABRE_PAR,
    FECHA_PAR,
    ABRE_CHAVE,
    FECHA_CHAVE,
    VIRGULA,
    PONTO_VIRGULA,
    OR,
    AND,
    DIFERENTE_IGUAL,
    EOS
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
    float atributo_numero;
    char atributo_ID[16];
}TInfoAtomo;

int linha = 1;

bool inCommentary = false;

char *buffer = 
                // "/* \n" //1
                // "programa le dois numeros\n" //2
                // "inteiros e encontra o maior\n" //3
                // "*/ \n" //4
                "int main(void){\n" //5
                "int _num1, _num2;\n" //6
                "int _maior;\n" //7
                "scanf(_num1);\n" //8
                "scanf(_num2);\n" //9
                "if( _num1 > _num2 )\n" //10
                "_maior = _num1;\n" //11
                "else\n" //12
                "_maior = _num2; \n" //13
                "\n" //14
                "printf(_maior); // imprime o maior valor \n" //15
                " }"; //16

// definicao de funcoes
TInfoAtomo obter_atomo();
TInfoAtomo reconhece_id();
TAtomo reconhece_num();
TInfoAtomo reconhece_palavra_reservada();
TInfoAtomo reconhece_barra();
TInfoAtomo reconhece_atribuicao();
TInfoAtomo reconhece_maior();
TInfoAtomo reconhece_menor();
TInfoAtomo reconhece_and();
TInfoAtomo reconhece_or();
TInfoAtomo reconhece_diferente();

// Inicio de variaveis sintatico

TInfoAtomo infoAtomo;

char *strAtomo[]={"Erro Lexico","BOOL","ELSE","FALSE","IF","INT","MAIN","PRINTF","SCANF","TRUE","VOID", 
"WHILE", "IDENTIFICADOR","NUMERO","ATRIBUICAO","COMPARACAO","SOMA","SUBTRACAO","DIVISAO","MULTIPLICACAO","MAIOR",
"MENOR","MAIOR_IGUAL","MENOR_IGUAL","ABRE_PAR","FECHA_PAR",
"ABRE_CHAVE","FECHA_CHAVE","VIRGULA","PONTO_VIRGULA","OR","AND","DIFERENTE_IGUAL","Fim de buffer"};

TAtomo lookahead;

// Inicio de funcoes sintatico

void consome(TAtomo atomo);
void programa();
void declaracoes();
void declaracao();
void tipo();
void lista_variavel();
void comandos();
void comando();
void bloco_comandos();
void atribuicao();
void comando_if();
void comando_while();
void comando_entrada();
void comando_saida();
void expressao();
void expressao_logica();
void expressao_relacional();
void op_relacional();
void expressao_adicao();
void expressao_multi();
void operando();

int main(void){
    infoAtomo = obter_atomo();
    lookahead = infoAtomo.atomo;
    // funcao para transformar arquivo em string
    printf("Analisando:\n%s\n", buffer);
    programa();
}

TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo=ERRO;
    // ignora delimitadores
    while((*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == '\r') && (!inCommentary)) {
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
    else if(*buffer == '_'){
        infoAtomo = reconhece_id();
    }
    //3 caso: quando comecar com numero -> funcao de numeros
    else if(*buffer == '0' && *(buffer + 1) == 'x') {
        infoAtomo.atomo = reconhece_num();
    }
    //4 caso: se reconhecer um / -> funcao de divisao e comentario
    else if(*buffer == '/'){
        infoAtomo = reconhece_barra();
    }
    //5 caso: se reconhecer = -> funcao de atribuicao
    else if(*buffer == '='){
        infoAtomo = reconhece_atribuicao();
    }
    //6 caso: se encontrar + -> soma
    else if(*buffer == '+'){
        infoAtomo.atomo = SOMA;
        buffer++;
    }
    //7 caso: se encontrar - -> subtracao
    else if(*buffer == '-'){
        infoAtomo.atomo = SUBTRACAO;
        buffer++;
    }
    //8 caso: se encontrar > -> funcao do maior
    else if(*buffer == '>'){
        infoAtomo = reconhece_maior();
    }
    //9 caso: se encontrar < -> funcao do menor
    else if(*buffer == '<'){
        infoAtomo = reconhece_menor();
    }
    //10 caso: se encontrar * -> multiplicacao
    else if(*buffer == '*'){
        infoAtomo.atomo = MULTIPLICACAO;
        buffer++;
    }
    //11 caso: se encontrar ( -> abre_par
    else if(*buffer == '('){
        infoAtomo.atomo = ABRE_PAR;
        buffer++;
    }
    //12 caso: se encontrar ) -> fecha_par
    else if(*buffer == ')'){
        infoAtomo.atomo = FECHA_PAR;
        buffer++;
    }
    //13 caso: se encontrar { -> abre_chave
    else if(*buffer == '{'){
        infoAtomo.atomo = ABRE_CHAVE;
        buffer++;
    }
    //14 caso: se encontrar } -> fecha_chave
    else if(*buffer == '}'){
        infoAtomo.atomo = FECHA_CHAVE;
        buffer++;
    }
    //15 caso: se encontrar , -> virgula
    else if(*buffer == ','){
        infoAtomo.atomo = VIRGULA;
        buffer++;
    }
    //16 caso: se encontrar ; -> ponto_virgula
    else if(*buffer == ';'){
        infoAtomo.atomo = PONTO_VIRGULA;
        buffer++;
    }
    //17 caso: se encontrar | -> funcao de OR
    else if(*buffer == '|'){
        infoAtomo = reconhece_or();
    }
    //18 caso: se encontrar & -> funcao de AND
    else if(*buffer == '&'){
        infoAtomo = reconhece_and();
    }
    //19 caso: se encontrar ! -> funcao de DIFERENTE
    else if(*buffer == '!'){
        infoAtomo = reconhece_diferente();
    }
    // caso: se chegar ao final da string retorna EOS
    else if(*buffer == '\0')
        infoAtomo.atomo = EOS;
    
    infoAtomo.linha = linha;
    return infoAtomo;
}

// Reconhece OR (||)
TInfoAtomo reconhece_or(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '|'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '|'){
        infoAtomo.atomo = OR;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = ERRO;
        return infoAtomo;
    }
    
}

// Reconhece AND (&&)
TInfoAtomo reconhece_and(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '&'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '&'){
        infoAtomo.atomo = AND;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = ERRO;
        return infoAtomo;
    }
    
}

// Reconhece DIFERENTE_IGUAL (!=)
TInfoAtomo reconhece_diferente(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '!'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '='){
        infoAtomo.atomo = DIFERENTE_IGUAL;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = ERRO;
        return infoAtomo;
    }
    
}

TInfoAtomo reconhece_menor(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '<'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '='){
        infoAtomo.atomo = MENOR_IGUAL;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = MENOR;
        return infoAtomo;
    }
}

//Reconhece > e >=
TInfoAtomo reconhece_maior(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '>'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '='){
        infoAtomo.atomo = MAIOR_IGUAL;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = MAIOR;
        return infoAtomo;
    }
    
}

// Reconhece atribuição (=) e comparação (==)
TInfoAtomo reconhece_atribuicao(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '='){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '='){
        infoAtomo.atomo = COMPARACAO;
        buffer++;
        return infoAtomo;
    }
    else {
        infoAtomo.atomo = ATRIBUICAO;
        return infoAtomo;
    }
    
}

// Reconhece divisão (/), comentário (//), começo de comentário (/*) e fim de comentário (*/)
TInfoAtomo reconhece_barra(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '/'){
        buffer++;
        goto q1;
    }
q1:
    if(*buffer == '/'){
        inCommentary = true;
        //Consome qualquer coisa ate chegar no quebra linha
        while(*buffer != '\n'){
            if(*buffer == '\0'){
                infoAtomo.atomo = ERRO;
                return infoAtomo;
            }
            buffer++;
            if(*buffer == '\n'){
                buffer++;
                linha++;
                inCommentary = false;
            }
        }
        
    }
    else if(*buffer == '*'){
        inCommentary = true;
        buffer++;
        goto q3;
    }
    else{
        infoAtomo.atomo = DIVISAO;
        return infoAtomo;
    }

q3:
    
    while(*buffer != '*'){
        
        if(*buffer == '\n'){
            buffer++;
            linha++;
        }
        if(*buffer == '\0'){
            inCommentary = false;
            infoAtomo.atomo = ERRO;
            return infoAtomo;
        }
        if(*buffer == '*'){
            buffer++;
            goto q4;
        }
        buffer++;
    }
    

q4:
    if(*buffer == '/'){
        inCommentary = false;
        buffer++;
        linha++;
        
    }
    else
        goto q3;
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

    return infoAtomo; 
}

TInfoAtomo reconhece_id(){
    TInfoAtomo infoAtomo;
    //Marca inicio do buffer
    char *iniLexema;
    iniLexema = buffer;

q0:
    if(*buffer == '_') {
        buffer++;
        goto q1;
    }
    printf("Erro 1");
    infoAtomo.atomo = ERRO;
    return infoAtomo;
q1:
    if(isalpha(*buffer)) {
        buffer++;
        goto q2;
    }
    printf("Erro 2");
    infoAtomo.atomo = ERRO;
    return infoAtomo;

q2:
    if(isalpha(*buffer)) {
        buffer++;
        goto q2;
    } else if(isdigit(*buffer)) {
        buffer++;
        goto q2;
    } else {
        goto q3;
    }
    printf("Erro 3");
    infoAtomo.atomo = ERRO;
    return infoAtomo;


q3:
    // recortar do buffer o lexema.
    if(buffer-iniLexema <= 15){
        // referencia:https://cplusplus.com/reference/cstring/strncpy/
        strncpy(infoAtomo.atributo_ID,iniLexema,buffer-iniLexema);
        infoAtomo.atributo_ID[buffer-iniLexema]='\0';// finaliza string
        infoAtomo.atomo = IDENTIFICADOR;
    } else {
        printf("Erro 4");
        infoAtomo.atomo = ERRO;
    }

    return infoAtomo;
}

TAtomo reconhece_num(){
q0:
    if(*buffer == '0' && *(++buffer) == 'x') { // Checa se o potencial número começa com o identificador de hexadecimal
        buffer++;
        goto q1;
    }
    printf("Erro 1");
    return ERRO;
    
q1:
    if(isdigit(*buffer)) { // Se for um número ou A|B|C|D|E|F, vai para o próximo estado
        buffer++;
        goto q2;
    } else if(*buffer == 'A'|| *buffer =='B' || *buffer =='C' || *buffer =='D' || *buffer =='E' || *buffer =='F') {
        buffer++;
        goto q2;
    }
    printf("Erro 2");
    return ERRO;

q2: 
    if(isdigit(*buffer)) { // Se for um número, A|B|C|D|E|F ou se terminar em ; termina
        buffer++;
        goto q2;
    } else if(*buffer == 'A'|| *buffer =='B' || *buffer =='C' || *buffer =='D' || *buffer =='E' || *buffer =='F') {
        buffer++;
        goto q2;
    } else { // Isso aqui está meme
        goto q3;
    }
    printf("Erro 3");
    return ERRO;

q3: 
    return NUMERO;
}

// Inicio funcoes analisador sintatico
void consome(TAtomo atomo){
    if (lookahead == atomo){
        infoAtomo = obter_atomo();
        lookahead = infoAtomo.atomo;

        printf("%d# %s ",infoAtomo.linha, strAtomo[infoAtomo.atomo]);
        
        if( infoAtomo.atomo == IDENTIFICADOR)
            printf("| %s",infoAtomo.atributo_ID);
        printf("\n");
    }
    else{
        printf("erro sintatico: esperado [%s] encontrado [%s], linha: %d \n",strAtomo[atomo],strAtomo[lookahead],infoAtomo.linha);
        exit(1);
    }
}

void programa(){
    consome(INT);
    consome(MAIN);
    consome(ABRE_PAR);
    consome(VOID);
    consome(FECHA_PAR);
    consome(ABRE_CHAVE);
    declaracoes();
    comandos();
    consome(FECHA_CHAVE);
}

void declaracoes(){
  while(lookahead == INT || lookahead == BOOL) {
    declaracao();
  }
}

void declaracao() {
  tipo();
  lista_variavel();
  consome(PONTO_VIRGULA);
}

void tipo(){
    if(lookahead == INT){
        consome(INT);
    }
    else if(lookahead == BOOL){
        consome(BOOL);
    }
    
}

void lista_variavel(){
    consome(IDENTIFICADOR);

    if(lookahead == VIRGULA){
        while(lookahead == VIRGULA){
            consome(VIRGULA);
            consome(IDENTIFICADOR);
        }
    }
}

void comandos(){
    while(lookahead == PONTO_VIRGULA || lookahead == IDENTIFICADOR || lookahead == IF || lookahead == WHILE || lookahead == SCANF || lookahead == PRINTF){
        comando();
    }
}

void comando(){
    if(lookahead == PONTO_VIRGULA){
        consome(PONTO_VIRGULA);
    }
    else if(lookahead == ABRE_CHAVE){
        bloco_comandos();
    }
    else if(lookahead == IDENTIFICADOR){
        atribuicao();
    }
    else if(lookahead == IF){
        comando_if();
    }
    else if(lookahead == WHILE){
        comando_while();
    }
    else if(lookahead == SCANF){
        comando_entrada();
    }
    else if(lookahead == PRINTF){
        comando_saida();
    }

}

void bloco_comandos(){
    consome(ABRE_CHAVE);
    comandos();
    consome(FECHA_CHAVE);
}

void atribuicao(){
    consome(IDENTIFICADOR);
    consome(ATRIBUICAO);
    expressao();
    consome(PONTO_VIRGULA);
}

void comando_if(){
  consome(IF);
  consome(ABRE_PAR);
  expressao();
  consome(FECHA_PAR);
  comando();
  if(lookahead == ELSE) {
    consome(ELSE);
    comando();
  }
}

void comando_while(){
    consome(WHILE);
    consome(ABRE_PAR);
    expressao();
    consome(FECHA_PAR);
    comando();
}

void comando_entrada(){
    consome(SCANF);
    consome(ABRE_PAR);
    lista_variavel();
    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
}

void comando_saida() {
  consome(PRINTF);
  consome(ABRE_PAR);
  expressao();
  if(lookahead == VIRGULA){
    while(lookahead == VIRGULA) {
        consome(VIRGULA);
        expressao();
    }
  }
  consome(FECHA_PAR);
  consome(PONTO_VIRGULA);
}

void expressao(){
    expressao_logica();
    if (lookahead == OR){
        while(lookahead == OR){
            consome(OR);
            expressao_logica();
        }
    }
}

void expressao_logica() {
  expressao_relacional();
  if(lookahead == AND) {
    while(lookahead == AND) {
      consome(AND);
      expressao_relacional();
    }
  }
}

void expressao_relacional(){
    expressao_adicao();
    if(lookahead == MENOR || lookahead == MENOR_IGUAL || lookahead == COMPARACAO || lookahead == DIFERENTE_IGUAL || lookahead == MAIOR || lookahead == MAIOR_IGUAL){
        op_relacional();
        expressao_adicao();
    }
}

void op_relacional(){
    if(lookahead == MENOR){
        consome(MENOR);
    }
    else if(lookahead == MENOR_IGUAL){
        consome(MENOR_IGUAL);
    }
    else if(lookahead == COMPARACAO){
        consome(COMPARACAO);
    }
    else if(lookahead == DIFERENTE_IGUAL){
        consome(DIFERENTE_IGUAL);
    }
    else if(lookahead == MAIOR){
        consome(MAIOR);
    }
    else if(lookahead == MAIOR_IGUAL){
        consome(MAIOR_IGUAL);
    }
}

void expressao_adicao() {
  expressao_multi();
  if(lookahead == SOMA || lookahead == SUBTRACAO) {
    while(lookahead == SOMA || lookahead == SUBTRACAO) {  
      if(lookahead == SOMA) {
        consome(SOMA);
      } else if(lookahead == SUBTRACAO) {
        consome(SUBTRACAO);
      }
      expressao_multi();
    }
  }
}

void expressao_multi(){
    operando();
    if (lookahead == MULTIPLICACAO || lookahead == DIVISAO){
        while(lookahead == MULTIPLICACAO || lookahead == DIVISAO){
            if(lookahead == MULTIPLICACAO){
                consome(MULTIPLICACAO);
            }
            else if(lookahead == DIVISAO){
                consome(DIVISAO);
            }
            operando();
        }
    }
}

void operando(){
    if(lookahead == IDENTIFICADOR){
        consome(IDENTIFICADOR);
    }
    else if(lookahead == NUMERO){
        consome(NUMERO);
    }
    else if(lookahead == TRUE){
        consome(TRUE);
    }
    else if(lookahead == FALSE){
        consome(FALSE);
    }
    else if(lookahead == IDENTIFICADOR){
        operando();
    }
}