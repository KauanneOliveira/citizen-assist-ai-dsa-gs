#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// DEFINICOES, CONSTANTES E ESTRUTURAS
#define T_NOME 60
#define T_CATEGORIA 30
#define T_DESC 120
#define T_REQ 80
#define T_CIDADE 40
#define T_UF 3
#define T_TEL 20
#define T_HORARIO 30
#define ARQUIVO "servicos.txt"
#define POR_ID 1
#define POR_NOME 2
#define QTD_CATEGORIAS 6

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

// MANIPULACAO DA LISTA ENCADEADA
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

// libera todos os nos (free)  
void liberar_lista(Servico *cabeca) {
    Servico *atual = cabeca;
    while (atual != NULL) {
        Servico *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
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

// FUNCOES DE EXIBICAO E FORMATACAO
// formata o titulo da opcao escolhida
void titulo(const char *texto) {
    printf("\n\t\t%s\n", texto);
}

// formata a exibicao
void exibir_resumo(Servico *s) {
    printf("ID %d - %s\n", s->id, s->nome);
    printf("\tCategoria: %s\n", s->categoria);
    printf("\tLocal: %s-%s\n", s->cidade, s->estado);
    printf("\tTelefone: %s\n", s->telefone);
    printf("\tHorario: %s\n\n", s->horario);
}

// mostra todos os campos de um servico
void exibir_detalhe(Servico *s) {
    printf("ID %d - %s\n", s->id, s->nome);
    printf("\tCategoria: %s\n", s->categoria);
    printf("\tDescricao: %s\n", s->descricao);
    printf("\tRequisitos: %s\n", s->requisitos);
    printf("\tLocal: %s-%s\n", s->cidade, s->estado);
    printf("\tTelefone: %s\n", s->telefone);
    printf("\tHorario: %s\n\n", s->horario);
}

// percorre e exibe todos os nos  
void listar(Servico *cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Servico *atual = cabeca;
    while (atual != NULL) {
        exibir_resumo(atual);
        atual = atual->proximo;
    }
}

// ENTRADA DE DADOS E VALIDACAO 
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

// CADASTRO DE SERVICOS
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

// CONSULTAS E PESQUISAS
// consulta por id usando a busca sequencial
void consultar_por_id(Servico *cabeca) {
    int id;

    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    if (!ler_inteiro("ID para consulta: ", &id)) {
        printf("ID invalido.\n");
        return;
    }
    Servico *encontrado = buscar_por_id(cabeca, id);
    if (encontrado == NULL) {
        printf("Nenhum servico encontrado com o ID %d.\n", id);
        return;
    }
    exibir_detalhe(encontrado);
}

/* pesquisa por categoria: percorre a lista inteira (busca sequencial)
   e mostra todos os servicos que combinam */
void pesquisar_por_categoria(Servico *cabeca) {
    char categoria[T_CATEGORIA];
    int achou = 0;

    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    escolher_categoria(categoria);

    Servico *atual = cabeca;
    while (atual != NULL) {
        if (strcmp(atual->categoria, categoria) == 0) {
            exibir_resumo(atual);
            achou++;
        }
        atual = atual->proximo;
    }
    if (achou == 0) {
        printf("Nenhum servico encontrado na categoria %s.\n", categoria);
    } else {
        printf("Total encontrado: %d\n", achou);
    }
}

// pesquisa por estado, mesma logica da pesquisa por categoria
void pesquisar_por_estado(Servico *cabeca) {
    char estado[T_UF];
    int achou = 0;

    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ler_estado(estado);

    Servico *atual = cabeca;
    while (atual != NULL) {
        if (strcmp(atual->estado, estado) == 0) {
            exibir_resumo(atual);
            achou++;
        }
        atual = atual->proximo;
    }
    if (achou == 0) {
        printf("Nenhum servico encontrado no estado %s.\n", estado);
    } else {
        printf("Total encontrado: %d\n", achou);
    }
}

// submenu da opcao pesquisar
void menu_pesquisa(Servico *cabeca) {
    int op;

    printf("\n1 - Por categoria\n2 - Por estado\n0 - Voltar\n");
    if (!ler_inteiro("Opcao: ", &op)) {
        op = -1;
    }
    switch (op) {
        case 1: pesquisar_por_categoria(cabeca); break;
        case 2: pesquisar_por_estado(cabeca); break;
        case 0: break;
        default: printf("Opcao invalida.\n");
    }
}

// ATUALIZACAO E REMOCAO DE REGISTROS
// atualiza um unico campo do servico (o id nao pode ser alterado)
void atualizar(Servico *cabeca) {
    int id, op;

    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    if (!ler_inteiro("ID do servico a atualizar: ", &id)) {
        printf("ID invalido.\n");
        return;
    }
    Servico *s = buscar_por_id(cabeca, id);
    if (s == NULL) {
        printf("Nenhum servico encontrado com o ID %d.\n", id);
        return;
    }

    printf("\nServico atual:\n");
    exibir_detalhe(s);
    printf("Campo para alterar:\n");
    printf("\t1 - Nome\n\t2 - Categoria\n\t3 - Descricao\n\t4 - Requisitos\n");
    printf("\t5 - Cidade\n\t6 - Estado\n\t7 - Telefone\n\t8 - Horario\n\t0 - Cancelar\n");
    if (!ler_inteiro("Opcao: ", &op)) {
        op = -1;
    }

    switch (op) {
        case 1: ler_texto_obrigatorio("Novo nome: ", s->nome, T_NOME); break;
        case 2: escolher_categoria(s->categoria); break;
        case 3: ler_texto_obrigatorio("Nova descricao: ", s->descricao, T_DESC); break;
        case 4: ler_texto_obrigatorio("Novos requisitos: ", s->requisitos, T_REQ); break;
        case 5: ler_texto_obrigatorio("Nova cidade: ", s->cidade, T_CIDADE); break;
        case 6: ler_estado(s->estado); break;
        case 7: ler_texto_obrigatorio("Novo telefone: ", s->telefone, T_TEL); break;
        case 8: ler_texto_obrigatorio("Novo horario: ", s->horario, T_HORARIO); break;
        case 0: printf("Atualizacao cancelada.\n"); return;
        default: printf("Opcao invalida.\n"); return;
    }
    printf("Servico atualizado com sucesso.\n");
}

/* remove o servico pelo id, religando os ponteiros para manter a lista integra;
   devolve a cabeca (que muda se o primeiro no for removido) */
Servico *excluir(Servico *cabeca) {
    int id;

    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return cabeca;
    }
    if (!ler_inteiro("ID do servico a excluir: ", &id)) {
        printf("ID invalido.\n");
        return cabeca;
    }

    Servico *atual = cabeca;
    Servico *anterior = NULL;
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Nenhum servico encontrado com o ID %d.\n", id);
        return cabeca;
    }

    if (anterior == NULL) {
        cabeca = atual->proximo; // removendo o primeiro no
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Servico removido com sucesso.\n");
    return cabeca;
}

// ORDENACAO E COMPARACAO
// compara dois textos ignorando maiusculas e minusculas
int comparar_texto(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        int ca = tolower((unsigned char) a[i]);
        int cb = tolower((unsigned char) b[i]);
        if (ca != cb) {
            return ca - cb;
        }
        i++;
    }
    return tolower((unsigned char) a[i]) - tolower((unsigned char) b[i]);
}

