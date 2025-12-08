#include "../include/Elemento.hpp"

// Construtor
Elemento::Elemento(const string& nome, const Datas& dataCriacao, const Datas& dataModificacao)
    : nome(nome), dataCriacao(dataCriacao), dataModificacao(dataModificacao) {}

// Getters
string Elemento::getNome() const {
    return nome;
}

Datas Elemento::getDataCriacao() const {
    return dataCriacao;
}

Datas Elemento::getDataModificacao() const {
    return dataModificacao;
}

// Setters
void Elemento::setNome(const string& novoNome) {
    nome = novoNome;
}

void Elemento::setDataModificacao(const Datas& novaData) {
    dataModificacao = novaData;
}

// Métodos de verificação
bool Elemento::verificarDiretoria() const {
    return isDiretoria();
}

bool Elemento::verificarFicheiro() const {
    return !isDiretoria();
}