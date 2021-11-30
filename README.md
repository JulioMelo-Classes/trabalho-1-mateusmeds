# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1X3VDW6EBE_ZRDHCoRNwqva17R1EZMpwDunRgDg9N4HU/edit?usp=sharing). Preencha o [author.md](author.md) com as informações relativas ao grupo/autor.

1. cd src
2. g++ -c main.cpp Forca.cpp Partida.cpp
3. g++ -o prog main.o Forca.o Partida.o
4. ./prog palavras.txt scores.txt

# Avaliação

## Código | Funcionalidades
1. Classe forca 10/10

2. Interface textual 10/10

3. Execução completa do jogo 13/15
- Ficou faltando sortear as letras que já iniciam pro usuário nos níveis fácil e médio

4. Validação dos arquivos de texto 1/5
- Vc validou se os arquivos existem vou considerar um pouco

5. Arquivos de teste de validação dos casos de erro 0/5
- A ideia aqui era que voce enviasse arquivos que mostrassem as validações implementadas

6. Arquivos de teste de validação dos níveis de dificuldade 1/5
- A ideia aqui era vc incluir arquivos de palavras que pudessem ser usados para validar os níveis de dificuldade
especialmente quando ocorre game over devido o usuário ter acertado todas as palavras. Vou considerar o arquivo já inserido
como um possível caso de teste mas o melhor era que ficasse mais organizado.

7. Observações gerais
- Essa classe "Partida" parece mais uma classe "Score" =).


## Código | Boas práticas

1. Documentação do código e readme 5/10
- Partida.hpp não está documentado

2. Organização e indentação 5/10
- Voces não usaram a organização sugerida no trabalho, ou qualquer outra organização de diretórios.

3. Compilação automatizada 0/5

