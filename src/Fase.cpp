#include "Fase.hpp"
#include "utils.hpp"
#include "Helicoptero.hpp"
#include "Base.hpp"
#include "SpriteAnimado.hpp"
#include "constantes.hpp"
#include "Item.hpp"
#include "Sound.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <unistd.h>
using namespace std;

Fase::Fase(){};
Fase::Fase(vector<ObjetoDoJogo> objetosDoJogo, string caminhoBackgroud){
    base = Base("sprites/base.txt", jogo::XINICIALBASE, jogo::YINICIALBASE);
    helicoptero = Helicoptero("sprites/helicoptero.txt",jogo::XINICIALHELICOPTERO , jogo::YINICIALHELICOPTERO);
    background = SpriteAnimado(caminhoBackgroud);
    objetos = objetosDoJogo;
    musica = Sound("sounds/musicafase1.mp3");
    somColetaItem = Sound("sounds/somcoletaitem.mp3");
    somColetaPessoa = Sound("sounds/somcoletapessoa.mp3");
    somSemCombustivel = Sound("sounds/somacaboucombustivel.mp3");
    somVitoria = Sound("sounds/somvitoria.mp3");
    somColisao = Sound("sounds/somcolisao.mp3");
    executando = true;
};

Fase::~Fase(){
    //musica.~Sound();
}

void Fase::inicializar(){
    //informações
    musica.playloop();
    for(int i=0; i< jogo::ALTURASECAOINFORMACOES; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            if(i==0){
                secaoInformacoes[i][j] = '~';
            }else if(i == jogo::ALTURASECAOINFORMACOES-1){
                secaoInformacoes[i][j] = '~';
            }else{
                if(j > 0 && j < 5){
                    secaoInformacoes[i][j] = ' ';
                }else if(j == 5){
                    //construção da barra de combustivel a partir da porcentagem atual do combustivel
                    string barraCombustivel = "";
                    int quantidadeBarra = util::calcularPorcentagem(helicoptero.getCombustivel(), helicoptero.getCombustivelMax())/10;
                    for(int i = 0; i < 10; i++){
                        if(i >= 0 && i < quantidadeBarra){
                            barraCombustivel.push_back('=');
                        }
                        else{
                            barraCombustivel.push_back('-');
                        }
                    }
                    for(int i = 0; i < 10 ; i++){
                        
                    }
                    secaoInformacoes[i][j] = "Combustivel " + barraCombustivel;
                }else if(j == 6){
                    secaoInformacoes[i][j] = "   Pessoas Resgatadas "
                                            +to_string(base.getPessoasResgatadas().size())
                                            +"/"
                                            +to_string(jogo::PESSOASRESGATAR);
                }else if(j == 7){
                    secaoInformacoes[i][j] = "   Capacidade "
                                            +to_string(helicoptero.getQntPessoas())
                                            +"/"
                                            +to_string(helicoptero.getCapacidadeMax());
                }
            }
        }
    }

    //jogo
    for(int i=0; i < jogo::ALTURAJOGO; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            secaoJogo[i][j] = ' ';
        }
    }
    desenhar(1,1,background.getSpriteAtual());
    for(int i = 0; i < objetos.size(); i++){
        ObjetoDoJogo obj = objetos[i];
        desenhar(obj);
    }
    desenhar(base);
    desenhar(helicoptero);
};


void Fase::mostrar(){
    //informações
    for(int i=0; i< jogo::ALTURASECAOINFORMACOES; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            cout << secaoInformacoes[i][j]; 
        }
        cout<<endl;
    }
    //jogo
    for(int i=0; i < jogo::ALTURAJOGO; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            cout << secaoJogo[i][j];
        }
        cout<<endl;
    }
};

