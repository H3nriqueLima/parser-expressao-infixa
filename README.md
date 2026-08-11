# Parser de Expressões

Um parser de expressões aritméticas escrito em C puro, sem bibliotecas externas.

## O que faz?

Lê uma expressão matemática em texto (ex: `3 + 4 * (2 - 1)`) e calcula o resultado, respeitando precedência de operadores e parênteses, igual uma calculadora resolveria na mão.

## Por que existe?

Esse projeto será (ainda em desenvolvimento) feito como exercício de retomada de estudos em C, com foco em entender na prática como um parser recursivo descendente funciona: tokenização de texto, construção de uma gramática em camadas (expressão → termo → fator), e avaliação recursiva respeitando precedência sem precisar de tabela de prioridade explícita.

## Operações suportadas

- Soma, subtração, multiplicação, divisão.
- Parênteses para agrupar sub-expressões.
- Validação básica de sintaxe (expressão malformada é rejeitada).

## Como rodar (ainda a desenvolver o arquivo main)

```bash
gcc main.c -o parser
./parser
```

Digite uma expressão e pressione enter.

## Contexto

Parte de uma série de projetos em C focados em fundamentos de baixo/médio nível. O próximo passo natural desse é evoluir a mesma técnica de parsing recursivo pra um interpretador de linguagem simples.