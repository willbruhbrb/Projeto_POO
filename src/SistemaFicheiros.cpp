#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "SistemaFicheiros.hpp"
#include "Diretorias.hpp"
#include "Datas.hpp"
#include "Ficheiros.hpp"
using namespace std;

//contrutor
SistemaFicheiros::SistemaFicheiros()
:raiz(make_unique<Diretorias>("root")),
diretoriaAtual(raiz.get()),
diretoriaAnterior(nullptr){
}

//Sistema de navegação (cd/cd~/cd-/...)
void SistemaFicheiros::cd(const string& caminho){
    if(caminho == "~" || caminho.empty() || caminho == "/"){
        //"cd" ou "cd~" -> vai para a raiz
        diretoriaAnterior = diretoriaAtual;//diretoriaAnterior=diretoriaAtual=
        diretoriaAtual = raiz.get();
        return;
    }
    if(caminho == "-"){
        //"cd-" -> retorna à diretoria do comando anterior
        if(diretoriaAnterior != nullptr){//verificar se a diretoria existe
        Diretorias* temp = diretoriaAtual;//diretoriaAtual=home, diretoriaAnterior=raiz, temp=home
        diretoriaAtual = diretoriaAnterior;//diretoriaAtual=diretoriaAnterior=root, temp =home
        diretoriaAnterior = temp;//diretoriaAtual= root, diretoriaAnterior= home, temp=home
        }
        return;
    }
}

//Gestão das Diretorias
Diretorias* SistemaFicheiros::CriarDiretoria(const string& nomeDiretoria){
    //"mkdir" -> cria uma diretoria no local atual
    //validação
    if(!diretoriaAtual){//verifica se já está numa diretoria
        cout<<"Erro!: Nenhuma diretoria encontrada!"<<endl;
        return nullptr;
    }
    if(nomeDiretoria.empty()){//verifica se a diretoria tem nome
        cout<<"Erro!: A diretoria não tem nome!"<<endl;
        return nullptr;
    }
    if(diretoriaAtual->encontrarSubDiretoria(nomeDiretoria) !=nullptr){
        cout<<"Erro!: Diretoria '"<<nomeDiretoria<<"' já existe."<<endl;
        return nullptr;
    }
    //criar Diretoria
    auto novaDiretoria = make_unique<Diretorias>(nomeDiretoria);
    Diretorias* ptr = novaDiretoria.get();
    //push_back
    diretoriaAtual->addSubDiretoria(move(novaDiretoria));
    return ptr;
}
bool SistemaFicheiros::RemoverDiretoria(string& nomeDiretoria){
    //remover subdiretoria da diretoria atual
    //verificações
    if(!diretoriaAtual){
        cout<<"Erro! Não está numa diretoria."<<endl;
        return false;
    }
    if(nomeDiretoria.empty()){
        cout<<"Erro! Ficheiro vazio."<<endl;
        return false;
    }

    //Recebe a lista de ficheirosna diretoria atual
    auto& subDiretorias = diretoriaAtual -> getSubDiretorias();

    //procurar o ficheiro pelo nome
    auto it = find_if(subDiretorias.begin(), subDiretorias.end(),
        [&](const unique_ptr<Diretorias>& d) {
            return d->getNomeDiretoria() == nomeDiretoria;
    });
    if(it != subDiretorias.end()){
        subDiretorias.erase(it);
        cout<<"Ficheiro "<< nomeDiretoria <<" removido com sucesso!"<<endl;
        return true;
    }else{
        cout<<"Erro!Ficheiro Não encontrado."<<endl;
        return false;
    }
}

//Gestão de Ficheiros
Diretorias* SistemaFicheiros::CriarFicheiro(const string& nomeFicheiro, size_t tamanho){
    //criar um ficheiro novo
    //validação
    if(!diretoriaAtual){//verifica se já está numa diretoria
        cout<<"Erro!: Nenhuma diretoria selecionada!"<<endl;
        return nullptr;
    }
    if(nomeFicheiro.empty()){//verifica se foi dado nome de Ficheiro
        cout<<"Erro!: O ficheiro não tem nome!"<<endl;
        return nullptr;
    }
    //criar Ficheiro
    auto novoFicheiro = make_unique<Ficheiros>(nomeFicheiro, tamanho);//criamos um novo objeto para o ficheiro
    Ficheiros* ptr = novoFicheiro.get();//criamos um ponteiro para esse vetor já que declaramos "Ficheiros" como ponteiro no ficheiro "Diretorias.hpp"
    //agora que temos o ponteiro definido podemos mover esse ponteiro para "Ficheiros" e dar push_back para a "diretoriaAtual"
    diretoriaAtual->addFicheiro(move(novoFicheiro));

    cout << "Ficheiro '" << nomeFicheiro << "' criado com sucesso! ("<< tamanho << " bytes)" << endl;

    return diretoriaAtual;
}
bool SistemaFicheiros::RemoverFicheiro(string& nomeFicheiro){
    //remover ficheiro da diretoria atual
    //verificações
    if(!diretoriaAtual){
        cout<<"Erro! Não está numa diretoria."<<endl;
        return false;
    }
    if(nomeFicheiro.empty()){
        cout<<"Erro! Ficheiro vazio."<<endl;
        return false;
    }

    //Recebe a lista de ficheirosna diretoria atual
    auto& ficheiros = diretoriaAtual -> getFicheiros();

    //procurar o ficheiro pelo nome
    auto it = find_if(ficheiros.begin(), ficheiros.end(),
        [&nomeFicheiro](const unique_ptr<Ficheiros>& ficheiro) {
            return ficheiro->getNomeFicheiro() == nomeFicheiro;
    });
    if(it != ficheiros.end()){
        ficheiros.erase(it);
        cout<<"Ficheiro "<< nomeFicheiro <<" removido com sucesso!"<<endl;
        return true;
    }else{
        cout<<"Erro!Ficheiro Não encontrado."<<endl;
        return false;
    }
}