// compara dois nos pelo criterio; negativo se "a" deve vir antes de "b"
int comparar(Servico *a, Servico *b, int criterio) {
    if (criterio == POR_ID) {
        return a->id - b->id;
    }
    return comparar_texto(a->nome, b->nome);
}

// troca os dados de dois nos, mantendo cada ponteiro proximo no lugar
void trocar_dados(Servico *a, Servico *b) {
    Servico temp = *a;
    Servico *proxA = a->proximo;
    Servico *proxB = b->proximo;

    *a = *b;
    *b = temp;
    a->proximo = proxA;
    b->proximo = proxB;
}

/* ordena a lista com insertion sort pelo criterio (id crescente ou nome a-z).
   o inicio da lista e a parte ja ordenada; a cada passo, o proximo no
   e encaixado na posicao certa deslocando os dados com trocas */
void ordenar_lista(Servico *cabeca, int criterio) {
    if (cabeca == NULL || cabeca->proximo == NULL) {
        return;
    }

    Servico *ultimo = cabeca; // ultimo no da parte ordenada
    while (ultimo->proximo != NULL) {
        Servico *atual = ultimo->proximo; // no a ser encaixado

        if (comparar(ultimo, atual, criterio) <= 0) {
            ultimo = atual; // ja esta na posicao certa
        } else {
            // acha o primeiro no da parte ordenada que deve vir depois do atual
            Servico *pos = cabeca;
            while (comparar(pos, atual, criterio) <= 0) {
                pos = pos->proximo;
            }
            // empurra os dados para frente ate chegar no atual
            Servico *k = pos;
            while (k != atual) {
                trocar_dados(k, atual);
                k = k->proximo;
            }
            ultimo = atual; // a parte ordenada agora inclui o atual
        }
    }
}

// mostra a lista ordenada por nome e depois volta a lista para a ordem de id
void ordenar(Servico *cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ordenar_lista(cabeca, POR_NOME);
    printf("Lista ordenada por nome (A-Z):\n\n");
    listar(cabeca);
    ordenar_lista(cabeca, POR_ID);
}

