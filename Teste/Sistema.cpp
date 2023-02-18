#include "Sistema.h"

Sistema::Sistema()
{
    White = new Equipa("White");
    Black = new Equipa("Black");
    int i; int j; int k; int l;
    for(i=0; i<8; i++){
        tabuleiro[1][i] = White->getPecas()[i];
    }
    for(j=0; j<8; j++){
        tabuleiro[6][j] = Black->getPecas()[j];
    }
    for(k=8; k<16; k++){
        tabuleiro[0][k-8] = White->getPecas()[k];
    }
    for(l=8; l<16; l++){
        tabuleiro[7][l-8] = Black->getPecas()[l];
    }
}

Peca* Sistema::getPeca(int c, int l){  // Pode ser útil (é - está a ser)
    return tabuleiro[l][c];
}

// Verifica as Colisões dos Bispo, Torre e Rainha
bool Sistema::verificaColisoes(Peca *a, int c, int l){
    int x = a->getColuna() - 1; int y = a->getLinha() - 1;  //Casa da peca a ser verificada
    if(a->getNome()[1] == 'T' || a->getNome()[1] == 'Q'){
        if(x == c){
            if(l > y){
                for(int i=1; i<abs(y-l); i++){
                    if(tabuleiro[y+i][x] != nullptr) return false;
                }
            }
            else if(l < y){
                for(int i=1; i<abs(y-l); i++){
                    if(tabuleiro[y-i][x] != nullptr) return false;
                }
            }
        }
        else if(y == l){
            if(c > x){
                for(int i=1; i<abs(x-c); i++){
                    if(tabuleiro[y][x+i] != nullptr) return false;
                }
            }
            else if(c < x){
                for(int i=1; i<abs(x-c); i++){
                    if(tabuleiro[y][x-i] != nullptr) return false;
                }
            }
        }
    }
    if((a->getNome()[1] == 'B' || a->getNome()[1] == 'Q' && abs(x-c) == abs(y-l))){
        if(c > x && l > y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y+i][x+i] != nullptr) return false;
            }
        }
        else if(c < x && l < y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y-i][x-i] != nullptr) return false;
            }
        }
        else if(c < x && l > y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y+i][x-i] != nullptr) return false;
            }
        }
        else if(c > x && l < y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y-i][x+i] != nullptr) return false;
            }
        }
    }
    else if(a->getNome()[1] == 'P' && a->getLinha() == 2 && l == 3 && tabuleiro[2][c] != nullptr) return false;
    return true;
}

// Verifica as Colisões dos Bispo, Torre e Rainha
string Sistema::getPosicoesCheck(Peca *a, int c, int l){
    string posicoes;
    int x = a->getColuna() - 1; int y = a->getLinha() - 1;  //Casa da peca a ser verificada
    if(a->getNome()[1] == 'T' || a->getNome()[1] == 'Q'){
        if(x == c){
            if(l > y){
                for(int i=1; i<abs(y-l); i++){
                    if(tabuleiro[y+i][x] != nullptr){
                        string pos = to_string(10*(x+1) + (y+i+1));
                        posicoes += pos;
                    }
                }
            }
            else if(l < y){
                for(int i=1; i<abs(y-l); i++){
                    if(tabuleiro[y-i][x] != nullptr){
                        string pos = to_string(10*(x+1) + (y+1)-i);
                        posicoes += pos;
                    }
                }
            }
        }
        else if(y == l){
            if(c > x){
                for(int i=1; i<abs(x-c); i++){
                    if(tabuleiro[y][x+i] != nullptr){
                        string pos = to_string(10*((x+1)+i) + (y+1));
                        posicoes += pos;
                    }
                }
            }
            else if(c < x){
                for(int i=1; i<abs(x-c); i++){
                    if(tabuleiro[y][x-i] != nullptr){
                        string pos = to_string(10*((x+1)-i) + (y+1));
                        posicoes += pos;
                    }
                }
            }
        }
    }
    if((a->getNome()[1] == 'B' || a->getNome()[1] == 'Q' && abs(x-c) == abs(y-l))){
        if(c > x && l > y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y+i][x+i] != nullptr){
                    string pos = to_string(10*((x+1)+i) + (y+1)+i);
                    posicoes += pos;
                }
            }
        }
        else if(c < x && l < y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y-i][x-i] != nullptr){
                    string pos = to_string(10*((x+1)-i) + (y+1)-i);
                    posicoes += pos;
                }
            }
        }
        else if(c < x && l > y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y+i][x-i] != nullptr){
                    string pos = to_string(10*((x+1)-i) + (y+1)+i);
                    posicoes += pos;
                }
            }
        }
        else if(c > x && l < y){
            for(int i=1; i<abs(x-c); i++){
                if(tabuleiro[y-i][x+i] != nullptr){
                    string pos = to_string(10*((x+1)+i) + (y+1)-i);
                    posicoes += pos;
                }
            }
        }
    }
    return posicoes;
}


