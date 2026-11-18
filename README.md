# Citizen Assist AI - Rede de Apoio à Mulher

Global Solution 2026.2 - Data Structures and Algorithms (DSA). Protótipo em C, executado no terminal.

## 1. Recorte escolhido

O sistema cadastra **serviços de proteção e apoio à mulher em situação de violência** (delegacias, abrigos, apoio jurídico, saúde, apoio psicológico e canais de denúncia). Ele guarda informações dos **serviços**, e não de vítimas ou agressores, por isso não trata dados pessoais sensíveis.

## 2. Como compilar e executar

```
gcc -Wall -Wextra main.c -o citizen_assist
.\citizen_assist
```

No Windows, execute `citizen_assist.exe`. O arquivo `servicos.txt` é criado na pasta de onde o programa é executado.

## 3. Modelo dos registros

Cada serviço é um nó da lista (`struct Servico`):

| Campo | Tipo | Tamanho do vetor | Descrição |
|---|---|---|---|
| id | int | - | identificador único, digitado pelo usuário (positivo) |
| nome | char[] | 60 | nome do serviço |
| categoria | char[] | 30 | uma das 6 categorias fixas |
| descricao | char[] | 120 | o que o serviço oferece |
| requisitos | char[] | 80 | o que é preciso para acessar |
| cidade | char[] | 40 | cidade |
| estado | char[] | 3 | sigla da UF (2 letras, gravada em maiúscula) |
| telefone | char[] | 20 | telefone de contato |
| horario | char[] | 30 | horário de funcionamento |
| proximo | ponteiro | - | próximo nó da lista |

O tamanho do vetor inclui o `\0`, e textos maiores que o campo são cortados.

Categorias: Delegacia e seguranca, Acolhimento e abrigo, Apoio juridico, Saude, Apoio psicologico, Canal de denuncia.

## 4. Lista encadeada

Lista **simplesmente encadeada**, implementada pela equipe com `struct`, `typedef`, ponteiros e alocação dinâmica. A variável `lista` do `main` guarda o primeiro nó.

| Operação | Função | Como funciona |
|---|---|---|
| Criação do nó | `criar_no` | `malloc`; devolve `NULL` se faltar memória |
| Inserção | `inserir_final` | percorre até o último nó e liga o novo |
| Percurso | `listar` | segue `proximo` até `NULL` |
| Remoção | `excluir` | religa o ponteiro do nó anterior (ou a cabeça) e usa `free` |
| Liberação | `liberar_lista` | `free` em todos os nós ao encerrar |

A lista é mantida em ordem crescente de ID.

## 5. Menu

| Opção | Função | Descrição |
|---|---|---|
| 1 | `cadastrar` | lê os campos, valida e insere no final |
| 2 | `listar` | exibe todos os serviços |
| 3 | `consultar_por_id` | exibe todos os campos de um serviço |
| 4 | `menu_pesquisa` | pesquisa por categoria ou por estado |
| 5 | `atualizar` | altera um campo por vez (o ID não muda) |
| 6 | `excluir` | remove um serviço pelo ID |
| 7 | `ordenar` | exibe a lista ordenada por nome (A-Z); depois a lista volta à ordem de ID |
| 8 | `analisar` | total de serviços e quantidade por categoria (as 6 sempre aparecem) |
| 0 | - | encerra e libera a memória |

Tratamentos: opção inválida, ID inválido ou duplicado, ID inexistente, campo obrigatório vazio, UF inválida, categoria inválida e lista vazia.

## 6. Algoritmos

**Busca sequencial** (`buscar_por_id`, `pesquisar_por_categoria`, `pesquisar_por_estado`): começa no primeiro nó e segue `proximo`, comparando o campo buscado. Na busca por ID, para no primeiro nó encontrado (o ID é único). Nas pesquisas por categoria e estado, percorre a lista inteira e exibe todos os que combinam. Se nada é encontrado, o programa informa.

**Insertion Sort** (`ordenar_lista`): o início da lista é a parte já ordenada. A cada passo, o próximo nó é comparado com o último da parte ordenada; se já está no lugar, a parte ordenada cresce, senão o programa acha a posição correta e desloca os dados com trocas (`trocar_dados`) até encaixá-lo. A função recebe o critério (ID crescente ou nome A-Z) e, no nome, a comparação ignora maiúsculas e minúsculas (`comparar_texto`).

## 7. Persistência

Os dados ficam em `servicos.txt`, **9 linhas por serviço**, na ordem: id, nome, categoria, descricao, requisitos, cidade, estado, telefone, horario. O arquivo é lido ao iniciar e gravado após cada cadastro, atualização ou exclusão, sempre em ordem de ID.