// ANALISE E RELATORIOS
// mostra o total de servicos e a quantidade por categoria
void analisar(Servico *cabeca) {
    int contagem[QTD_CATEGORIAS] = {0};
    int total = 0;

    if (cabeca == NULL) {
        printf("Lista vazia.\n\n");
    }

    Servico *atual = cabeca;
    while (atual != NULL) {
        total++;
        for (int i = 0; i < QTD_CATEGORIAS; i++) {
            if (strcmp(atual->categoria, CATEGORIAS[i]) == 0) {
                contagem[i]++;
                break;
            }
        }
        atual = atual->proximo;
    }

    printf("Total de servicos: %d\n", total);
    for (int i = 0; i < QTD_CATEGORIAS; i++) {
        printf("\t%s: %d\n", CATEGORIAS[i], contagem[i]);
    }
}

// MANIPULACAO DE ARQUIVOS
// le uma linha do arquivo e remove o \n e retorna 0 se acabou o arquivo
int ler_linha_arquivo(FILE *arq, char *dest, int tam) {
    if (fgets(dest, tam, arq) == NULL) {
        return 0;
    }
    if (strchr(dest, '\n') == NULL) {
        int c;
        // descarta o resto da linha que nao coube no campo
        while ((c = fgetc(arq)) != '\n' && c != EOF) { }
    }
    dest[strcspn(dest, "\n")] = '\0';
    return 1;
}

/* grava a lista inteira no arquivo
   retorna 1 se deu certo e 0 se nao conseguiu abrir */
int salvar(Servico *cabeca) {
    FILE *arq = fopen(ARQUIVO, "w");
    if (arq == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return 0;
    }
    Servico *atual = cabeca;
    while (atual != NULL) {
        fprintf(arq, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                atual->id, atual->nome, atual->categoria, atual->descricao,
                atual->requisitos, atual->cidade, atual->estado,
                atual->telefone, atual->horario);
        atual = atual->proximo;
    }
    fclose(arq);
    return 1;
}

void salvar_por_id(Servico *cabeca) {
    ordenar_lista(cabeca, POR_ID);
    salvar(cabeca);
}

/* le o arquivo e monta a lista encadeada;
   se o arquivo nao existe (primeira execucao), devolve lista vazia */
Servico *carregar(void) {
    Servico *cabeca = NULL;
    FILE *arq = fopen(ARQUIVO, "r");
    if (arq == NULL) {
        return NULL;
    }

    int id, c;
    char nome[T_NOME], categoria[T_CATEGORIA], descricao[T_DESC];
    char requisitos[T_REQ], cidade[T_CIDADE], estado[T_UF];
    char telefone[T_TEL], horario[T_HORARIO];

    while (fscanf(arq, "%d", &id) == 1) {
        // descarta o resto da linha do id
        while ((c = fgetc(arq)) != '\n' && c != EOF) { }

        if (!ler_linha_arquivo(arq, nome, T_NOME) ||
            !ler_linha_arquivo(arq, categoria, T_CATEGORIA) ||
            !ler_linha_arquivo(arq, descricao, T_DESC) ||
            !ler_linha_arquivo(arq, requisitos, T_REQ) ||
            !ler_linha_arquivo(arq, cidade, T_CIDADE) ||
            !ler_linha_arquivo(arq, estado, T_UF) ||
            !ler_linha_arquivo(arq, telefone, T_TEL) ||
            !ler_linha_arquivo(arq, horario, T_HORARIO)) {
            break; // registro incompleto no arquivo
        }

        Servico *novo = criar_no(id, nome, categoria, descricao, requisitos,
                                 cidade, estado, telefone, horario);
        if (novo == NULL) {
            break;
        }
        cabeca = inserir_final(cabeca, novo);
    }
    fclose(arq);
    return cabeca;
}

// FUNCAO PRINCIPAL 
int main(void) {
    Servico *lista = carregar();
    ordenar_lista(lista, POR_ID); // garante a ordem de id mesmo com arquivo antigo
    int op;

    do {
        printf("\n1 - Cadastrar\n2 - Listar\n3 - Consultar por ID\n4 - Pesquisar\n5 - Atualizar\n6 - Excluir\n7 - Ordenar por nome\n8 - Analise\n0 - Sair\n");
        if (!ler_inteiro("Opcao: ", &op)) {
            op = -1;
        }
        switch (op) {
            case 1:
                titulo("CADASTRO");
                lista = cadastrar(lista);
                salvar_por_id(lista);
                break;
            case 2:
                titulo("LISTAR");
                listar(lista);
                break;
            case 3:
                titulo("CONSULTA POR ID");
                consultar_por_id(lista);
                break;
            case 4:
                titulo("PESQUISAR");
                menu_pesquisa(lista);
                break;
            case 5:
                titulo("ATUALIZAR");
                atualizar(lista);
                salvar_por_id(lista);
                break;
            case 6:
                titulo("EXCLUIR");
                lista = excluir(lista);
                salvar_por_id(lista);
                break;
            case 7:
                titulo("ORDENAR");
                ordenar(lista);
                break;
            case 8:
                titulo("ANALISE");
                analisar(lista);
                break;
            case 0:
               printf("\t\tENCERRADO\n");
                break;
            default: 
                printf("Opcao invalida.\n");
        }
    } while (op != 0);

    liberar_lista(lista);
    return 0;
}