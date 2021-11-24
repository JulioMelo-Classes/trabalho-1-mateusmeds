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
    std::ofstream score_file;
    score_file.open(arq, std::ios::app);
    score_file << dificuldade + "; ";
    score_file << jogador + "; ";
    for (int i = 0; i < palavras_certas.size(); i++) {
        if (i < palavras_certas.size() - 1) {
            score_file << palavras_certas[i] + ",";
        } else {
            score_file << palavras_certas[i];
        }
    }
    score_file << "; ";
    score_file << pontuacao;
    score_file << "\n";
    score_file.close();
}