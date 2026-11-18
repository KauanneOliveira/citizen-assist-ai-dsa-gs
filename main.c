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

// ENTRADA DE DADOS E VALIDACAO 
#define QTD_CATEGORIAS 6

const char *CATEGORIAS[QTD_CATEGORIAS] = {
    "Delegacia e seguranca",
    "Acolhimento e abrigo",
    "Apoio juridico",
    "Saude",
    "Apoio psicologico",
    "Canal de denuncia"
};

// descarta o que sobrou na linha digitada
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// le texto com espacos e remove o \n
void ler_texto(const char *msg, char *dest, int tam) {
    printf("%s", msg);
    if (fgets(dest, tam, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    if (strchr(dest, '\n') == NULL) {
        limpar_buffer();  //  texto maior que o campo: descarta o excesso
    }
    dest[strcspn(dest, "\n")] = '\0';
}

// repete ate o usuario digitar algo
void ler_texto_obrigatorio(const char *msg, char *dest, int tam) {
    do {
        ler_texto(msg, dest, tam);
        if (dest[0] == '\0') {
            printf("Campo obrigatorio. Tente novamente.\n");
        }
    } while (dest[0] == '\0');
}

// le um inteiro e retorna 1 se valido, 0 se digitou letras
int ler_inteiro(const char *msg, int *valor) {
    printf("%s", msg);
    if (scanf("%d", valor) != 1) {
        limpar_buffer();
        return 0;
    }
    limpar_buffer();
    return 1;
}

// busca sequencial por ID; retorna o no ou NULL
Servico *buscar_por_id(Servico *cabeca, int id) {
    Servico *atual = cabeca;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// mostra o menu de categorias e copia a escolhida
void escolher_categoria(char *dest) {
    int op;
    while (1) {
        printf("Categorias:\n");
        for (int i = 0; i < QTD_CATEGORIAS; i++) {
            printf("  %d - %s\n", i + 1, CATEGORIAS[i]);
        }
        if (ler_inteiro("Escolha a categoria: ", &op) && op >= 1 && op <= QTD_CATEGORIAS) {
            strcpy(dest, CATEGORIAS[op - 1]);
            return;
        }
        printf("Opcao invalida.\n");
    }
}

// le a UF: exatamente 2 letras e guarda em maiuscula
void ler_estado(char *dest) {
    char tmp[20];
    while (1) {
        ler_texto("Estado (sigla UF, ex.: SP): ", tmp, sizeof(tmp));
        if (strlen(tmp) == 2) {
            char a = tmp[0], b = tmp[1];
            if (a >= 'a' && a <= 'z') a = a - 32;
            if (b >= 'a' && b <= 'z') b = b - 32;
            if (a >= 'A' && a <= 'Z' && b >= 'A' && b <= 'Z') {
                dest[0] = a;
                dest[1] = b;
                dest[2] = '\0';
                return;
            }
        }
        printf("Estado invalido. Digite 2 letras.\n");
    }
}

// cadastra um servico lendo do teclado e devolve a cabeca
Servico *cadastrar(Servico *cabeca) {
    int id;
    char nome[T_NOME], categoria[T_CATEGORIA], descricao[T_DESC];
    char requisitos[T_REQ], cidade[T_CIDADE], estado[T_UF];
    char telefone[T_TEL], horario[T_HORARIO];

    if (!ler_inteiro("ID (numero positivo): ", &id) || id <= 0) {
        printf("ID invalido.\n");
        return cabeca;
    }
    if (buscar_por_id(cabeca, id) != NULL) {
        printf("Ja existe um servico com o ID %d.\n", id);
        return cabeca;
    }

    ler_texto_obrigatorio("Nome: ", nome, T_NOME);
    escolher_categoria(categoria);
    ler_texto_obrigatorio("Descricao: ", descricao, T_DESC);
    ler_texto_obrigatorio("Requisitos: ", requisitos, T_REQ);
    ler_texto_obrigatorio("Cidade: ", cidade, T_CIDADE);
    ler_estado(estado);
    ler_texto_obrigatorio("Telefone: ", telefone, T_TEL);
    ler_texto_obrigatorio("Horario de funcionamento: ", horario, T_HORARIO);

    Servico *novo = criar_no(id, nome, categoria, descricao, requisitos,
                             cidade, estado, telefone, horario);
    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return cabeca;
    }
    printf("Servico cadastrado com sucesso.\n");
    return inserir_final(cabeca, novo);
}

// MAIN   
int main(void) {
    Servico *lista = NULL;
    int op;

    do {
        printf("\n1 - Cadastrar\n2 - Listar\n0 - Sair\n");
        if (!ler_inteiro("Opcao: ", &op)) {
            op = -1;
        }
        switch (op) {
            case 1: lista = cadastrar(lista); break;
            case 2: listar(lista); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);

    liberar_lista(lista);
    return 0;
}