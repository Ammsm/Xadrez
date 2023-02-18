#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include "Equipa.h"

class Sistema
{
    public:
        Sistema();
        Peca* getPeca(int c, int l);
        bool verificaColisoes(Peca *a, int c, int l);
        string getPosicoesCheck(Peca *a, int c, int l);
        bool verificaAutoCheck(Peca *a, Peca *v, int c, int l);
        bool verificaCheckB();
        bool verificaCheckW();
        Peca* DevolveCheckB();
        Peca* DevolveCheckW();
        bool verificaCheckMate();

        void Move(Peca *a, int c, int l);

        void Castle(Peca *a, int c, int l);
        void Movimento(Peca *a, int c, int l);
        bool PromovePeao(Peca *a, int c, int l, string escolha);

        Equipa getWhite();
        Equipa getBlack();

    protected:

    private:
        Equipa *White = nullptr;
        Equipa *Black = nullptr;
        Peca* tabuleiro[8][8];  // Para o verificador do checks devia criar outra tabuleiro para poder voltar a trás
};

#endif // SISTEMA_H