// Verifica se é feito um autocheck e reverte a jogada - devolve true se algo for feito, devolve false se estiver tudo em ordem
bool Sistema::verificaAutoCheck(Peca *a, Peca *v, int x, int y){  // Coordenadas antigas
    int c = a->getColuna() - 1; int l = a->getLinha() - 1;  //Coordenadas novas
    if(a->getEquipa() == "White" && verificaCheckW()){
        tabuleiro[y][x] = a;
        tabuleiro[l][c] = v;
        if(v != nullptr){v->Move(c+1, l+1); v->setDentro(true);}
        a->Move(x+1, y+1);
        return true;
    }
    else if(a->getEquipa() == "Black" && verificaCheckB()){
        tabuleiro[y][x] = a;
        tabuleiro[l][c] = v;
        if(v != nullptr){v->Move(c+1, l+1); v->setDentro(true);}
        a->Move(x+1, y+1);
        return true;
    }
    return false;
}

// Devolve verdadeiro se o Rei PRETO estiver em check
bool Sistema::verificaCheckB(){  //Verifica se o Rei PRETO está em check
    Peca *k = Black->Busca("BKg");
    int x = k->getColuna() - 1;
    int y = k->getLinha() - 1;
    for(int i=0; i<White->getPecas().size(); i++){
        Peca *a = White->getPecas()[i];
        if(a->getNome()[1] != 'K' && a->getNome()[1] != 'P' && a->getDentro() == true && a->verificadorMove(x+1, y+1) && verificaColisoes(a, x, y)){
            return true;  //Outra ideia é alterar um atributo do sistema
        }
        if(a->getNome()[1] == 'P' && a->getDentro() == true && a->verificadorCome(x+1, y+1)){  // NO futuro, não esquecer de verificar colisões, caso ponha
            return true;  //Outra ideia é alterar um atributo do sistema
        }
    }
    return false;
}

// Devolve verdadeiro se o Rei BRANCO estiver em check
bool Sistema::verificaCheckW(){  //Verifica se o Rei BRANCO está em check
    Peca *k = White->Busca("WKg");
    int x = k->getColuna() - 1;
    int y = k->getLinha() - 1;
    for(int i=0; i<Black->getPecas().size(); i++){
        Peca *a = Black->getPecas()[i];
        if(a->getNome()[1] != 'K' && a->getNome()[1] != 'P' && a->getDentro() == true && a->verificadorMove(x+1, y+1) && verificaColisoes(a, x, y)){
            return true;  //Outra ideia é alterar um atributo do sistema
        }
        if(a->getNome()[1] == 'P' && a->getDentro() == true && a->verificadorCome(x+1, y+1)){  // NO futuro, não esquecer de verificar colisões, caso ponha
            return true;  //Outra ideia é alterar um atributo do sistema
        }
    }
    return false;
}

// Devolve a peça que está a colocar o rei PRETO em check
Peca* Sistema::DevolveCheckB(){
    Peca *k = Black->Busca("BKg");
    int x = k->getColuna() - 1;
    int y = k->getLinha() - 1;
    for(int i=0; i<White->getPecas().size(); i++){
        Peca *a = White->getPecas()[i];
        if(a->getNome()[1] != 'K' && a->getNome()[1] != 'P' && a->getDentro() == true && a->verificadorMove(x+1, y+1) && verificaColisoes(a, x, y)){
            return a;
        }
        if(a->getNome()[1] == 'P' && a->getDentro() == true && a->verificadorCome(x+1, y+1)){  // NO futuro, não esquecer de verificar colisões, caso ponha
            return a;
        }
    }
    return nullptr;
}

// Devolve a peça que coloca o Rei BRANCO em check
Peca* Sistema::DevolveCheckW(){
    Peca *k = White->Busca("WKg");
    int x = k->getColuna() - 1;
    int y = k->getLinha() - 1;
    for(int i=0; i<Black->getPecas().size(); i++){
        Peca *a = Black->getPecas()[i];
        if(a->getNome()[1] != 'K' && a->getNome()[1] != 'P' && a->getDentro() == true && a->verificadorMove(x+1, y+1) && verificaColisoes(a, x, y)){
            return a;
        }
        if(a->getNome()[1] == 'P' && a->getDentro() == true && a->verificadorCome(x+1, y+1)){  // NO futuro, não esquecer de verificar colisões, caso ponha
            return a;
        }
    }
    return nullptr;
}

