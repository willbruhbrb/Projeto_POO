#pragma once

#include <iostream>
#include <filesystem>
#include "Ficheiros.hpp"
#include "Diretorias.hpp"

class SistemaFicheiros{
    private:
        unique_ptr<Diretorias> raiz;
        Diretorias* diretoriaAtual;
        Diretorias* diretoriaAnterior;
        
        //Funções auxiliares privadas para recursividade
        Diretorias* SearchRecursivo(Diretorias* diretoria, const string& nome) const;
    public:
        //contrutor
        SistemaFicheiros();
        //Destrutor
        ~SistemaFicheiros()=default;
        
        //getters não são necessários porque esta classe utiliza as caracteristicas das classes "Datas", "Ficheiros" e "Diretorias"
        //assim faz-se só a declaração das funções que se pretende fazer com esta classe
        
        //Navegação:
        void cd(const string& caminho);//para fazer o comando cd *comando*
        //este comando é base de todos os comandos de movimento no linux, o exemplo que vamos utilizar

        //Criação ou destruição
        Diretorias* CriarDiretoria(const string& nomeDiretoria);//função para criar uma Diretoria("mkdir *nome*" em linux)
        Diretorias* CriarFicheiro(const string& nomeFicheiro, size_t tamanho = 0);//função para criar um Ficheiro("touch *nome*" em linux)
        bool RemoverFicheiro(string& nomeFicheiro);//função para remover um ficheiro ou diretoria de uma diretoria("rm *nome*" em linux)
        bool RemoverDiretoria(string& nomeDiretoria);//função para remover uma diretoria("rmdir *nome*" em linux)

        //Listagem
        void ListarConteudo() const;//função para listar as diretorias e ficheiros dentro de uma diretoria("ls" em linux)
        
        //Busca
        Diretorias* Search(const string& nome) const;//função para fazer a pesquiza recursivamente

        //outras funções
        bool Load();//função para verificar se deu load corretamente do conteudo de uma diretoria
        int ContarFicheiros(Diretorias* diretoria = nullptr);//função para contar ficheiros recursivamente
        int ContarDiretorias(Diretorias* diretoria = nullptr);//função que faz a contagem de diretorias recursivamente
        int Memoria();//função para calcular a memória ocupada (por fazer)
        Diretorias* DiretoriaMaisElementos();//função para determinar a diretoria com mais informação (por fazer)
        Diretorias* DiretoriaMenosElementos();//função para determinar a diretorias com menos informação (por fazer)
        Ficheiros* FicheiroMaior();//função para encontrar o maior ficheiro (por fazer)
        Diretorias* DiretoriaMaior();//função para encontrar a maior diretoria (por fazer)
};