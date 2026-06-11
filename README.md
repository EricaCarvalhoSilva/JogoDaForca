# Jogo da Forca em C

## Sobre o Projeto

Este projeto consiste em uma implementação do tradicional jogo da forca desenvolvida em linguagem C.

O jogo utiliza um banco de palavras armazenado em arquivo e possui um sistema de dificuldades, permitindo ao jogador escolher entre palavras fáceis, médias ou difíceis.

O projeto foi desenvolvido com o objetivo de praticar conceitos fundamentais da programação, como manipulação de arquivos, structs, ponteiros, alocação dinâmica de memória e menus interativos.

---

## ✨ Funcionalidades

- Menu principal navegável utilizando as setas do teclado
- Cadastro de novas palavras
- Armazenamento permanente das palavras em arquivo
- Sistema de temas e dicas
- Seleção de dificuldade
- Filtragem de palavras pela dificuldade escolhida
- Sorteio aleatório de palavras
- Controle de letras corretas e incorretas
- Sistema de vitória e derrota

---

## Como Jogar

1. Execute o programa.
2. Escolha a opção **Jogar**.
3. Selecione uma dificuldade:
   - Fácil
   - Médio
   - Difícil
4. Observe o tema e a dica exibidos.
5. Digite letras para tentar descobrir a palavra.
6. Vença descobrindo a palavra antes de esgotar as tentativas.

---

## Como Executar

### Pré-requisitos

- Sistema operacional Windows
- GCC (MinGW) ou compilador compatível
- Arquivo `banco.txt` na mesma pasta do executável

### Compilação e Execução

Abra o terminal na pasta do projeto e execute:

```bash
g++ jogo_da_forca.cpp -o forca.exe
```

Após a compilação:

```bash
.\forca.exe
```

---

## Estrutura do Projeto

```txt
JogoDaForca/
│
├── jogo_da_forca.cpp
├── banco.txt
└── README.md
```

### Arquivos

#### jogo_da_forca.cpp

Contém toda a lógica do jogo:

- Menu principal
- Seleção de dificuldade
- Cadastro de palavras
- Leitura do banco de palavras
- Sorteio das palavras
- Execução do jogo

#### banco.txt

Arquivo responsável por armazenar as palavras cadastradas.

Formato:

```txt
palavra|tema|dica|dificuldade
```

Exemplo:

```txt
cachorro|Animais|Melhor amigo do homem|facil
computador|Tecnologia|Usado para programar|medio
algoritmo|Tecnologia|Sequencia de passos|dificil
```

---

## Tecnologias Utilizadas

- Linguagem C
- GCC / MinGW
- Biblioteca padrão da linguagem
- windows.h
- conio.h

---

## Conceitos Aplicados

Durante o desenvolvimento foram utilizados:

- Structs
- Ponteiros
- Vetores
- Vetores de ponteiros
- Alocação dinâmica de memória
- Manipulação de arquivos
- Funções
- Menus interativos
- Geração de números aleatórios
- Filtragem de dados

---

## 👨‍💻 Autor

Erica Carvalho

Projeto desenvolvido para fins de estudo e prática da linguagem C.
