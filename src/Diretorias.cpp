#include "Diretorias.hpp"
#include "Ficheiros.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

//declaração das variaveis desta classe
Diretorias::Diretorias(const string& nomeDiretoria)
    : Elemento(nomeDiretoria, Datas(1, 1, 2024), Datas(1, 1, 2024)), // datas default
      DiretoriaPai(nullptr) {
}
//getters
const string Diretorias::getNomeDiretoria() const{
    return getNome(); // usa o método da classe base
}
const vector<unique_ptr<Ficheiros>>& Diretorias::getFicheiros() const{
    return ficheiros;//getter do ficheiro
}
const vector<unique_ptr<Diretorias>>& Diretorias::getSubDiretorias(){
    return subDiretorias;//getter da subdiretoria
}
Diretorias* Diretorias::getDiretoriaPai() const{
    return DiretoriaPai;//getter do ponteiro da diretoria raiz
}

// Override de métodos virtuais
bool Diretorias::isDiretoria() const {
    return true; // diretorias são diretorias
}

size_t Diretorias::getTamanho() const {
    size_t tamanhoTotal = 0;
    
    // Soma o tamanho de todos os ficheiros
    for (const auto& ficheiro : ficheiros) {
        tamanhoTotal += ficheiro->getTamanhoFicheiro();
    }
    
    // Soma recursivamente o tamanho de todas as subdiretorias
    for (const auto& subDir : subDiretorias) {
        tamanhoTotal += subDir->getTamanho();
    }
    
    return tamanhoTotal;
}

//setters
void Diretorias::setNomeDiretoria(const string& nome){
    setNome(nome); // usa o método da classe base
}

void Diretorias::setDiretoriaPai(Diretorias* pai) {
    DiretoriaPai = pai;
}

//outras funções
void Diretorias::addFicheiro(unique_ptr<Ficheiros> ficheiro){
    ficheiros.push_back(move(ficheiro));//função para adicionar ficheiro
    //sempre que se utiliza o "push_back" estamos a adicionar à lista algo
}
void Diretorias::addSubDiretoria(unique_ptr<Diretorias> subDiretoria){
    subDiretoria->DiretoriaPai = this;//declaramos o ponteiro pai desta subdiretoria
    subDiretorias.push_back(move(subDiretoria));//adicionamos uma nova subdiretoria à diretoria onde declaramos o ponteiro pai
}
Diretorias* Diretorias::encontrarSubDiretoria(const string& nome) const{
    for(const auto& sub: subDiretorias){//loop por todos os elementos da subdiretoria
        if(sub->getNomeDiretoria() == nome){//recolhe o nome de "sub" e verifica se é igual ao nome do conteudo que está a ler
            return sub.get();
        }
    }
    return nullptr;
}

