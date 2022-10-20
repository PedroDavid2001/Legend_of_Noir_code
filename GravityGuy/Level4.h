/**********************************************************************************
// Level1 (Arquivo de Cabeçalho)
//
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL4_H_
#define _GRAVITYGUY_LEVEL4_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Font.h"
#include "Timer.h"
#include "Snow.h"
#include "Background.h"
#include "EndLevel.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class Level4 : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    Snow* snow = nullptr;
    Timer           timer;
    Font* playerHp = nullptr;
    EndLevel* endLvl = nullptr;
    stringstream	currentHp;
public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

#endif