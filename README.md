# Projeto 2ºGQ: Comparação de Estruturas de Dados

Comparação de desempenho entre três estruturas de dados nas operações de **inserção** e **busca por matrícula**, usando uma base de até 10 milhões de registros de estudantes (matrícula, nome e curso). Implementado em **C**, com alocação dinâmica de memória e módulos organizados como **TAD** (Tipo Abstrato de Dados).

## Integrantes

- Jeanne Espíndola Pereira
- Breno de Araújo Bezerra
- Daniel Silva

## Estruturas implementadas

| Estrutura | Arquivos | Descrição |
|---|---|---|
| Lista unicamente encadeada | `lista.h` / `lista.c` | Estrutura linear. Inserção sempre no início (O(1)) e busca sequencial (O(n)). |
| Tabela hash com endereçamento aberto | `hash_aberto.h` / `hash_aberto.c` | Trata colisões por sondagem. **[CONFERIR: sondagem usada (linear, quadrática ou dupla)]** |
| Tabela hash com encadeamento separado | `hash_encadeado.h` / `hash_encadeado.c` | Cada posição da tabela guarda uma lista encadeada. Colisões são inseridas na lista da própria posição. |

## Funções hash

Definidas em `hash_funcoes.h` / `hash_funcoes.c`. Cada tabela recebe a função hash como parâmetro (ponteiro para função), então as duas funções são testadas nas duas tabelas:

- **`FuncaoHashDiv`**: método da divisão (resto da divisão da matrícula pelo tamanho da tabela).
- **`FuncHashDobra`**: método da dobra (divide a matrícula em partes, soma as partes e ajusta ao tamanho da tabela).

Isso gera as **quatro configurações de tabela hash** (2 tabelas × 2 funções), além da lista.

## Outros módulos

| Arquivo | Função |
|---|---|
| `registro.h` / `registro.c` | Define a struct `Registro` (matrícula, nome e curso) e a função `imprimir_registro`. |
| `leitura.h` / `leitura.c` | Lê a base uma única vez, na ordem do arquivo, e guarda os registros em um vetor. As estruturas guardam ponteiros para esse vetor. |
| `main.c` | Executa os experimentos e mede os tempos. |

## Experimentos

Para cada volume (**100 mil**, **1 milhão** e **10 milhões** de registros), as cinco implementações começam vazias e recebem os registros na mesma ordem do arquivo. São feitas medições após atingir **30%, 60% e 100%** do volume:

- **Inserção:** tempo dos intervalos 0–30%, 30–60% e 60–100%.
- **Busca:** 10.000 buscas por matrículas existentes, sorteadas entre os registros já inseridos. As mesmas matrículas e a mesma ordem são usadas nas cinco implementações.
- **Colisões:** em cada intervalo, quantas vezes uma nova matrícula produz um índice hash inicial que já foi produzido por outra matrícula (apenas nas tabelas hash).
- **Fator de carga:** α = n / m, calculado após cada etapa (apenas nas tabelas hash).

O tempo de leitura do arquivo e o tempo de sorteio das matrículas **não** entram nas medições.

### Tamanho das tabelas hash

O mesmo tamanho é usado nas quatro configurações, e fica fixo durante cada experimento:

| Volume | Tamanho da tabela |
|---|---|
| 100 mil | 100003 |
| 1 milhão | 1000003 |
| 10 milhões | 10000019 |

**Justificativa:** são números primos ligeiramente maiores que o volume de dados. O tamanho maior que a quantidade de registros garante que a tabela de endereçamento aberto comporte todos eles, e o tamanho primo reduz padrões de colisão no método da divisão.

## Como compilar

Pré-requisito: compilador **gcc**. Abra o terminal na pasta dos arquivos-fonte (`Projeto2GQ`) e rode:

```
gcc -O2 main.c registro.c leitura.c lista.c hash_encadeado.c hash_aberto.c hash_funcoes.c -o programa
```

## Como executar

Coloque o arquivo da base na mesma pasta do programa. **[CONFERIR: nome do arquivo da base e se o programa recebe o nome por argumento]**

```
.\programa.exe        (Windows / PowerShell)
./programa            (Linux / macOS)
```

## Resultados

Os resultados dos experimentos (tabelas de tempos de inserção e busca, colisões e fator de carga para os três volumes e os três níveis de preenchimento) estão na pasta `resultados/` e nos slides da apresentação. **[CONFERIR]**

## Observações

- Cada matrícula é única na base.
- A struct de cada TAD fica escondida no `.c`; os outros módulos só usam as funções declaradas no `.h`.
- As estruturas guardam **ponteiros** para os registros do vetor lido, e não cópias, para não duplicar milhões de registros na memória.
- A função `liberar_base` libera o vetor de registros, e as funções `destruir` liberam apenas as estruturas (nós, listas e tabelas).
