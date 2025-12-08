#include <iostream>
#include <sstream>
#include <string>
#include "SistemaFicheiros.hpp"

using namespace std;

int main() {
    SistemaFicheiros fs;

    cout << "Sistema de Ficheiros (simulado)\n";
    cout << "Escreve 'help' para ver os comandos.\n";

    string linha;
    while (true) {
        cout << "fs> ";//por convenção todas as linhas que esperam o input do utilizador começam com "fs>""
        if (!std::getline(cin, linha)) break;//lê uma linha inteira de input de utilizador até este precionar "Enter"

        istringstream iss(linha);
        string cmd;
        iss >> cmd;//
        if (cmd.empty()) continue;

        if (cmd == "exit" || cmd == "quit") {
            break;
        } else if (cmd == "help") {
            cout <<
                "Comandos:\n"
                "  cd [path]         - mudar diretoria (cd, cd ~, cd /, cd -, cd ..)\n"
                "  mkdir <name>      - criar diretoria\n"
                "  touch <name> [s]  - criar ficheiro (opcional size)\n"
                "  rm <name>         - remover ficheiro\n"
                "  rmdir <name>      - remover diretoria\n"
                "  ls                - listar conteudo da diretoria atual\n"
                "  load              - carregar ficheiros/diretoria do disco (usa a função Load())\n"
                "  find <name>       - procurar subdiretoria na diretoria atual\n"
                "  help              - mostrar esta ajuda\n"
                "  exit/quit         - sair\n";
        } else if (cmd == "cd") {
            string caminho;
            if (!(iss >> caminho)) caminho = "";  // cd sem arg -> home
            fs.cd(caminho);
        } else if (cmd == "mkdir") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "mkdir: falta nome\n";
                continue;
            }
            fs.CriarDiretoria(nome);
        } else if (cmd == "touch") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "touch: falta nome\n";
                continue;
            }
            size_t tamanho = 0;
            if (iss >> tamanho) {
                // size provided
            }
            // assinatura no header: Diretorias* CriarFicheiro(const string&, size_t)
            fs.CriarFicheiro(nome, tamanho);
        } else if (cmd == "rm") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "rm: falta nome\n";
                continue;
            }
            // função espera string& -> usa variável
            string arg = nome;
            fs.RemoverFicheiro(arg);
        } else if (cmd == "rmdir") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "rmdir: falta nome\n";
                continue;
            }
            string arg = nome;
            fs.RemoverDiretoria(arg);
        } else if (cmd == "ls") {
            fs.ListarConteudo();
        } else if (cmd == "load") {
            // header tem Load() sem args
            if (!fs.Load()) {
                cerr << "Load falhou\n";
            }
        } else if (cmd == "find") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "find: falta nome\n";
                continue;
            }
            Diretorias* res = fs.ProcurarLocal(nome);
            if (res) cout << "Encontrado: " << nome << '\n';
            else cout << "Não encontrado: " << nome << '\n';
        } else {
            cerr << "Comando desconhecido: " << cmd << '\n';
        }
    }

    cout << "Programa terminado.\n";
    return 0;
}

//MELHORAR O MAIN DEPOIS DE FAZER TODAS AS FUNÇÕES
//TENTAR FAZER O SISTEMA FUNCIONAL E COMPILAR SEM ERROS
//TENTAR DESCOBRIR COMO COMPILAR TODOS OS FICHEIROS AO MESMO TEMPO
//TENTAR DESCOBRIR COMO RODAR TODOS OS FICHEIROS AO MESMO TEMPO
//FAZER UMA REVISÃO FINAL PARA VERIFICAR SE ENTENDO TUDO OQUE FIZ
//ADICIONAR COMENTÁRIOS A TODAS AS FUNÇÕES
//FAZ COMENÁRIOS COM O DOXIGEN PARA GERAR DOCUMENTAÇÃO AUTOMÁTICA