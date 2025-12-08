#include "Ficheiros.hpp"
#include "Datas.hpp"
#include <iostream>
using namespace std;

//contrutor
Ficheiros::Ficheiros(const string& nome, const size_t tamanho, const Datas& dataCriacao, const Datas& dataModificacao)
    : Elemento(nome, dataCriacao, dataModificacao),
      tamanhoFicheiro(tamanho) {
}

//getters
string Ficheiros::getNomeFicheiro() const{
    return getNome(); // usa o método da classe base
}

size_t Ficheiros::getTamanhoFicheiro() const{
    return tamanhoFicheiro;
}

// Override de métodos virtuais
bool Ficheiros::isDiretoria() const {
    return false; // ficheiros não são diretorias
}

size_t Ficheiros::getTamanho() const {
    return tamanhoFicheiro;
}

//setters

void Ficheiros::setNomeFicheiro(const string& nome){
    setNome(nome); // usa o método da classe base
}

void Ficheiros::setTamanhoFicheiro(size_t tamanho){
    tamanhoFicheiro = tamanho;
}
