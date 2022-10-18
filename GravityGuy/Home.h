/**********************************************************************************
// Home (Arquivo de Cabeçalho)
// 
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de abertura do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_HOME_H_
#define _GRAVITYGUY_HOME_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite*  title = nullptr;

    float posB11, posB12;							//posição horizontal dos primeiros predios
    float posB21, posB22;							//posição horizontal dos predios do meio
    float posB31, posB32;							//posição horizontal dos predios de tras

    Sprite* build_11; //predios mais proximos
    Sprite* build_12;

    Sprite* build_21; //predios do meio
    Sprite* build_22;

    Sprite* build_31; //predios mais distantes
    Sprite* build_32;

    TileSet * tileset = nullptr;    // tileset da animação
    Animation * anim = nullptr;     // animação do menu

public:
    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};

// -----------------------------------------------------------------------------

#endif