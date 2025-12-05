#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

class Datas{
    private:
    //as datas vão ser guardas com os parametros do dia, mês e ano para garantir a flexiblidade da apresentação e uso da data
        //data de criação
        uint16_t diaCriacao;
        uint16_t mesCriacao;
        uint16_t anoCriacao;

        //data de modificação
        uint16_t diaModificacao;
        uint16_t mesModificacao;
        uint16_t anoModificacao;
    public:
        //construtor
        Datas();
        //destrutor
        ~Datas();

        //getters
        uint16_t getDiaCriacao() const;//recolhe o dia da criação do ficheiro
        uint16_t getMesCriacao() const;//recolhe o mês da criação do ficheiro
        uint16_t getAnoCriacao() const;//recolhe o ano da criação do ficheiro

        //setters
        void setDataModificacao(uint16_t dia, uint16_t mes, uint16_t ano);//função para atualizar a data de alteração do ficheiro
};