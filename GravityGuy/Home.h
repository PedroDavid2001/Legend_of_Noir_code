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
#include "Item.h"
#include "Scene.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

enum HomeItens{ START, QUIT };

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

    Item* menu[2] = { 0 };    // itens do menu

    Mouse* mouse = nullptr;         // objeto mouse

public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};

// -----------------------------------------------------------------------------

#endif