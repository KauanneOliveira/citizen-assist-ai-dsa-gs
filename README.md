# Citizen Assist AI - Rede de Apoio à Mulher

Global Solution 2026.2 - Data Structures and Algorithms (DSA). Protótipo em C, executado no terminal.

## Identificação Acadêmica
**Disciplina**: Data Structures and Algorithms <br>
**Curso**: Ciências da Computação - 1º Ano <br>
**Turma**: 1CCPI <br>
**Integrantes**:

| Nome | RM |
|------|----|
| Kauanne Paula de Oliveira | 574191 |
| Nayhely Estela Calle Castillo | 571416 |

## 1. Recorte escolhido

O sistema cadastra **serviços de proteção e apoio à mulher em situação de violência** (delegacias, abrigos, apoio jurídico, saúde, apoio psicológico e canais de denúncia). Ele guarda informações dos **serviços**, e não de vítimas ou agressores, por isso não trata dados pessoais sensíveis.

## 2. Como compilar e executar

```
gcc main.c -o citizen_assist
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
| Criação do nó | `criar_no` | `malloc` e devolve `NULL` se faltar memória |
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
| 7 | `ordenar` | exibe a lista ordenada por nome (A-Z). Depois a lista volta à ordem de ID |
| 8 | `analisar` | total de serviços e quantidade por categoria (as 6 sempre aparecem) |
| 0 | - | encerra e libera a memória |

Tratamentos: opção inválida, ID inválido ou duplicado, ID inexistente, campo obrigatório vazio, UF inválida, categoria inválida e lista vazia.

## 6. Algoritmos

**Busca sequencial** (`buscar_por_id`, `pesquisar_por_categoria`, `pesquisar_por_estado`): começa no primeiro nó e segue `proximo`, comparando o campo buscado. Na busca por ID, para no primeiro nó encontrado (o ID é único). Nas pesquisas por categoria e estado, percorre a lista inteira e exibe todos os que combinam. Se nada é encontrado, o programa informa.

**Insertion Sort** (`ordenar_lista`): o início da lista é a parte já ordenada. A cada passo, o próximo nó é comparado com o último da parte ordenada; se já está no lugar, a parte ordenada cresce, senão o programa acha a posição correta e desloca os dados com trocas (`trocar_dados`) até encaixá-lo. A função recebe o critério (ID crescente ou nome A-Z) e, no nome, a comparação ignora maiúsculas e minúsculas (`comparar_texto`).

## 7. Análise de complexidade (Big-O)

| Operação | Função | Melhor caso | Pior caso |
|---|---|---|---|
| Inserção no final | `inserir_final` | O(1) (lista vazia) | O(n) |
| Cadastro completo | `cadastrar` | O(n) | O(n) |
| Busca por ID | `buscar_por_id` | O(1) (primeiro nó) | O(n) |
| Pesquisa por categoria ou estado | `pesquisar_por_categoria`, `pesquisar_por_estado` | O(n) | O(n) |
| Remoção | `excluir` | O(1) (primeiro nó) | O(n) |
| Ordenação (Insertion Sort) | `ordenar_lista` | O(n) (já ordenada) | O(n²) (ordem inversa) |
| Exibir ordenado por nome | `ordenar` | O(n) | O(n²) |
| Percurso | `listar` | O(n) | O(n) |
| Análise (indicador) | `analisar` | O(n) | O(n) |
| Gravar no arquivo | `salvar` | O(n) | O(n) |
| Carregar do arquivo | `carregar` | O(n²) | O(n²) |

**Inserção**: a inserção é feita no final. Como a lista não guarda o ponteiro do último nó, `inserir_final` percorre a lista até encontrá-lo, o que custa O(n); só na lista vazia o novo nó vira a cabeça em O(1). O cadastro completo também é O(n): busca de ID duplicado (O(n)), inserção (O(n)), reordenação por ID e gravação no arquivo (ambas O(n)). A reordenação é linear porque, depois da inserção, no máximo um nó está fora de lugar. Com um ponteiro para o último nó a inserção cairia para O(1), mas isso não foi implementado.

**Busca**: a busca é sequencial. Começa na cabeça e segue `proximo`. Na busca por ID, o melhor caso é O(1) (registro no primeiro nó) e o pior é O(n) (último nó ou ID inexistente). Nas pesquisas por categoria e estado, a lista é sempre percorrida inteira, pois podem existir vários resultados, então o custo é O(n) em qualquer caso. A busca binária não se aplica, pois a lista encadeada não dá acesso direto ao elemento do meio.

**Remoção**: `excluir` percorre a lista guardando o nó anterior até achar o ID (O(n) no pior caso, O(1) se for o primeiro nó). Religar o ponteiro do anterior (ou a cabeça) e liberar o nó com `free` custa O(1). O custo total é O(n).

**Ordenação**: foi usado o Insertion Sort com troca de dados entre os nós (`trocar_dados`). No melhor caso (lista já ordenada), cada nó é comparado só com o último da parte ordenada, o que dá n-1 comparações e O(n). No pior caso (ordem inversa), cada nó é deslocado por toda a parte ordenada, o que dá cerca de n(n-1)/2 comparações e trocas, ou seja, O(n²). O caso médio também é O(n²). O espaço adicional é O(1), pois só há ponteiros auxiliares e uma estrutura temporária na troca. O algoritmo é estável, porque a comparação usa `<=` e registros iguais mantêm a ordem relativa. Cada troca copia o registro inteiro, custo constante por troca que não muda a classe de complexidade. A opção 7 faz duas ordenações (por nome e de volta por ID) mais um percurso, então custa O(n²) no pior caso.

**Demais operações**: `listar`, `analisar` (um percurso com no máximo 6 comparações por nó) e `salvar` são O(n). A atualização de um campo custa O(n) pela busca do ID, e a regravação do arquivo também é O(n). `carregar` é O(n²), pois chama `inserir_final` (O(n)) para cada um dos n registros lidos.

**Observações**: *n* é a quantidade de serviços na lista. A comparação de textos é tratada como custo constante, porque os campos têm tamanho fixo (no máximo 119 caracteres). A leitura do teclado é desconsiderada. A análise segue a implementação efetiva: lista simplesmente encadeada sem ponteiro para o último nó.

## 8. Persistência

Os dados ficam em `servicos.txt`, **9 linhas por serviço**, na ordem: id, nome, categoria, descricao, requisitos, cidade, estado, telefone, horario. O arquivo é lido ao iniciar e gravado após cada cadastro, atualização ou exclusão, sempre em ordem de ID.

## 9. Limitações conhecidas

- A comparação de nomes não trata acentos. Recomenda-se cadastrar sem acento.
- Textos maiores que o campo são cortados.
- Um ID digitado como `12abc` é lido como `12`.

## 10. Dados de exemplo para os testes

Os dados abaixo são **fictícios** (telefones e descrições ilustrativos) e servem só para testar o sistema. Há duas formas de usá-los.

### 10.1 Carregar direto pelo arquivo

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

### 10.2 Cadastrar pelo menu (opção 1)

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

### 10.3 Resultados esperados com esses 6 serviços

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

## 11. Evidências de testes

Os testes usam os dados da seção 10. Os grupos 11.1 e 11.2 partem de uma execução **sem** `servicos.txt`; do grupo 11.3 em diante, o `servicos.txt` é o da seção 10.1 (6 serviços). Todos os testes foram executados e o resultado observado foi o esperado. Os prints ficam na pasta `evidencias/`, nomeados pelo número do teste (`teste-01.png`, `teste-02.png`, ...). Casos repetitivos de um mesmo grupo (por exemplo, a mensagem `Lista vazia.` em várias opções) podem não ter print próprio e foram executados com o mesmo resultado.

### 11.1 Lista vazia (sem `servicos.txt`)

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 1 | opção `2` | `Lista vazia.` | Conforme o esperado |
| 2 | opção `3` | `Lista vazia.` | Conforme o esperado |
| 3 | opção `4`, depois `1` | `Lista vazia.` | Conforme o esperado |
| 4 | opção `4`, depois `2` | `Lista vazia.` | Conforme o esperado |
| 5 | opção `5` | `Lista vazia.` | Conforme o esperado |
| 6 | opção `6` | `Lista vazia.` | Conforme o esperado |
| 7 | opção `7` | `Lista vazia.` | Conforme o esperado |
| 8 | opção `8` | `Lista vazia.`, `Total de servicos: 0` e as 6 categorias com `0` | Conforme o esperado |

### 11.2 Menu principal

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 9 | opção `9` | `Opcao invalida.` e o menu volta | Conforme o esperado |
| 10 | opção `abc` | `Opcao invalida.` e o menu volta | Conforme o esperado |

### 11.3 Carga, consulta e pesquisa (com os 6 serviços da seção 10.1)

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 11 | iniciar o programa e opção `2` | os 6 serviços na ordem de ID (1 a 6), carregados do arquivo | Conforme o esperado |
| 12 | opção `3`, ID `3` | os campos completos de Casa da Mulher Brasileira | Conforme o esperado |
| 13 | opção `3`, ID `99` | `Nenhum servico encontrado com o ID 99.` | Conforme o esperado |
| 14 | opção `3`, ID `abc` | `ID invalido.` | Conforme o esperado |
| 15 | opção `4`, `1`, categoria `1` | serviços 2 e 4 e `Total encontrado: 2` | Conforme o esperado |
| 16 | opção `4`, `1`, categoria `4` | `Nenhum servico encontrado na categoria Saude.` | Conforme o esperado |
| 17 | opção `4`, `1`, categoria `9` | `Opcao invalida.` e o menu de categorias reaparece | Conforme o esperado |
| 18 | opção `4`, `2`, estado `sp` | serviços 2 e 4 e `Total encontrado: 2` (aceita minúscula) | Conforme o esperado |
| 19 | opção `4`, `2`, estado `RJ` | `Nenhum servico encontrado no estado RJ.` | Conforme o esperado |
| 20 | opção `4`, `2`, estado `SAO` | `Estado invalido. Digite 2 letras.` e pede de novo | Conforme o esperado |
| 21 | opção `4`, depois `9` | `Opcao invalida.` | Conforme o esperado |

### 11.4 Ordenação e análise

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 22 | opção `7` | `Lista ordenada por nome (A-Z):` com os IDs 5, 3, 6, 2, 4, 1 (`defensoria publica`, em minúsculo, fica entre Casa e Delegacia) | Conforme o esperado |
| 23 | opção `2`, logo depois | IDs 1, 2, 3, 4, 5, 6 (a lista volta à ordem de ID) | Conforme o esperado |
| 24 | opção `8` | `Total de servicos: 6`; Delegacia e seguranca: 2; Acolhimento e abrigo: 2; Apoio juridico: 1; Saude: 0; Apoio psicologico: 0; Canal de denuncia: 1 | Conforme o esperado |

### 11.5 Cadastro

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 25 | opção `1`, ID `7`, nome `Centro de Saude da Mulher`, categoria `4`, descrição `Atendimento de saude`, requisitos `Documento com foto`, cidade `Fortaleza`, estado `ce`, telefone `(85) 0000-0000`, horário `8h as 17h` | `Servico cadastrado com sucesso.` | Conforme o esperado |
| 26 | opção `2` | serviço 7 por último, com `Fortaleza-CE` (UF em maiúscula) | Conforme o esperado |
| 27 | opção `1`, ID `7` | `Ja existe um servico com o ID 7.`, sem pedir mais dados | Conforme o esperado |
| 28 | opção `1`, ID `abc`, `0` ou `-5` | `ID invalido.` | Conforme o esperado |
| 29 | opção `1`, ID `8`, nome vazio (só Enter) | `Campo obrigatorio. Tente novamente.` | Conforme o esperado |
| 30 | opção `1`, ID `8`, nome `Teste`, categoria `9` | `Opcao invalida.` e o menu de categorias reaparece | Conforme o esperado |
| 31 | opção `1`, ID `8`, nome `Teste`, categoria `1`, descrição, requisitos e cidade quaisquer, estado `1a` e depois `SP`, telefone e horário quaisquer | `Estado invalido. Digite 2 letras.`; ao informar `SP` o cadastro segue e termina com `Servico cadastrado com sucesso.` | Conforme o esperado |

### 11.6 Atualização

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 32 | opção `5`, ID `4`, campo `7`, `(19) 1111-1111` | `Servico atualizado com sucesso.`; opção `3` com ID `4` mostra o telefone novo | Conforme o esperado |
| 33 | opção `5`, ID `7`, campo `1`, `Centro de Saude` | `Servico atualizado com sucesso.`; o nome muda | Conforme o esperado |
| 34 | opção `5`, ID `7`, campo `6`, `xyz` e depois `Ce` | `Estado invalido. Digite 2 letras.` e depois atualiza para `CE` | Conforme o esperado |
| 35 | opção `5`, ID `99` | `Nenhum servico encontrado com o ID 99.` | Conforme o esperado |
| 36 | opção `5`, ID `abc` | `ID invalido.` | Conforme o esperado |
| 37 | opção `5`, ID `1`, campo `0` | `Atualizacao cancelada.` | Conforme o esperado |
| 38 | opção `5`, ID `1`, campo `9` | `Opcao invalida.` | Conforme o esperado |

### 11.7 Exclusão

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 39 | opção `6`, ID `99` | `Nenhum servico encontrado com o ID 99.` | Conforme o esperado |
| 40 | opção `6`, ID `abc` | `ID invalido.` | Conforme o esperado |
| 41 | opção `6`, ID `3` (nó do meio) | `Servico removido com sucesso.`; `2` lista sem o 3 | Conforme o esperado |
| 42 | opção `6`, ID `1` (primeiro nó) | removido; `2` começa no 2 | Conforme o esperado |
| 43 | opção `6`, ID `8` (último nó) | removido; `2` termina no 7 | Conforme o esperado |
| 44 | opção `3`, ID `3` | `Nenhum servico encontrado com o ID 3.` | Conforme o esperado |

### 11.8 Persistência e lista vazia ao final

| Nº | Entrada | Esperado | Observado |
|---|---|---|---|
| 45 | opção `0`, executar de novo e opção `2` | serviços 2, 4, 5, 6 e 7, com o telefone novo do 4 e o nome atualizado do 7 | Conforme o esperado |
| 46 | abrir o `servicos.txt` | 9 linhas por serviço, em ordem de ID (linhas 1, 10, 19, 28 e 37 com `2`, `4`, `5`, `6` e `7`) | Conforme o esperado |
| 47 | opção `6` para os IDs 2, 4, 5, 6 e 7 e depois opção `2` | `Lista vazia.` | Conforme o esperado |
| 48 | opção `0`, apagar o `servicos.txt` e executar | inicia sem erro e `2` mostra `Lista vazia.` | Conforme o esperado |

## 12. Demonstração em vídeo

[Assistir à demonstração](https://youtu.be/tZJxAmTLvlY)
