#include "Partida.hpp"
#include <iostream>
#include <vector>
#include <fstream>

Partida::Partida() {
    
}
void Partida::set_dificuldade(std::string d) {
    dificuldade = d;
}
void Partida::set_jogador(std::string j) {
    jogador = j;
}
void Partida::set_palavras_certas(std::vector<std::string> palavra) {
    palavras_certas = palavra;
}
void Partida::set_pontuacao(int p) {
    pontuacao = p;
}
std::string Partida::get_dificuldade() {
    return dificuldade;
}
std::string Partida::get_jogador() {
    return jogador;
}

void Partida::salvar(std::string arq) {
    std::ofstream Hypnos_FILE;
    Hypnos_FILE.open(arq, std::ios::app);
    Hypnos_FILE << dificuldade + "; ";
    Hypnos_FILE << jogador + "; ";
    for (int i = 0; i < palavras_certas.size(); i++) {
        if (i < palavras_certas.size() - 1) {
            Hypnos_FILE << palavras_certas[i] + ",";
        } else {
            Hypnos_FILE << palavras_certas[i];
        }
    }
    Hypnos_FILE << "; ";
    Hypnos_FILE << pontuacao;
    Hypnos_FILE << "\n";
    Hypnos_FILE.close();
}

//na hora de salvar a partida no arquivo, para separar as palavras por vírgula
/*
for () {
    if (i < palavra.size() - 1)
        palavra + ","
    else 
        palavra 
}
*/