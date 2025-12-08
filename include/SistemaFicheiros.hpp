#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include "Ficheiros.hpp"
#include "Diretorias.hpp"

// Struct para armazenar informação dos ficheiros
struct InfoFicheiro {
    string nome;
    size_t tamanho;
    string caminho;
};

class SistemaFicheiros{
    private:
        unique_ptr<Diretorias> raiz;
        Diretorias* diretoriaAtual;
        Diretorias* diretoriaAnterior;
        
        //Funções auxiliares privadas para recursividade
        //estas funções são usadas internamente pela classe
        //servem apenas para simplificar o código público
        Diretorias* SearchRecursivo(Diretorias* diretoria, const string& nome) const;
        Diretorias* DiretoriaMaisElementosRecursivo(Diretorias* diretoria);
        Diretorias* DiretoriaMenosElementosRecursivo(Diretorias* diretoria);
        Ficheiros* FicheiroMaiorRecursivo(Diretorias* diretoria);
        void RemoveAllRecursivo(Diretorias* diretoria);
        void RemoveAllFicheirosRecursivo(Diretorias* diretoria);
        Datas* DataModificacaoFicheiro(const string& nomeFicheiro);//função auxiliar para obter a data de modificação
        void PesquisarAllFicheirosRecursivo(Diretorias* diretoria, const string& caminho, const string& nomeFicheiro);//função auxiliar recursiva para procurar ficheiros
        void FicheirosDuplicadosRecursivo(Diretorias* diretoria, const string& caminho, vector<InfoFicheiro>& todosFicheiros);//função auxiliar recursiva para encontrar duplicados
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
        int ContarFicheiros(Diretorias* diretoria = nullptr);//função para contar ficheiros recursivamente(tenho que fazer a função apartir da raiz)
        int ContarDiretorias(Diretorias* diretoria = nullptr);//função que faz a contagem de diretorias recursivamente(tenho de fazer a função apartir da raiz)
        size_t Memoria(Diretorias* diretoria = nullptr);//função para calcular a memória ocupada
        Diretorias* DiretoriaMaisElementos();//função para determinar a diretoria com mais informação
        Diretorias* DiretoriaMenosElementos();//função para determinar a diretorias com menos informação
        Ficheiros* FicheiroMaior();//função para encontrar o maior ficheiro
        Diretorias* DiretoriaMaisEspaco();//função para encontrar a maior diretoria
        bool RemoveAll(const string& confirmacao);//função para remover todo o conteudo. Tem que escrever "DIR" para confirmar
        void Escrever_XML();//função para gravar os ficheiro em formato XML para todo o Sistema de Ficheiros
        bool Ler_XML();//função para ler os ficheiros em formato XML para todo o Sistema de Ficheiros
        bool MoverFicheiro(const string& nomeFicheiro, Diretorias* destino);//função para mover ficheiros entre diretorias
        bool MoverDiretoria(const string& nomeDiretoria, Diretorias* destino);//função para mover diretorias entre diretorias
        Datas* DataFicheiro (const string& nomeFicheiro);//função para mostrar ambas as datas (criação e modificação) e devolver a data de criação
        void PesquisarAllFicheiros(const string& nomeFicheiro);//função para procurar e listar todos os ficheiros com o nome especificado recursivamente
        void PesquisarAllDiretorias(const string& nomeDiretoria);//função para procurar e listar todas as diretorias com o nome especificado na diretoria atual
        void RenomearFicheiros(const string& nomeAntigo, const string& nomeNovo);//função para renomear um ficheiro
        //falta esta função e depois só faltam a da tree, de escrever XML e ler XML e por fim a de CopyBach
        bool FicheirosDuplicados(Diretorias* diretoria = nullptr);//função para encontrar ficheiros duplicados no sistema de ficheiros
};