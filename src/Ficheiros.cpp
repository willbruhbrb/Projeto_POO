#include "Ficheiros.hpp"
#include "Datas.hpp"
#include <iostream>
using namespace std;

//contrutor
Ficheiros::Ficheiros(const string& nome, const size_t tamanho, const Datas& dataCriacao, const Datas& dataModificacao)
    :nomeFicheiro(nome),
     tamanhoFicheiro(tamanho),
     dataCriacao(dataCriacao),
     dataModificacao(dataModificacao){
}

//getters
string Ficheiros::getNomeFicheiro() const{
    return nomeFicheiro;
}

size_t Ficheiros::getTamanhoFicheiro() const{
    return tamanhoFicheiro;
}

Datas Ficheiros::getDataCriacao() const{
    return dataCriacao;
}

Datas Ficheiros::getDataModificacao() const{
    return dataModificacao;
}

//setters

void Ficheiros::setNomeFicheiro(const string& nome){
    nomeFicheiro = nome;
}

void Ficheiros::setTamanhoFicheiro(size_t tamanho){
    tamanhoFicheiro = tamanho;
}

void Ficheiros::setDataModificacao(Datas &novaData){
    dataModificacao = novaData;
}
