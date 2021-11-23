#include <iostream>
#include <fstream>
#include <string>

#include "Foca.hpp"
#include "Partida.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::fstream;

int main (int argc, char *argv[]) {
    //TODO: arquivo de palavras -> argv[1] | arquivo de scores -> argv[2]
    Forca forca = Forca(argv[1], argv[2]);

    int opcaoInicio;
    int etapa = 1;

    while (!forca.game_over()) {
        while (etapa == 1) {
            forca.exibir_menu_inicial();
            cin>>opcaoInicio;
            switch (opcaoInicio) {
                case 1: 
                    etapa = 2; 
                    forca.carrega_arquivos();
                    break;
                case 2: forca.exibir_scores(); break;
            default: break;
            }
        }
        //Escolher nível de dificuldade
        if (etapa == 2) {
            forca.exibir_opcoes_dificuldade();
            int opcaoDificuldade;
            cin>>opcaoDificuldade;
            Forca::Dificuldade d = Forca::Dificuldade::FACIL;
            switch (opcaoDificuldade) {
                case 2: d = Forca::Dificuldade::MEDIO; break;
                case 3: d = Forca::Dificuldade::DIFICIL; break;
                default: break;
            }
            forca.set_dificuldade(d);
            etapa = 3;
        }
        if (etapa == 3) {
            cout<< "Iniciando o Jogo da Forca no nível " + forca.get_dificuldade() <<endl;
            forca.set_media_frequencia();
            forca.set_palavra_atual();
            forca.set_tentativas_restantes(6);
            etapa = 4;
        }
        while (forca.get_tentativas_restantes() > 0 && etapa == 4) {
            forca.get_palavra_tempo_real();
            cout<< "Pontos: " << forca.get_pontuacao() <<endl;
            cout<< "Palpite: ";
            std::string letra;
            cin>>letra;
            if (!forca.verificar_se_letra_ja_foi(letra)) {
                if (forca.palpite(letra)) {
                    forca.set_pontuacao(forca.get_pontuacao() + 1);
                    cout << "Muito bem! A palavra contém a letra " << letra << "!" <<endl;
                    //convertendo string para char
                    std::vector<char> cstr(letra.c_str(), letra.c_str() + letra.size() + 1);
                    std::vector<int> indices = forca.get_indices_acerto(cstr[0]);
                    forca.set_letras_acerto(indices, letra);
                } else {
                    cout<< "Errou! A palavra não contém a letra " << letra << "!" <<endl;
                    switch (forca.get_tentativas_restantes()) {
                    case 6: cout<< " O \n" <<endl; break;
                    case 5: cout<< " O \n | \n" <<endl; break;
                    case 4: cout<< " O \n/|\n" <<endl; break;
                    case 3: cout<< " O \n/|\\\n" <<endl; break;
                    case 2: cout<< " O \n/|\\\n/\n" <<endl; break;
                    case 1: cout<< " O \n/|\\\n/ \\\n" <<endl; break;
                    default:
                        break;
                    } 
                    forca.set_pontuacao(forca.get_pontuacao() - 1);
                    forca.set_tentativas_restantes(forca.get_tentativas_restantes() - 1);
                }
            }

            if (forca.acertou_palavra()) {
                forca.get_palavra_tempo_real();
                cout<< "Pontos: " << forca.get_pontuacao() <<endl;
                forca.set_pontuacao(forca.get_pontuacao() + 2);
                if (forca.get_tentativas_restantes() == 6) {
                    forca.set_pontuacao(forca.get_pontuacao() + 1);
                }
                forca.set_palavra_certa();
                cout<< "Parabéns! Você acertou a palavra!"<<endl;
                cout<< "Escolha uma das opções abaixo: "<<endl;
                cout<< "1 - Continuar\n2 - Encerrar"<<endl;
                int opc;
                cin>>opc;
                if (opc == 1) {
                    etapa = 3;
                } else {
                    etapa = 5;
                }
            }

            if (forca.game_over()) {
                cout<< "Game Over!" <<endl;
                cout<< "A palavra era " << forca.get_palavra_atual() << "!" <<endl;
            }
        }
        if (etapa == 5) {
            break;
        }
    }

    //TODO: salvando os dados da partida
    cout<< "Por favor, informe seu nome: ";
    std::string nome;
    
    //TODO: por algum motivo não estava lendo o nome do jogador, tive que acresentar esta linha
    std::string lixo;
    getline(cin, lixo);

    getline(cin, nome);
    cout<< nome <<endl;
    Partida partida = Partida();
    
    partida.set_dificuldade(forca.get_dificuldade());
    partida.set_jogador(nome);
    partida.set_palavras_certas(forca.get_palavras_certas());
    partida.set_pontuacao(forca.get_pontuacao());

    partida.salvar(argv[2]);

    return 0;
}