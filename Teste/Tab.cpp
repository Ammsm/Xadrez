#include "Tab.h"

Tab::Tab()
{
    Jogo = new Sistema();
}

// Transforma a coluna em coordenadas da janela
int Tab::CcoordsX(int c){
    int x = lado/2 + c*lado;
    return x;
}

// Transforma a linha em coordenadas da janela
int Tab::LcoordsY(int l){
    int y = lado/2 - (l-7)*lado;
    return y;
}

Peca * Tab::getPeca(int c, int l){
    return Jogo->getPeca(c, l);
}

void Tab::PromovePeao(Peca * peca, int c, int l, string escolha){
    Jogo->PromovePeao(peca, c, l, escolha);
}

// Executa o movimento no tabuleiro
bool Tab::Move(Peca * peca, int c, int l){
    int x = peca->getColuna() - 1; int y = peca->getLinha() - 1;
    Peca * v = Jogo->getPeca(c, l);
    if(peca->getNome()[1] == 'K' && (peca->getLinha() == 1 || peca->getLinha() == 8) && abs(c-x) >= 2){
        Jogo->Castle(peca, c, l);
        return true;
    }
    if(v == nullptr && peca->verificadorMove(c+1, l+1) && Jogo->verificaColisoes(peca, c, l)){
        Jogo->Movimento(peca, c, l);
        if(!Jogo->verificaAutoCheck(peca, v, x, y)){
            return true;
        }
    }
    else if(v != nullptr && peca->getNome()[1] != 'P' && peca->verificadorMove(c+1, l+1) && v->getEquipa() != peca->getEquipa() && Jogo->verificaColisoes(peca, c, l)){
        Jogo->Movimento(peca, c, l);
        if(!Jogo->verificaAutoCheck(peca, v, x, y)){
            v->setOrigem(0, 0);
            v->setEscala(0.55, 0.55);
            return true;
        }
    }
    else if(v != nullptr && peca->getNome()[1] == 'P' && peca->verificadorCome(c+1, l+1) && v->getEquipa() != peca->getEquipa()){
        Jogo->Movimento(peca, c, l);
        if(!Jogo->verificaAutoCheck(peca, v, x, y)){
            v->setOrigem(0, 0);
            v->setEscala(0.55, 0.55);
            return true;
        }
    }
    return false;
}



