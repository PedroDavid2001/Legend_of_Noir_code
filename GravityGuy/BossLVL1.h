/**********************************************************************************
// Level2 (Arquivo de Cabeçalho)
//
// Criação:     27 Set 2021
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 2 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_BOSSLVL1_H_
#define _GRAVITYGUY_BOSSLVL1_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "Boss.h"

// ------------------------------------------------------------------------------

class BossLVL1 : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    Boss *      boss  = nullptr;
public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

#endif