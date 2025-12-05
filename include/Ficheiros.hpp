#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "Datas.hpp"
using namespace std;

class Ficheiros{
    private:
        string nomeFicheiro;//nome do ficheiro
        size_t tamanhoFicheiro;//tamanho do ficheiro em bytes

       Datas dataCriacao;//As datas foram feitas numa classe diferente
       Datas dataModificacao;

    public:
        /*contrutor
        inicializa os atributos do ficheiro
        */
        Ficheiros(const string &nomeFicheiro, size_t tamanhoFicheiro, const Datas& dataCriacao, const Datas& dataModificacao);

        /*destrutor
        Liberta a memória alocada para o ficheiro
        */
        ~Ficheiros()= default;// não é necessário mas é boa prática

        /*getters
        estes métodos retornam os atributos do ficheiro
        */
        string getNomeFicheiro() const;//defenir o nome do ficheiro
        size_t getTamanhoFicheiro() const;//calcular o tamanho do ficheiro
        Datas getDataCriacao() const;//definir a data de criação
        Datas getDataModificacao() const;//recolher a data de modificação

        /*setters
        estes métodos permitem alterar os atributos do ficheiro
        por isso vamos só atribui-los apenas a valores alteráveis
        */
        void setNomeFicheiro(const string & nome);
        void setTamanhoFicheiro(size_t tamanho);
        void setDataModificacao(Datas &novaData);
        //só a data de modificação visto que não se vai alterar a data de criação do ficheiro
};