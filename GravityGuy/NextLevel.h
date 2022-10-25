/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
//
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Fim do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_NEXTLEVEL_H_
#define _GRAVITYGUY_NEXTLEVEL_H_

// ------------------------------------------------------------------------------

enum NextLevelItens { CONTINUE };

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "GravityGuy.h"
#include "Item.h"
#include "Font.h"
#include "Scene.h"
#include "TileSet.h"
#include "Mouse.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class NextLevel : public Game
{
private:

    Sprite* title = nullptr;       // tela de fim
    Sprite* scoreSpt = nullptr;       // tela de fim
    Item* menu[1] = { 0 };    // itens do menu
    Mouse* mouse = nullptr;         // objeto mouse
    Font* score = nullptr;
    stringstream	currentScore;

public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // lógica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finalização do nível
};

// ------------------------------------------------------------------------------

#endif