//Sistema de navegação por nome de ficheiro/diretoria
Diretorias* SistemaFicheiros::Search(const string& nome) const{
    if(!raiz || nome.empty()){
        cout<<"Erro! Sistema não inicializado ou nome vazio."<<endl;
        return nullptr;
    }
    
    //começar pesquisa recursiva pela raiz
    return SearchRecursivo(raiz.get(), nome);
}

//Função auxiliar para pesquisa recursiva
Diretorias* SistemaFicheiros::SearchRecursivo(Diretorias* diretoria, const string& nome) const{
    if(!diretoria){
        return nullptr;
    }
    
    //verificar se a diretoria atual tem o nome procurado
    if(diretoria->getNomeDiretoria() == nome){
        cout<<"Diretoria '"<<nome<<"' encontrada!"<<endl;
        return diretoria;
    }
    
    //procurar nos ficheiros da diretoria atual
    auto& ficheiros = diretoria->getFicheiros();
    for(const auto& ficheiro : ficheiros){//procura todos os ficheiros da diretoria atual
        if(ficheiro->getNomeFicheiro() == nome){
            cout<<"Ficheiro '"<<nome<<"' encontrado na diretoria '"<<diretoria->getNomeDiretoria()<<"'!"<<endl;
            return diretoria; //retorna a diretoria onde está o ficheiro
        }
    }
    
    //procurar recursivamente nas subdiretorias
    auto& subDiretorias = diretoria->getSubDiretorias();
    for(const auto& subDir : subDiretorias){//procura todas as subdiretorias da diretoria atual
        Diretorias* resultado = SearchRecursivo(subDir.get(), nome);//chama a função recursivamente
        if(resultado != nullptr){
            return resultado; //encontrou, retorna o resultado
        }
    }
    
    //não encontrou em nenhum lugar
    return nullptr;
}


//verificação de load
//tem de devolver true se der load corretamente
bool SistemaFicheiros::Load(){
    if (!diretoriaAtual){
        cout << "Erro: Diretoria atual não está correta!" << endl;
        return false;
    }

    if (raiz->getNomeDiretoria().empty()){
        cout << "Erro: Nome da raiz vazio!" << endl;
        return false;
    }

    try{
        auto& ficheiros = raiz->getFicheiros();
        auto& subDiretorias = raiz->getSubDiretorias();
        return true;
    }catch (const exception& e){
        cout << "Erro ao aceder à estrutura: " << e.what() << endl;
        return false;
    }
}

int SistemaFicheiros::ContarFicheiros(Diretorias* diretoria){
    //esta função pode contar tanto todos os ficheiros guardados em memória
    //como pode contar todos os ficheiros apartir de uma diretoria alvo

    //se não for dada dirtetoria alvo, começa pela raiz
    if (!diretoria){
        diretoria = raiz.get();
    }

    //contar ficheiros na diretoria atual
    int total = diretoria->getFicheiros().size();

    //somar ficheiros de todas as subdiretorias recursivamente
    for(const auto& subDir : diretoria->getSubDiretorias()){
        total += ContarFicheiros(subDir.get());
    }

    return total;
}

int SistemaFicheiros::ContarDiretorias(Diretorias* diretoria){
    //esta função pode contar tanto todas as diretorias guardadas em memória
    //como pode contar todas as subdiretorias apartir de uma diretoria alvo
    
    //se não for dada diretoria lavo, comaça pela raiz
    if(!diretoria){
        diretoria = raiz.get();
    }

    //contar subdiretorias na diretoria atual
    int total = diretoria->getSubDiretorias().size() + 1;//mais 1 para contar a diretoria atual

    //somar subdiretorias de todas as subdiretorias recursivamente
    for(const auto& subDir : diretoria->getSubDiretorias()){
        total += ContarDiretorias(subDir.get());
    }
}
