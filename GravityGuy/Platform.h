/**********************************************************************************
// Platform (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLATFORM_H_
#define _GRAVITYGUY_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "GravityGuy.h"
#include <random>
using namespace std;

// ---------------------------------------------------------------------------------

enum PLATTYPES { 
    FLOOR_2560X150,
    FLOOR_2560X300,
    PLAT_150X50_FIXED, 
    PLAT_150X50_MOBILE_H,                               //move horizontalmente
    PLAT_150X50_MOBILE_V,                               //move verticalmente
    PLAT_200X100, 
    FLOOR_1280X300, 
    PLAT_400X100, 
    PLAT_600X300, 
    PLAT_400X150, 
    PLAT_400X400,
	SIGN
};

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma
    float xOrigin, yOrigin;                 // posições de origem das plataformas móveis (são alteradas quando o player se move)
    float velocity;                         //velocidade alterada da plataforma para diferenciar o movimento
    random_device rd;
    mt19937 mt{ rd() };

    uniform_real_distribution<float> altVel {1.0f, 1.5f}; //alterador da velocidade da plataforma

public:
    float direcao = 1.0f;                   //direção do movimento (inverte quando a plataforma alcança um limite)
    uint platType;

    Platform(float posX, float posY, 
             uint plat, 
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
    float Height();
    float Width();
    float Bottom();
    float Top();
    float Left();
    float Right();
}; 

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Platform::Draw()
{ platform->Draw(x, y, Layer::MIDDLE, GravityGuy::totalScale, 0.0f, color); }

inline float Platform::Height() 
{
    return platform->Height() * GravityGuy::totalScale;
}

inline float Platform::Width()
{
    return platform->Width() * GravityGuy::totalScale;
}

inline float Platform::Bottom()
{
    return y + (this->Height() / 2.0f );
}

inline float Platform::Top()
{
    return y - (this->Height() / 2.0f );
}

inline float Platform::Right()
{
    return x + ( this->Width() / 2.0f );
}

inline float Platform::Left()
{
    return x - ( this->Width() / 2.0f );
}

// ---------------------------------------------------------------------------------

#endif