## 8. Limitações conhecidas

- A comparação de nomes não trata acentos. Recomenda-se cadastrar sem acento.
- Textos maiores que o campo são cortados.
- Um ID digitado como `12abc` é lido como `12`.

## 9. Dados de exemplo para os testes

Os dados abaixo são **fictícios** (telefones e descrições ilustrativos) e servem só para testar o sistema. Há duas formas de usá-los.

### 9.1 Carregar direto pelo arquivo

Crie o arquivo `servicos.txt` na pasta de onde o programa é executado com o conteúdo abaixo (9 linhas por serviço) e inicie o programa. Os 6 serviços já aparecem na lista.

```
1
Ligue 180
Canal de denuncia
Central de atendimento
Nenhum
Brasilia
DF
180
24h
2
Delegacia da Mulher
Delegacia e seguranca
Atendimento policial
Documento com foto
Sao Paulo
SP
(11) 0000-0000
24h
3
Casa da Mulher Brasileira
Acolhimento e abrigo
Atendimento integrado
Nenhum
Campo Grande
MS
(67) 0000-0000
24h
4
Delegacia de Defesa da Mulher
Delegacia e seguranca
Registro de ocorrencia
Documento com foto
Campinas
SP
(19) 0000-0000
8h as 18h
5
Abrigo Seguro
Acolhimento e abrigo
Acolhimento temporario
Encaminhamento
Recife
PE
(81) 0000-0000
24h
6
defensoria publica
Apoio juridico
Orientacao juridica gratuita
Documento com foto
Belo Horizonte
MG
(31) 0000-0000
8h as 17h
```

### 9.2 Cadastrar pelo menu (opção 1)

Apague o `servicos.txt` (se existir) e cadastre os serviços abaixo. O programa pede os campos nesta ordem: ID, Nome, Categoria (número), Descrição, Requisitos, Cidade, Estado, Telefone e Horário.

| ID | Nome | Categoria | Descrição | Requisitos | Cidade | UF | Telefone | Horário |
|---|---|---|---|---|---|---|---|---|
| 1 | Ligue 180 | 6 | Central de atendimento | Nenhum | Brasilia | DF | 180 | 24h |
| 2 | Delegacia da Mulher | 1 | Atendimento policial | Documento com foto | Sao Paulo | SP | (11) 0000-0000 | 24h |
| 3 | Casa da Mulher Brasileira | 2 | Atendimento integrado | Nenhum | Campo Grande | MS | (67) 0000-0000 | 24h |
| 4 | Delegacia de Defesa da Mulher | 1 | Registro de ocorrencia | Documento com foto | Campinas | SP | (19) 0000-0000 | 8h as 18h |
| 5 | Abrigo Seguro | 2 | Acolhimento temporario | Encaminhamento | Recife | PE | (81) 0000-0000 | 24h |
| 6 | defensoria publica | 3 | Orientacao juridica gratuita | Documento com foto | Belo Horizonte | MG | (31) 0000-0000 | 8h as 17h |

Números das categorias: 1 Delegacia e seguranca, 2 Acolhimento e abrigo, 3 Apoio juridico, 4 Saude, 5 Apoio psicologico, 6 Canal de denuncia.

Nenhum serviço de Saúde ou Apoio psicológico foi incluído de propósito, para que a análise mostre categorias com zero.

### 9.3 Resultados esperados com esses 6 serviços

| Ação | Resultado esperado |
|---|---|
| Opção 7 (ordenar por nome) | IDs na ordem 5, 3, 6, 2, 4, 1; o nome `defensoria publica`, em minúsculo, fica entre Casa e Delegacia (a comparação ignora maiúsculas) |
| Opção 2 (listar), logo depois | IDs na ordem 1, 2, 3, 4, 5, 6 (a lista volta para a ordem de ID) |
| Opção 8 (análise) | Total 6; Delegacia e seguranca: 2; Acolhimento e abrigo: 2; Apoio juridico: 1; Saude: 0; Apoio psicologico: 0; Canal de denuncia: 1 |
| Opção 4, por categoria, `2` | IDs 3 e 5 e `Total encontrado: 2` |
| Opção 4, por estado, `SP` | IDs 2 e 4 e `Total encontrado: 2` |
| Opção 4, por estado, `RJ` | `Nenhum servico encontrado no estado RJ.` |
| Opção 3, ID `99` | `Nenhum servico encontrado com o ID 99.` |
| Opção 1, ID `1` de novo | `Ja existe um servico com o ID 1.` |