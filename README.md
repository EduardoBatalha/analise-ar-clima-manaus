# 🌎 Análise da Qualidade do Ar e do Clima de Manaus

Projeto acadêmico desenvolvido em linguagem C para a disciplina de **Algoritmos e Estruturas de Dados**, da Universidade Federal do Amazonas (UFAM).

O projeto utiliza algoritmos de estatística de ordem para analisar dados ambientais de Manaus e comparar a eficiência de diferentes abordagens computacionais.

## 🎯 Objetivo

Implementar e comparar três algoritmos para encontrar estatísticas de ordem em conjuntos de dados ambientais, avaliando seus custos computacionais por meio da contagem de comparações.

## 🛠️ Tecnologias utilizadas

- Linguagem C
- GCC
- Arquivos CSV
- Algoritmos de ordenação e seleção

## 📊 Dados analisados

O programa utiliza três conjuntos de dados contendo:

- 1.000 registros
- 5.000 registros
- 10.000 registros

Os arquivos apresentam informações sobre temperatura, umidade relativa do ar e concentração de partículas PM2.5.

## 🧠 Algoritmos implementados

### Abordagem A — Bubble Sort

Realiza a ordenação completa dos elementos para identificar as estatísticas de ordem desejadas.

### Abordagem B — Particionamento

Utiliza uma estratégia de seleção baseada em particionamento, permitindo encontrar o elemento desejado sem ordenar completamente o vetor.

### Abordagem C — Contagem comparativa

Identifica a posição de um elemento por meio da contagem de valores menores e iguais, sem modificar a ordem original do vetor.

## 📈 Funcionalidades

O programa permite:

- Calcular a mediana dos valores de PM2.5.
- Determinar o percentil 90 de PM2.5.
- Identificar os dez menores valores de umidade.
- Comparar o número de comparações realizadas pelos algoritmos.
- Analisar o comportamento dos algoritmos com diferentes quantidades de registros.

## 💻 Como executar

É necessário possuir o compilador GCC instalado.

Clone o repositório:

```bash
git clone https://github.com/EduardoBatalha/analise-ambiental-manaus.git
```

Acesse a pasta:

```bash
cd analise-ambiental-manaus
```

Compile o programa:

```bash
gcc trabalho_clima.c -o trabalho_clima
```

Execute:

```bash
./trabalho_clima
```

O programa apresentará um menu para selecionar o conjunto de dados e o algoritmo desejado.

## 📄 Relatório técnico

O repositório também contém um relatório técnico com a descrição das implementações, resultados experimentais e análise de complexidade dos algoritmos.

## 🎓 Contexto acadêmico

**Instituição:** Universidade Federal do Amazonas (UFAM)

**Disciplina:** Algoritmos e Estruturas de Dados

**Período:** 2026/2

**Desenvolvedores:**
- Eduardo Guimarães da Silva Batalha
- Fernando Naum Santos Batista