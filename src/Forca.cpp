#include "Foca.hpp"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::fstream;

Forca::Forca(std::string palavras, std::string scores) {
    m_arquivo_palavras = palavras;  
    m_arquivo_scores = scores;
    std::pair<bool, std::string> teste = eh_valido();
    cout<< ">>> Lendo arquivo de palavras [" << m_arquivo_palavras << "] "<<
    "e scores [" << m_arquivo_scores << "]\nPor favor, aguarde..." << endl;
    cout<< "--------------------------------------------------" <<endl;
    cout<<">>> "<<teste.second<<endl;
    cout<< "--------------------------------------------------" <<endl;
    if (!teste.first) {
        exit(1);
    }
}

std::pair<bool, std::string> Forca::eh_valido() {
    fstream arquivo_scores(m_arquivo_scores);
    fstream arquivo_palavras(m_arquivo_palavras);
    if (arquivo_palavras.bad() || !arquivo_palavras || arquivo_palavras.is_open() == 0) {
        return {false, "Não foi possível abrir o arquivo " + m_arquivo_palavras};
    } else if (arquivo_scores.bad() || !arquivo_scores || arquivo_scores.is_open() == 0) {
        return {false, "Não foi possível abrir o arquivo " + m_arquivo_scores};
    }
    return {true, "Arquivos OK!"};
}

void Forca::carrega_arquivos() {
    fstream arquivo_palavras(m_arquivo_palavras);
    fstream arquivo_scores(m_arquivo_scores);

    std::pair<std::string, int> valor_temp;
    std::string palavra;
    int frequencia;
    while (arquivo_palavras >> palavra >> frequencia) {
        valor_temp.first = palavra;
        valor_temp.second = frequencia;
        m_palavras.push_back(valor_temp);
    }
}

void Forca::set_dificuldade(Dificuldade d) {
    dificuldade = d;
}

std::string Forca::proxima_palavra() {
    letras_informadas.clear();
    palavra_tempo_real.clear();
    std::vector<std::string> palavras;
    //Nível fácil
    if (dificuldade == 0) {
        for (int i = 0; i < m_palavras.size(); i++) {
            // Verifica se a palavra é maior ou igual a frequência
            if (m_palavras[i].second >= media_frequencia) {
                palavras.push_back(m_palavras[i].first);
            }
        }
    } 
    //Nível médio
    else if (dificuldade == 1) {
        for (int i = 0; i < m_palavras.size(); i++) {
            /**
             * Como a cada 3 palavras sorteadas, 1 tem que ser menor que a frequência média
             * neste if está verificando se foi sorteado até 2 palavras e caso sim adiciona no array
             * de palavras apenas as palavras com frequência maior ou igual a frequência média
            **/
            if (qtd_palavras_jogadas < 3) {
                if(m_palavras[i].second >= media_frequencia) {
                    palavras.push_back(m_palavras[i].first);
                } 
            } 
            /**
             * caso não, significa que já foi sorteado 2 palavras e a 3 tem que ser menor que a frequencia média
             * verifica se a palavra é menor ou igual a frequencia média e adicona ao array em caso positivo
            **/
            else if (m_palavras[i].second < media_frequencia) {
                palavras.push_back(m_palavras[i].first);
            }
        }
    } 
    //Nível dificil
    else {
        for (int i = 0; i < m_palavras.size(); i++) {
            if (m_palavras[i].second < media_frequencia) {
                palavras.push_back(m_palavras[i].first);
            }
        }
    }
    qtd_palavras_jogadas = qtd_palavras_jogadas == 3 ? 1 : qtd_palavras_jogadas + 1;
    //Remove do array de palavras as palavras que já foram jogadas, ou seja, cada palavra só é sorteada, no máximo, 1 vez
    for (int i = 0; i < palavras.size(); i++) {
        for (int j = 0; j < palavras_certas.size(); j++) {
            if (palavras[i] == palavras_certas[j]) {
                palavras.erase(palavras.begin() + i);
                i--;
                break;
            }
        }
    }
    srand((unsigned)time(0));
    int index = 0;
    if (palavras.size()) {
        index = rand() % (palavras.size());
    }
    //Caso existam palavras no array, retorna a palavra sorteada. Caso contrário retorna "0" que será usado como condição de parada
    return palavras.size() ? palavras[index] : "0";
}

