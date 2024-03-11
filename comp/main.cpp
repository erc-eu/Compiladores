#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;




int verificarOperador(char op[]){
    char operadores [] = "=+-/*";
    for(int i = 0 ; i < strlen(operadores); i++){
        if(op[0] == operadores[i]){
            return 2;
        }
    }
    return 0;
}

bool verificarNumeros(char n)
{
    char num[] = "0123456789";
    for(int i = 0; i < strlen(num); i++){
        if(n == num[i]){
            return true;
        }
    }
    return false;
}

bool verificarLetra(char palavra){
    char str[] = "abcdefghijklmnopqrstuvxwyz";

    for (int i = 0 ; i < strlen(str); i++){
        if(palavra == str[i]){
            return true;
        }
    }
    return false;
}

bool verificarLetraNumero(char id[]){
    for(int i = 0; i < strlen(id); i++){
        if(verificarLetra(id[i]) == false && verificarNumeros(id[i]) == false){
            return false;
        }
    }
    return true;
}

int reconhecer_id(char id[]){
    if(verificarLetra(id[0]) == true)
    {
        if(verificarLetraNumero(id) == true) {
            return 1;
        }else{
            return 0;
        }
    }
    else{
       return 0;
    }
}

int buscarQtdVirgula(char n[]){
    int cont = 0;
    for(int i = 0; i < strlen(n); i++){
        if(n[i] == ','){
            cont ++;
        }
    }
    return cont;
}

bool chegouNaVirgula(char n[], int p){
    for (p; p < strlen(n); p++){
        if(n[p] == ','){
            return false;
        }
        if(verificarNumeros(n[p]) == false){
            return false;
        }
        if(verificarLetra(n[p]) == true){
            return false;
        }
    }
    return true;
}

bool verificarNumAntesDaVirgula(char n[]){
    bool chegou;
    for(int i = 0; i < strlen(n); i++){
        if(n[i] == ','){
            //chegou na virgula e não a mais nada a seguir retorna false por não ser um decimal
            if(i == strlen(n)-1){
                return false;
            }
            //chegando na primeira virgula, chama uma funcao para verificar os valores apos a virgula
            chegou = chegouNaVirgula(n, i+1);
            break;
        }
        //verifica os numeros antes da primeira virgula
        if(verificarNumeros(n[i]) == false && n[i] != ','){
            return false;
        }
        //verifica se há letras na palavra antes da primeira virgula
        if(verificarLetra(n[i]) == true && n[i] != ','){
            return false;
        }
    }
    if(chegou == false){
        return false;
    }
    return true;
}
bool verificarNumeroDecimal (char n[]) {

    if(verificarNumAntesDaVirgula(n) == false){
        return false;
    }
    return true;
}

int verificarLiteral (char literal[]){
    for(int i = 0; i < strlen(literal); i++){
        //verificarNumeros(literal[i]) -> verifica se há apenas numeros e se não é decimal
        //verificarNumeroDecimal(literal) -> faz as verificações quando for decimal
        if(verificarNumeros(literal[i]) == false && verificarNumeroDecimal(literal) == false){
            return 0;
        }
    }
    return 3;
}

void menu(){
    int i = 0;
    do {
        int op;
        printf("1 - identificador\n 2 - Operador\n 3 - literal inteiro\n 4 - literal decimal\n");
        scanf("%d", &op);
        switch(op){
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        }

    }while(i == 0);
}


struct guardaDados{
    char palavra[20];
    int estado;

    struct guardaDados* prox;
};

struct guardaDados* criar(){
    struct guardaDados* novo = (struct guardaDados*)malloc(sizeof(struct guardaDados));
    memset(novo->palavra, 0, 20);
    novo->estado = -1;
    novo->prox = NULL;
    return novo;
};

struct guardaDados* inserir(guardaDados* lista, char palavra[], int estado) {
    struct guardaDados* novo = (struct guardaDados*)malloc(sizeof(struct guardaDados));
    strcpy(novo->palavra, palavra);
    novo->estado = estado;
    novo->prox = NULL;

    if (lista == NULL) {
        return novo;
    } else {
        struct guardaDados* atual = lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
        return lista; // Retorna o primeiro nó da lista
    }
}

void imprimir(struct guardaDados* lista) {
     struct guardaDados* atual = lista;

    while (atual != NULL) {
        if (atual->estado == -1) {
            // Avança para o próximo nó apenas se atual não for nulo
            if (atual->prox != NULL) {
                atual = atual->prox;
            }
        } else if (atual->estado == 1) {
            printf("Token: {ID}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        } else if (atual->estado == 2) {
            printf("Token: {OP}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        } else if (atual->estado == 3) {
            printf("Token: {literal}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        } else if (atual->estado == 4){
            printf("Token: {ABRE_PARENTESES}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        } else if (atual->estado == 5){
            printf("Token: {FECHA_PARENTESES}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        } else if (atual->estado == 6) {
            printf("Token: {ERROR}, lexema: %s\n", atual->palavra);
            atual = atual->prox;
        }
    }
}
void leitor(char fluxo[]) {
    struct guardaDados* d = criar();
    char leitor[20];
    int j = 0;
    memset(leitor, 0, sizeof(leitor));

    for (int i = 0; i <= strlen(fluxo); i++) {
        if (fluxo[i] == ' ' || i == strlen(fluxo)) {
            // verifica se o fluxo é um ID e insere na struct
            if(reconhecer_id(leitor) == 1){
                d = inserir(d, leitor, 1);
            }
            else if(verificarOperador(leitor) == 2){
                d = inserir(d, leitor, 2);
            }
            else if(verificarLiteral(leitor) == 3){
                if(leitor[1] != 0){
                    d = inserir(d, leitor, 3);
                }
            }
            else if(leitor[0] == '('){
                d = inserir(d, "(", 4);
            }
            else if(leitor[0] == ')'){
                d = inserir(d, ")", 5);
            }
            else{
                d = inserir(d, leitor, 6);
            }
            memset(leitor, 0, sizeof(leitor));
            j = 0;
        } else {
            leitor[j] = fluxo[i];
            j++;
        }
    }
    imprimir(d);
    free(d);
}




int main()
{
    char id[] = "x1 = ( 1,232 + 32,2 )";
    char op[] = "+";
    char literal_int[10];
    char literal_float[10];
    leitor(id);
    strcpy(literal_int, "0,1");
    strcpy(literal_float, "2312232,3");

    printf("\n---------------------\n");
    printf("id = %s\n", id);
    printf("op = %c\n", op);
    printf("literal_int = %s\n", literal_int);
    printf("literal_float = %s\n", literal_float);

    printf("%d\n", reconhecer_id(id));
    printf("%d\n", verificarOperador(op));
    printf("%d\n", verificarLiteral(literal_int));
    printf("%d", verificarLiteral(literal_float));
}
