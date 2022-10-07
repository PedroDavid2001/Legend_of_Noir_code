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

#ifndef _GRAVITYGUY_SNOW_H_
#define _GRAVITYGUY_SNOW_H_

// ------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;

// ------------------------------------------------------------------------------

class Snow : public Object
{
private:
    Sprite* snow = nullptr;      
    random_device rd;
    mt19937 mt{ rd() };

    uniform_real_distribution<float> posYInit{ 20.0f, 50.0f };
    uniform_real_distribution<float> posX{ 50.0f, window->Width() + 50.0f};
public:
    Snow();
    ~Snow();
    void Update();                  
    void Draw();                   
};
// ------------------------------------------------------------------------------
inline void Snow::Draw() { snow->Draw(x, y, z); }
// ------------------------------------------------------------------------------

#endif