// Faz o trabalho
void Tab::fazOTrabalho(){
    sf::RenderWindow window(sf::VideoMode(lado*12, lado*8), "Xadrez");
    window.setFramerateLimit(120);  //Cria janela "window"

    sf::Color claro(235, 235, 235, 255);  // Cria as cores do tabuleiro
    sf::Color escuro(100, 100, 100, 255);

    int x = 0;  //Def do quadrado branco
    int y = 0;
    sf::RectangleShape rect;
    sf::Vector2f posicao(x, y);
    rect.setPosition(posicao);  // Quadrado branco
    rect.setSize(sf::Vector2f(8*lado, 8*lado));
    rect.setFillColor(claro);

    sf::Font serif;
    serif.loadFromFile("Nonserif.ttf");

    // Interfacede promocao
    sf::RectangleShape quadro; // Criacao do quadro
    quadro.setPosition(920, 540);
    quadro.setSize(sf::Vector2f(360, 300));
    quadro.setFillColor(sf::Color(50, 50, 50, 255));
    quadro.setOutlineThickness(3); quadro.setOutlineColor(sf::Color(180, 180, 180, 255));
    // Texto "Promote"
    sf::Text promote;
    promote.setFont(serif); promote.setString("Promote"); promote.setCharacterSize(40); promote.setPosition(1015, 550); promote.setStyle(sf::Text::Bold);
    // Quadradros de apresentacao
    sf::RectangleShape quadro1; quadro1.setSize(sf::Vector2f(150, 65)); quadro1.setPosition(939, 640); quadro1.setFillColor(sf::Color(80, 80, 80)); quadro1.setOutlineThickness(2); quadro1.setOutlineColor(sf::Color(180, 180, 180));
    sf::RectangleShape quadro2; quadro2.setSize(sf::Vector2f(150, 65)); quadro2.setPosition(939, 740); quadro2.setFillColor(sf::Color(80, 80, 80)); quadro2.setOutlineThickness(2); quadro2.setOutlineColor(sf::Color(180, 180, 180));
    sf::RectangleShape quadro3; quadro3.setSize(sf::Vector2f(150, 65)); quadro3.setPosition(1109, 640); quadro3.setFillColor(sf::Color(80, 80, 80)); quadro3.setOutlineThickness(2); quadro3.setOutlineColor(sf::Color(180, 180, 180));
    sf::RectangleShape quadro4; quadro4.setSize(sf::Vector2f(150, 65)); quadro4.setPosition(1109, 740); quadro4.setFillColor(sf::Color(80, 80, 80)); quadro4.setOutlineThickness(2); quadro4.setOutlineColor(sf::Color(180, 180, 180));
    //Textos das caixas
    sf::Text texto1;
    texto1.setFont(serif); texto1.setString("Queen"); texto1.setCharacterSize(30); texto1.setPosition(967, 651); texto1.setStyle(sf::Text::Bold);
    sf::Text texto2;
    texto2.setFont(serif); texto2.setString("Rook"); texto2.setCharacterSize(30); texto2.setPosition(978, 751); texto2.setStyle(sf::Text::Bold);
    sf::Text texto3;
    texto3.setFont(serif); texto3.setString("Bishop"); texto3.setCharacterSize(30); texto3.setPosition(1138, 650); texto3.setStyle(sf::Text::Bold);
    sf::Text texto4;
    texto4.setFont(serif); texto4.setString("Knight"); texto4.setCharacterSize(30); texto4.setPosition(1139, 750); texto4.setStyle(sf::Text::Bold);

    // Caixa das pecas comidas
    sf::RectangleShape board; board.setPosition(900, 20); board.setSize(sf::Vector2f(400, 250));
    board.setFillColor(sf::Color(60, 60, 60, 255)); board.setOutlineThickness(3); board.setOutlineColor(sf::Color(180, 180, 180, 255));
    //Textos
    sf::Text branco;
    branco.setFont(serif); branco.setString("White Team:"); branco.setCharacterSize(30); branco.setPosition(910, 30); branco.setStyle(sf::Text::Bold);
    sf::Text preto;
    preto.setFont(serif); preto.setString("Black Team:"); preto.setCharacterSize(30); preto.setPosition(910, 140); preto.setStyle(sf::Text::Bold);


    //Valores do primeiro input
    int x_1 = 0;
    int y_1 = 0;
    int a = 99;
    int b = 99;

    //Valores do segundo input
    int x_2 = 0;
    int y_2 = 0;
    int c = 99;
    int d = 99;

    Peca * peca = nullptr;
    Peca * anterior = Jogo->getPeca(7, 7);

    //Quadrado da seleção
    sf::RectangleShape sel;
    sel.setSize(sf::Vector2f(lado, lado));
    sf::Color amarelo(190, 190, 0, 120);
    sel.setFillColor(amarelo);
    sel.setOrigin(55, 55);

    // Coiso que faz mexer
    int a2 = 99;
    int b2 = 99;
    int conta = 1;


    // O que se faz na janela
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
            else if(!peca_move && !promocao && sf::Mouse::isButtonPressed(sf::Mouse::Left) && x_1 == 0 && peca == nullptr){
                x_1 = sf::Mouse::getPosition(window).x;
                y_1 = sf::Mouse::getPosition(window).y;
                a = floor((x_1 - x) / lado);
                b = -(floor((y_1 - y) / lado) - 7);
                peca = getPeca(a, b);
                if(x_1 >= x && x_1 <= x+(8*lado) && y_1 >= y && y_1 <= y+(8*lado) && peca != nullptr && peca->getEquipa() != anterior->getEquipa()){
                }
                else{
                    x_1 = 0;
                    y_1 = 0;
                    a = 99;
                    b = 99;
                    peca = nullptr;
                }
            }
            else if(!peca_move && !promocao && sf::Mouse::isButtonPressed(sf::Mouse::Left) && x_1 != 0){
                x_2 = sf::Mouse::getPosition(window).x;
                y_2 = sf::Mouse::getPosition(window).y;
                c = floor((x_2 - x) / lado);
                d = -(floor((y_2 - y) / lado) - 7);
                if(x_2 >= x && x_2 <= x+(8*lado) && y_2 >= y && y_2 <= y+(8*lado) && (a != c || b != d) && peca != nullptr){
                    if(Move(peca, c, d)){
                        anterior = peca; peca_move= true; peca_movendo = peca; //Mudei aqui coisas da peca_movendo
                        a2 = a; b2 = b;
                    }
                    if(peca->getNome()[1] == 'P' && (peca->getLinha() == 1 || peca->getLinha() == 8)) promocao = true;
                }
                x_1 = 0;
                y_1 = 0;
                a = 99;
                b = 99;
                peca = nullptr;
            }
            if (!peca_move && promocao && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;
                if(x >= 939 && x <= 1089 && y >= 640 && y <= 705) {Jogo->PromovePeao(anterior, anterior->getColuna() - 1, anterior->getLinha() - 1, "Rainha"); promocao = false;}
                if(x >= 939 && x <= 1089 && y >= 740 && y <= 805) {Jogo->PromovePeao(anterior, anterior->getColuna() - 1, anterior->getLinha() - 1, "Torre"); promocao = false;}
                if(x >= 1109 && x <= 1259 && y >= 640 && y <= 705) {Jogo->PromovePeao(anterior, anterior->getColuna() - 1, anterior->getLinha() - 1, "Bispo"); promocao = false;}
                if(x >= 1109 && x <= 1259 && y >= 740 && y <= 805) {Jogo->PromovePeao(anterior, anterior->getColuna() - 1, anterior->getLinha() - 1, "Cavalo"); promocao = false;}

            }
        }
        window.clear(sf::Color(70, 70, 70, 255));
        //Desenha o tabuleiro
        window.draw(rect);
        for(int k=0; k<8; k++){
            sf::RectangleShape quad;
            quad.setSize(sf::Vector2f(lado, lado));
            quad.setFillColor(escuro);
            int Ypos = posicao.y;
            Ypos += k*lado;
            for(int i=0; i<4; i++){
                int Xpos = posicao.x;
                if(k % 2 == 0){
                    Xpos += (2*i+1)*lado;
                    quad.setPosition(Xpos, Ypos);
                    window.draw(quad);
                }
                else if(k % 2 == 1){;
                    Xpos += (2*i)*lado;
                    quad.setPosition(Xpos, Ypos);
                    window.draw(quad);
                }
            }
        }
        // Mostra o quadrado de seleção
        sel.setPosition(CcoordsX(a), LcoordsY(b));
        window.draw(sel);

        //Mostra as peças em campo
        for(int i=0; i<Jogo->getWhite().getPecas().size(); i++){
            Peca *a = Jogo->getWhite().getPecas()[i];
            if(a->getDentro() == true){
                window.draw(a->getSprite());
            }
        }
        for(int i=0; i<Jogo->getBlack().getPecas().size(); i++){
            Peca *a = Jogo->getBlack().getPecas()[i];
            if(a->getDentro() == true){
                window.draw(a->getSprite());
            }
        }
        window.draw(board);
        window.draw(branco);
        window.draw(preto);

        //Movimento das peças mexidas
        if(peca_move){
            sf::Sprite imagem = peca_movendo->getSprite();
            float x = (float)imagem.getPosition().x;
            float y = (float)imagem.getPosition().y;
            float col = (float)(c-a2)*lado/11;
            float lin = (float)(b2-d)*lado/11;
            if(conta < 11){
                conta += 1;
                peca_movendo->CoordssetPosRep(lado, x+col, y+lin);
            }
            else if(conta == 11){
                conta = 1;
                peca_movendo->setPosRep(110, c, d);
                peca_move = false;
                peca_movendo = nullptr;
            }
        }

        // Mostra as peças comidas
        for(int i=0; i<Jogo->getWhite().getPecas().size(); i++){
            Peca * peca = Jogo->getWhite().getPecas()[i];
            if(peca->getDentro() != true){
                peca->CoordssetPosRep(110, 897 + i*23, 175);
                window.draw(peca->getSprite());
            }
        }
        for(int i=0; i<Jogo->getBlack().getPecas().size(); i++){
            Peca * peca = Jogo->getBlack().getPecas()[i];
            if(peca->getDentro() != true){
                peca->CoordssetPosRep(110, 897 + i*23, 65);
                window.draw(peca->getSprite());
            }
        }

        // Mostra o quadro de promoção
        if(promocao){
            window.draw(quadro);
            window.draw(quadro1);
            window.draw(texto1);
            window.draw(quadro2);
            window.draw(texto2);
            window.draw(quadro3);
            window.draw(texto3);
            window.draw(quadro4);
            window.draw(texto4);
            window.draw(promote);
        }
        window.display();
    }
}
