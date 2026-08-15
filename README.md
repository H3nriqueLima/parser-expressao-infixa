# Parser de Expressões

Um parser de expressões aritméticas escrito em C puro, sem bibliotecas externas.

## O que faz?

Lê uma expressão matemática em texto (ex: `3 + 4 * (2 - 1)`) e calcula o resultado, respeitando precedência de operadores e parênteses, igual uma calculadora resolveria na mão.

## Por que existe?

Feito como exercício de retomada de estudos em C, com foco em entender na prática como um parser recursivo descendente funciona: tokenização de texto, construção de uma gramática em camadas (expressão → termo → potência → fator), e avaliação recursiva respeitando precedência sem precisar de tabela de prioridade explícita.

## Operações suportadas

- Soma, subtração, multiplicação, divisão, potência (`^`, associativo à direita).
- Números decimais (`3.5`) e negativo/positivo unário (`-5`, `-(3 + 4)`).
- `()`, `[]`, `{}` para agrupar sub-expressões (com validação de correspondência).
- Validação de sintaxe → caractere inválido, delimitador não fechado, divisão por zero e overflow numérico são rejeitados com mensagem de erro.

## Como rodar (ainda a desenvolver o arquivo main)

```bash
gcc -Wall -Wextra -std=c99 -I include src/main.c -o parser
./parser
```

Roda em loop no terminal, escolhe "Calcular", digita a expressão, vê o resultado, repete.

## Contexto

Parte de uma série de projetos em C focados em fundamentos de baixo/médio nível. O próximo passo natural desse é evoluir a mesma técnica de parsing recursivo pra um interpretador de linguagem simples.