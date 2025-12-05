#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include "Ficheiros.hpp"
using namespace std;

class Diretorias {
    private:
        string nomeDiretoria; // nome da diretoria
        vector<unique_ptr <Ficheiros>> ficheiros; //vetor de ficheiros na diretoria
        vector<unique_ptr <Diretorias>> subDiretorias; //vetor de subdiretorias 
        Diretorias *DiretoriaPai;//ponteiro para a diretoria raiz das subdiretorias
    public:
        //contrutor
        Diretorias(const string &nomeDiretoria);//para as diretorias só é obrigatório o nome

        //destrutor
        ~Diretorias()=default; //não é necessário mas é boa prática

        //getters
        const string getNomeDiretoria() const;//define o nome da diretoria
        const vector<unique_ptr<Ficheiros>>& getFicheiros() const;//recolhe os ficheiros da diretoria atual
        const vector<unique_ptr<Diretorias>>& getSubDiretorias();//recolhe as subdiretorias da diretoria atual
        Diretorias* getDiretoriaPai() const;//serve para definir a diretoria pai

        //setters
        void setNomeDiretoria(const string &nome);// o const impede que se altera o conteudo do endereço inicial
        void setDiretoriaPai(unique_ptr<Diretorias> addSubDiretoria);
        
        //metodos para adicionar informação
        //os ficheiros e subdiretorias não podem ser alterados diretamente
        void addFicheiro(unique_ptr<Ficheiros> ficheiro);//adiciona um ficheiro à diretoria atual
        void addSubDiretoria(unique_ptr<Diretorias> subDiretoria);//adiciona uma subdiretoria à diretoria atual
        
        //método para encontrar subdiretoria
        Diretorias* encontrarSubDiretoria(const string& nome) const;//função para encontrar uma subdiretoria dentro de uma diretoria
};  