void Forca::set_media_frequencia() {
    int sum = 0;
    int i;
    for (i = 0; i < m_palavras.size(); i++) {
        sum += m_palavras[i].second;
    }
    media_frequencia = (float) sum / i;
}

std::string Forca::get_palavra_atual() {
    return m_palavra_atual;
}

std::vector<int> Forca::get_indices_acerto(char letra) {
    std::vector<int> indices;
    for (int i = 0; i < m_palavra_atual.length(); i++) {
        if (letra == m_palavra_atual[i]) {
            indices.push_back(i);
        }  
    }
    return indices;
}

void Forca::set_letras_acerto(std::vector<int> index, std::string let) {
    for (int i = 0; i < index.size(); i++) {
        palavra_tempo_real[index[i]] = let;
    }
}

bool Forca::palpite(std::string palpite) {
    if (m_palavra_atual.find(palpite) != std::string::npos) {
        return true;
    }
    return false;
}

bool Forca::verificar_se_letra_ja_foi(std::string str) {
    for (int i = 0; i < letras_informadas.size(); i++) {
        if (str == letras_informadas[i]) {
            return true;
        }
    }
    letras_informadas.push_back(str);
    return false;
}

bool Forca::game_over() {
    if (m_tentativas_restantes == 0) {
        return true;
    }
    return false;
}

void Forca::set_tentativas_restantes(int tentativas) {
    m_tentativas_restantes = tentativas;
}

void Forca::set_palavra_atual() {
    m_palavra_atual = Forca::proxima_palavra();
    for (int i = 0; i < m_palavra_atual.length(); i++)
        palavra_tempo_real.push_back("_");
}
int Forca::get_tentativas_restantes() {
    return m_tentativas_restantes;
}

std::string Forca::get_dificuldade() {
    if (dificuldade == 0) {
        return "Fácil";
    } else if (dificuldade == 1) {
        return "Médio";
    }
    return "Difícil";
}

void Forca::get_palavra_tempo_real() {
    for (int i = 0; i < palavra_tempo_real.size(); i++)
        cout<<palavra_tempo_real[i]<< + " ";
    cout<<""<<endl;
}

void Forca::set_pontuacao(int p) {
    pontuacao = p;
}

int Forca::get_pontuacao() {
    return pontuacao;
}

std::vector<std::string> Forca::get_palavras_certas() {
    return palavras_certas;
}

void Forca::set_palavra_certa() {
    palavras_certas.push_back(m_palavra_atual);
}

void Forca::exibir_scores() {
    std::cout<< "----------------------------" <<endl;
    cout<< "SCORES" <<endl;
    std::ifstream arquivo_scores(m_arquivo_scores);
    std::string s;
    std::string delimiter = ";";
    size_t pos = 0;
    std::string token;
    //TODO: referência -> https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    while (getline(arquivo_scores, s)) {
        int count = 0;
        std::cout<< "----------------------------" <<endl;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (count == 0) cout<< "Dificildade: ";
            if (count == 1) cout<< "Jogador(a):";
            if (count == 2) cout<< "Palavras Acertadas:";
            cout<< token <<endl;
            s.erase(0, pos + delimiter.length());
            count++;
        }
        std::cout<< "Pontuação:" << s <<endl;
    }
    std::cout<< "----------------------------" <<endl;
}

void Forca::exibir_menu_inicial() {
    cout<< "Bem vindo(a) ao Jogo da Forca! Por favor, escolha uma das opções abaixo:" <<endl;
    cout<< "1 - Iniciar Jogo\n2 - Ver scores anteriores" <<endl;
    cout<< "Sua escolha: ";
}

void Forca::exibir_opcoes_dificuldade() {
    cout<< "1 - Fácil\n2 - Médio\n3 - Difícil" <<endl;
    cout<< "Sua escolha: ";
}

bool Forca::acertou_palavra() {
    for (int i = 0; i < palavra_tempo_real.size(); i++) {
        if (palavra_tempo_real[i] == "_")
            return false; 
    }
    return true;
}