// Esta função verifica o checkmate
bool Sistema::verificaCheckMate(){
    //Vê se há check
    Peca * check = DevolveCheckW();
    if(check == nullptr) return false;

    //Busca o Rei
    Peca* rei = White->Busca("WKg");

    //Verifica se o rei tem movimentos
    int x = rei->getColuna() - 1;
    int y = rei->getLinha() - 1;
    for(int i=-1; i==1; i++){
        for(int k=-1; k==1; k++){
            Peca* v = tabuleiro[y+k][x+i];
            if(i != 0 || k !=0){
                if(x+i >=0 && x+i <=7 && y+k >= 0 && y+k <= 7 && (v == nullptr ||(v != nullptr && v->getEquipa() != rei->getEquipa()))){
                    Movimento(rei, x+i, y+k);
                    //Restaura o tabuleiro
                    if(!verificaCheckW()){
                        tabuleiro[y][x] = check;
                        tabuleiro[y+k][x+i] = v;
                        if(v != nullptr){v->Move(x+i+1, y+k+1); v->setDentro(true);}
                        check->Move(x+1, y+1);
                        //Devolve false caso o rei tenha para onde fugir
                     return false;
                    }
                    else{
                        tabuleiro[y][x] = check;
                        tabuleiro[y+k][x+i] = v;
                        if(v != nullptr){v->Move(x+i+1, y+k+1); v->setDentro(true);}
                        check->Move(x+1, y+1);
                    }
                }
            }
        }
    }
    string posis = getPosicoesCheck(check, x, y);
    for(int l=0; l*2<posis.size(); l++){

    }
}

//a -> Peca a Mover (Rei)
void Sistema::Castle(Peca *a, int c, int l){
    int x = a->getColuna() - 1; int y = a->getLinha() - 1;
    if(c > x && tabuleiro[y][x+1] == nullptr && tabuleiro[y][x+2] == nullptr && tabuleiro[y][x+3]->getNome()[1] == 'T' && tabuleiro[y][x+3]->getEquipa() == a->getEquipa()){
        Peca * b = tabuleiro[y][x+1];  //Peça nulidade
        tabuleiro[y][x] = tabuleiro[y][x+2];
        tabuleiro[y][x+1] = tabuleiro[y][x+3];
        tabuleiro[y][x+2] = a;
        tabuleiro[y][x+3] = b;
        a->Move(c, l);
        tabuleiro[y][x+1]->Move(c, l+1);
        tabuleiro[y][x+1]->setPosRep(110, c-1, l);
    }
    if(c < x && tabuleiro[y][x-1] == nullptr && tabuleiro[y][x-2] == nullptr && tabuleiro[y][x-3] == nullptr && tabuleiro[y][x-4]->getNome()[1] == 'T' && tabuleiro[y][x-4]->getEquipa() == a->getEquipa()){
        Peca * b = tabuleiro[y][x-1];  //Peça nulidade
        tabuleiro[y][x] = tabuleiro[y][x-2];
        tabuleiro[y][x-1] = tabuleiro[y][x-4];
        tabuleiro[y][x-2] = a;
        tabuleiro[y][x-4] = b;
        a->Move(c+1, l);
        tabuleiro[y][x-1]->Move(c+2, l+1);
        tabuleiro[y][x-1]->setPosRep(110, c+1, l);
    }
}

//Faz o movimento natural das peças
void Sistema::Movimento(Peca *a, int c, int l){
    int x = a->getColuna() - 1; int y = a->getLinha() - 1;
    Peca * v = getPeca(c, l);
    a->Move(c+1, l+1);  //Faz o mov. de uma peça de casa para casa
    tabuleiro[l][c] = a;
    tabuleiro[y][x] = nullptr;
    if(v != nullptr) v->setDentro(false);
}

bool Sistema::PromovePeao(Peca *a, int c, int l, string escolha){
    if(a->getNome()[1] == 'P' && (a->getLinha() == 8 || a->getLinha() == 1)){
        a->Move(c+1, l+1);
        if(a->getEquipa() == "White"){
            a->setDentro(false);
            tabuleiro[l][c] = White->promovePiao(escolha, c+1, l+1, a);
            return true;
        }
        else if(a->getEquipa() == "Black"){
            a->setDentro(false);
            tabuleiro[l][c] = Black->promovePiao(escolha, c+1, l+1, a);
            return true;
        }
        return false;
    }
    return false;
}

Equipa Sistema::getWhite(){
    return *White;
}

Equipa Sistema::getBlack(){
    return *Black;
}