void Fase::atualizar(){
    //informações
    for(int i=0; i< jogo::ALTURASECAOINFORMACOES; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            if(i==0){
                secaoInformacoes[i][j] = '~';
            }else if(i == jogo::ALTURASECAOINFORMACOES-1){
                secaoInformacoes[i][j] = '~';
            }else{
                if(j > 0 && j < 5){
                    secaoInformacoes[i][j] = ' ';
                }else if(j == 5){
                    //construção da barra de combustivel a partir da porcentagem atual do combustivel
                    string barraCombustivel = "";
                    int quantidadeBarra = util::calcularPorcentagem(helicoptero.getCombustivel(), helicoptero.getCombustivelMax())/10;
                    for(int i = 0; i < 10; i++){
                        if(i >= 0 && i < quantidadeBarra){
                            barraCombustivel.push_back('=');
                        }
                        else{
                            barraCombustivel.push_back('-');
                        }
                    }
                    for(int i = 0; i < 10 ; i++){
                        
                    }
                    secaoInformacoes[i][j] = "Combustivel " + barraCombustivel;
                }else if(j == 6){
                    secaoInformacoes[i][j] = "   Pessoas Resgatadas "
                                            +to_string(base.getPessoasResgatadas().size())
                                            +"/"
                                            +to_string(jogo::PESSOASRESGATAR);
                }else if(j == 7){
                    secaoInformacoes[i][j] = "   Capacidade "
                                            +to_string(helicoptero.getQntPessoas())
                                            +"/"
                                            +to_string(helicoptero.getCapacidadeMax());
                }
            }
        }
    }

    //jogo
    for(int i=0; i < jogo::ALTURAJOGO; i++){
        for(int j=0; j < jogo::LARGURAJOGO; j++){
            secaoJogo[i][j] = ' ';
        }
    }
    base.atualizar();
    helicoptero.atualizar();
    background.atualizar();
    desenhar(1,1,background.getSpriteAtual());
    desenhar(base);
    desenhar(helicoptero);
    for(int i = 0; i < objetos.size(); i++){
        ObjetoDoJogo *obj = &objetos[i];
        if(obj->getAtivo()){
            obj->atualizar();
            desenhar(*obj);
            if(obj->getItem()){
                if(helicoptero.colideComObjeto(*obj)){
                    somColetaItem.play();
                    helicoptero.abastece(jogo::BONUSITEM);
                    obj->desativa();
                }
            }
        }
    }
    if(base.getPessoasResgatadas().size() == jogo::PESSOASRESGATAR){
        executando = false;
        somVitoria.play();
    }
}

void Fase::desenhar(ObjetoDoJogo obj){
    int x = obj.getX();
    int y = obj.getY();
    SpriteAnimado sprites = obj.getSprites();
    vector<string> linhasDoSprite = sprites.getSpriteAtual().getLinhas();
    
    for(int linhaSprite = 0; linhaSprite < linhasDoSprite.size(); linhaSprite++){
        string linha = linhasDoSprite[linhaSprite];
        for(int indice = 0; indice < linha.length(); indice++){
            secaoJogo[y+linhaSprite][x+indice] = linha[indice]; 
        }
    }
}

void Fase::desenhar(int y, int x,Sprite spr){
    vector<string> linhasDoSprite = spr.getLinhas();
    for(int linhaSprite = 0; linhaSprite < linhasDoSprite.size(); linhaSprite++){
       string linha = linhasDoSprite[linhaSprite];
       for(int indice = 0; indice < linha.length(); indice++){
           secaoJogo[y+linhaSprite][x+indice] = linha[indice]; 
       }
    }
}

void Fase::jogar(){
    string cmd;
    inicializar();
    while(executando){
        mostrar();
        cin >> cmd;
        if(cmd == "x"){
        for(int i = 0; i < objetos.size(); i++){
            ObjetoDoJogo* objColisao = &objetos[i];
            if(!objColisao->getObstaculo()){
                if(helicoptero.colideComObjeto(*objColisao) && helicoptero.getQntPessoas()+1 <= helicoptero.getCapacidadeMax()){ 
                    somColetaPessoa.play();
                    objColisao->desativa();
                    helicoptero+*objColisao;
                }
            }
            }
        if(helicoptero.getX() >= base.getX() && helicoptero.getX()+helicoptero.getLargura()<= base.getX() + base.getLargura()){
            if(helicoptero.getY()+helicoptero.getAltura() == base.getY()+1){
                if(helicoptero.getPessoasResgatadas().size() > 0){
                    ObjetoDoJogo pessoaResgatada = --helicoptero;
                    base+pessoaResgatada;
                }
            }
        }
        }else if(cmd == "p"){}
        else if(cmd == "q"){
            executando = false;
        }else{
            helicoptero.moveTo(cmd);
            for(int i = 0; i < objetos.size(); i++){
                ObjetoDoJogo obj = objetos[i];
                if(helicoptero.getCombustivel() < 1){
                    executando = false;
                    somSemCombustivel.play();
                }
                if(helicoptero.colideComObjeto(obj) && obj.getObstaculo()){
                    executando = false;
                    somColisao.play();
                }
            }
        }
        atualizar();
        system("clear");
    }
    musica.stop();
    cin >> cmd;
    system("clear");
}