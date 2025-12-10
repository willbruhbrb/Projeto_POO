#include <iostream>
#include <sstream>
#include <string>
#include "SistemaFicheiros.hpp"

using namespace std;

int main() {
    SistemaFicheiros fs;

    cout << "=== Sistema de Ficheiros Simulado ===" << endl;
    cout << "Escreve 'help' para ver os comandos disponíveis.\n" << endl;

    string linha;
    while (true) {
        cout << "fs> ";
        if (!getline(cin, linha)) break;

        istringstream iss(linha);
        string cmd;
        iss >> cmd;
        if (cmd.empty()) continue;

        if (cmd == "exit" || cmd == "quit") {
            cout << "A sair do programa..." << endl;
            break;
            
        } else if (cmd == "help") {
            cout << "\n=== Comandos Disponíveis ===" << endl;
            cout << "Navegação:" << endl;
            cout << "  cd [path]              - Mudar diretoria (cd, cd ~, cd /, cd -)" << endl;
            cout << "\nGestão de Ficheiros/Diretorias:" << endl;
            cout << "  mkdir <nome>           - Criar diretoria" << endl;
            cout << "  touch <nome> [tamanho] - Criar ficheiro (tamanho opcional em bytes)" << endl;
            cout << "  rm <nome>              - Remover ficheiro" << endl;
            cout << "  rmdir <nome>           - Remover diretoria" << endl;
            cout << "  mv <nome> <destino>    - Mover ficheiro (usar com search para obter destino)" << endl;
            cout << "  rename <antigo> <novo> - Renomear ficheiro" << endl;
            cout << "\nListagem e Pesquisa:" << endl;
            cout << "  ls                     - Listar conteúdo da diretoria atual" << endl;
            cout << "  tree                   - Mostrar estrutura em árvore" << endl;
            cout << "  search <nome>          - Procurar ficheiro/diretoria recursivamente" << endl;
            cout << "  searchall <nome>       - Procurar todos os ficheiros com esse nome" << endl;
            cout << "  searchdir <nome>       - Procurar todas as diretorias com esse nome" << endl;
            cout << "  duplicates             - Encontrar ficheiros duplicados" << endl;
            cout << "\nEstatísticas:" << endl;
            cout << "  count                  - Contar ficheiros no sistema" << endl;
            cout << "  countdir               - Contar diretorias no sistema" << endl;
            cout << "  memory                 - Calcular memória total ocupada" << endl;
            cout << "  largest                - Encontrar maior ficheiro" << endl;
            cout << "  mostfiles              - Diretoria com mais elementos" << endl;
            cout << "  leastfiles             - Diretoria com menos elementos" << endl;
            cout << "\nPersistência:" << endl;
            cout << "  save                   - Guardar sistema em XML" << endl;
            cout << "  load                   - Carregar sistema de XML" << endl;
            cout << "\nOutros:" << endl;
            cout << "  clear                  - Limpar todo o sistema (DIR para confirmar)" << endl;
            cout << "  help                   - Mostrar esta ajuda" << endl;
            cout << "  exit/quit              - Sair do programa" << endl;
            cout << endl;
            
        } else if (cmd == "cd") {
            string caminho;
            if (!(iss >> caminho)) caminho = "";
            fs.cd(caminho);
            
        } else if (cmd == "mkdir") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: mkdir requer um nome" << endl;
                continue;
            }
            fs.CriarDiretoria(nome);
            
        } else if (cmd == "touch") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: touch requer um nome" << endl;
                continue;
            }
            size_t tamanho = 0;
            iss >> tamanho;
            fs.CriarFicheiro(nome, tamanho);
            
        } else if (cmd == "rm") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: rm requer um nome" << endl;
                continue;
            }
            fs.RemoverFicheiro(nome);
            
        } else if (cmd == "rmdir") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: rmdir requer um nome" << endl;
                continue;
            }
            fs.RemoverDiretoria(nome);
            
        } else if (cmd == "rename") {
            string antigo, novo;
            if (!(iss >> antigo >> novo)) {
                cerr << "Erro: rename requer nome antigo e novo" << endl;
                continue;
            }
            fs.RenomearFicheiros(antigo, novo);
            
        } else if (cmd == "ls") {
            fs.ListarConteudo();
            
        } else if (cmd == "tree") {
            fs.Tree();
            
        } else if (cmd == "search") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: search requer um nome" << endl;
                continue;
            }
            fs.Search(nome);
            
        } else if (cmd == "searchall") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: searchall requer um nome" << endl;
                continue;
            }
            fs.PesquisarAllFicheiros(nome);
            
        } else if (cmd == "searchdir") {
            string nome;
            if (!(iss >> nome)) {
                cerr << "Erro: searchdir requer um nome" << endl;
                continue;
            }
            fs.PesquisarAllDiretorias(nome);
            
        } else if (cmd == "duplicates") {
            fs.FicheirosDuplicados();
            
        } else if (cmd == "count") {
            int total = fs.ContarFicheiros();
            cout << "Total de ficheiros: " << total << endl;
            
        } else if (cmd == "countdir") {
            int total = fs.ContarDiretorias();
            cout << "Total de diretorias: " << total << endl;
            
        } else if (cmd == "memory") {
            size_t total = fs.Memoria();
            cout << "Memória total ocupada: " << total << " bytes";
            if (total > 1024) cout << " (" << (total / 1024) << " KB)";
            if (total > 1048576) cout << " (" << (total / 1048576) << " MB)";
            cout << endl;
            
        } else if (cmd == "largest") {
            Ficheiros* maior = fs.FicheiroMaior();
            if (maior) {
                cout << "Maior ficheiro: " << maior->getNomeFicheiro() 
                     << " (" << maior->getTamanhoFicheiro() << " bytes)" << endl;
            } else {
                cout << "Nenhum ficheiro encontrado." << endl;
            }
            
        } else if (cmd == "mostfiles") {
            Diretorias* dir = fs.DiretoriaMaisElementos();
            if (dir) {
                cout << "Diretoria com mais elementos: " << dir->getNomeDiretoria() << endl;
            } else {
                cout << "Nenhuma diretoria encontrada." << endl;
            }
            
        } else if (cmd == "leastfiles") {
            Diretorias* dir = fs.DiretoriaMenosElementos();
            if (dir) {
                cout << "Diretoria com menos elementos: " << dir->getNomeDiretoria() << endl;
            } else {
                cout << "Nenhuma diretoria encontrada." << endl;
            }
            
        } else if (cmd == "save") {
            fs.Escrever_XML();
            
        } else if (cmd == "load") {
            if (!fs.Ler_XML()) {
                cerr << "Erro ao carregar ficheiro XML." << endl;
            }
            
        } else if (cmd == "clear") {
            string confirmacao;
            cout << "Tem a certeza que quer limpar todo o sistema? (escreva DIR para confirmar): ";
            getline(cin, confirmacao);
            if (fs.RemoveAll(confirmacao)) {
                cout << "Sistema limpo com sucesso!" << endl;
            }
            
        } else {
            cerr << "Comando desconhecido: '" << cmd << "'. Escreva 'help' para ajuda." << endl;
        }
    }

    cout << "\nPrograma terminado. Até à próxima!" << endl;
    return 0;
}