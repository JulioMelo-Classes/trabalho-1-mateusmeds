#include <iostream>
#include <vector>

class Partida {
    private:
        std::string dificuldade;
        std::string jogador;
        std::vector<std::string> palavras_certas;
        int pontuacao;

    public:
        Partida();
        void set_dificuldade(std::string d);
        void set_jogador(std::string j);
        void set_palavras_certas(std::vector<std::string> palavra);
        void set_pontuacao(int p);

        std::string get_dificuldade();
        std::string get_jogador();
        int get_pontuacao();
        std::vector<std::string> get_palavras_certas();

        void salvar(std::string arq);
};