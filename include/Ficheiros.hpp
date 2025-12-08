#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "Datas.hpp"
#include "Elemento.hpp"
using namespace std;

class Ficheiros : public Elemento {
    private:
        size_t tamanhoFicheiro; // tamanho do ficheiro em bytes

    public:
        /*contrutor
        inicializa os atributos do ficheiro
        */
        Ficheiros(const string &nomeFicheiro, size_t tamanhoFicheiro, const Datas& dataCriacao, const Datas& dataModificacao);

        /*destrutor
        Liberta a memória alocada para o ficheiro
        */
        ~Ficheiros()= default;// não é necessário mas é boa prática

        // Getters (nome vem da classe base)
        string getNomeFicheiro() const; // wrapper para getNome()
        size_t getTamanhoFicheiro() const;
        
        // Override de métodos virtuais da classe base
        bool isDiretoria() const override;
        size_t getTamanho() const override;

        // Setters
        void setNomeFicheiro(const string& nome); // wrapper para setNome()
        void setTamanhoFicheiro(size_t tamanho);
s};