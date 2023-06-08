#ifndef FASE_H
#define FASE_H
#include "ObjetoDoJogo.h"
#include "Base.h"
#include "Sprite.h"
#include "Helicoptero.h"
#include "constantes.h"
#include <vector>
#include <iostream>
using namespace std;

class Fase{
    private:
        vector<ObjetoDoJogo> objetos;
        Base base;
        Helicoptero helicoptero;
        string tela[jogo::ALTURAJOGO][jogo::LARGURAJOGO];
        int qntdPessoasResgatadas;
        bool executando;
    public:
        Fase();
        Fase(vector<ObjetoDoJogo> objetosDoJogo);
        void mostrar();
        void inicializar();
        void atualizar();
        void desenharEntidade(ObjetoDoJogo obj);
        void desenharEntidade(int y, int x, Sprite obj);
        void jogar();
};

#endif