#pragma once

#include <string>
#include "Datas.hpp"
using namespace std;

// Classe base abstrata para Ficheiros e Diretorias
class Elemento {
    protected:
        string nome; // nome do elemento (ficheiro ou diretoria)
        Datas dataCriacao;
        Datas dataModificacao;
    
    public:
        // Construtor
        Elemento(const string& nome, const Datas& dataCriacao, const Datas& dataModificacao);
        
        // Destrutor virtual para permitir polimorfismo
        virtual ~Elemento() = default;
        
        // Getters
        virtual string getNome() const;
        Datas getDataCriacao() const;
        Datas getDataModificacao() const;
        
        // Setters
        virtual void setNome(const string& nome);
        void setDataModificacao(const Datas& novaData);
        
        // Método virtual puro - cada subclasse implementa
        virtual bool isDiretoria() const = 0;
        
        // Métodos de verificação com nomes mais descritivos
        bool verificarDiretoria() const;
        bool verificarFicheiro() const;
        
        // Método virtual para obter tamanho (ficheiros têm tamanho, diretorias calculam recursivamente)
        virtual size_t getTamanho() const = 0;
};
