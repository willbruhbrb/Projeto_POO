#include "Diretorias.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

//declaração das variaveis desta classe
Diretorias::Diretorias(const string& nomeDiretoria)
    :nomeDiretoria(nomeDiretoria), DiretoriaPai(nullptr){
}
//getters
const string Diretorias::getNomeDiretoria() const{
    return nomeDiretoria;//getter do nome da diretoria
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

//setters
void Diretorias::setNomeDiretoria(const string& nome){
    nomeDiretoria = nome;//setter do nome
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

