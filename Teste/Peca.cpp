#include <iostream>
#include "Peca.h"

Peca::Peca()
{

}

void Peca::setNome(string n){
    nome = n;
}

void Peca::setColuna(int c){
    coluna = c;
}

void Peca::setLinha(int l){
    linha = l;
}

void Peca::setPosicao(int c, int l){
    setColuna(c);
    setLinha(l);
}

void Peca::setEquipa(string e){
    equipa = e;
}

string Peca::getNome(){
    return nome;
}

string Peca::getEquipa(){
    return equipa;
}

int Peca::getColuna(){
    return coluna;
}

int Peca::getLinha(){
    return linha;
}

bool Peca::verificadorMove(int x, int y){

}

void Peca::Move(int x, int y){

}

bool Peca::verificadorCome(int x, int y){

}

bool Peca::getCastle(){
    return castle;
}

bool Peca::getDentro(){
    return dentro;
}

void Peca::setDentro(bool d){
    dentro = d;
}

string Peca::getTextura(string equipa){

}

void Peca::criaSprite(int lado){

}

sf::Sprite Peca::getSprite(){

}

void Peca::setPosRep(int lado, int c, int l){

}

void Peca::CoordssetPosRep(int lado, int x, int y){

}

void Peca::setOrigem(int x, int y){

}

void Peca::setEscala(float x, float y){

}
