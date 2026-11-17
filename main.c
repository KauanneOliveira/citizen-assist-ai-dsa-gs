#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ESTRUTURA DO REGISTRO (NO DA LISTA)
#define T_NOME 60
#define T_CATEGORIA 30
#define T_DESC 120
#define T_REQ 80
#define T_CIDADE 40
#define T_UF 3
#define T_TEL 20
#define T_HORARIO 30

typedef struct Servico {
    int id;
    char nome[T_NOME];
    char categoria[T_CATEGORIA];
    char descricao[T_DESC];
    char requisitos[T_REQ];
    char cidade[T_CIDADE];
    char estado[T_UF];
    char telefone[T_TEL];
    char horario[T_HORARIO];
    struct Servico *proximo;
} Servico;

// LISTA ENCADEADA

// cria um no com malloc e retorna NULL se faltar memoria
Servico *criar_no(int id, const char *nome, const char *categoria,
                  const char *descricao, const char *requisitos,
                  const char *cidade, const char *estado,
                  const char *telefone, const char *horario) {
    Servico *novo = (Servico *) malloc(sizeof(Servico));
    if (novo == NULL) {
        return NULL;
    }
    novo->id = id;
    strncpy(novo->nome, nome, T_NOME - 1);             novo->nome[T_NOME - 1] = '\0';
    strncpy(novo->categoria, categoria, T_CATEGORIA - 1); novo->categoria[T_CATEGORIA - 1] = '\0';
    strncpy(novo->descricao, descricao, T_DESC - 1);   novo->descricao[T_DESC - 1] = '\0';
    strncpy(novo->requisitos, requisitos, T_REQ - 1);  novo->requisitos[T_REQ - 1] = '\0';
    strncpy(novo->cidade, cidade, T_CIDADE - 1);       novo->cidade[T_CIDADE - 1] = '\0';
    strncpy(novo->estado, estado, T_UF - 1);           novo->estado[T_UF - 1] = '\0';
    strncpy(novo->telefone, telefone, T_TEL - 1);      novo->telefone[T_TEL - 1] = '\0';
    strncpy(novo->horario, horario, T_HORARIO - 1);    novo->horario[T_HORARIO - 1] = '\0';
    novo->proximo = NULL;
    return novo;
}

// insere no final e devolve a cabeca da lista  
Servico *inserir_final(Servico *cabeca, Servico *novo) {
    if (cabeca == NULL) {
        return novo;
    }
    Servico *atual = cabeca;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return cabeca;
}

// percorre e exibe todos os nos  
void listar(Servico *cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Servico *atual = cabeca;
    while (atual != NULL) {
        printf("ID: %d | %s | %s | %s-%s\n",
               atual->id, atual->nome, atual->categoria,
               atual->cidade, atual->estado);
        atual = atual->proximo;
    }
}

// libera todos os nos (free)  
void liberar_lista(Servico *cabeca) {
    Servico *atual = cabeca;
    while (atual != NULL) {
        Servico *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

// MAIN   
int main(void) {
    Servico *lista = NULL;

    listar(lista);

    lista = inserir_final(lista, criar_no(1, "Ligue 180", "Canal de denuncia",
            "Central de atendimento", "Nenhum", "Brasilia", "DF", "180", "24h"));
    lista = inserir_final(lista, criar_no(2, "Delegacia da Mulher", "Delegacia e seguranca",
            "Atendimento policial", "Documento com foto", "Sao Paulo", "SP", "(11) 0000-0000", "24h"));
    lista = inserir_final(lista, criar_no(3, "Casa da Mulher Brasileira", "Acolhimento e abrigo",
            "Atendimento integrado", "Nenhum", "Campo Grande", "MS", "(67) 0000-0000", "24h"));

    printf("--- Apos 3 insercoes ---\n");
    listar(lista);

    liberar_lista(lista);
    printf("Memoria liberada.\n");
    return 0;
}