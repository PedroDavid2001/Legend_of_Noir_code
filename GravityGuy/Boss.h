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

#ifndef _GRAVITYGUY_BOSS_H_
#define _GRAVITYGUY_BOSS_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "TileSet.h"                                     // desenho de sprites
#include "Animation.h"
#include "GravityGuy.h"

// ---------------------------------------------------------------------------------

enum Bosses {
    BANSHEE     //nome do boss
};

// ---------------------------------------------------------------------------------

class Boss : public Object
{
private:
    TileSet* tileSet = nullptr;             // sprite da plataforma
    Animation* anim = nullptr;
    uint hp;
public:
    uint boss;                              //armazena o boss atual
    Boss( uint boss );                      // construtor    
    ~Boss();                                 // destrutor

    void Update();                          // atualização do objeto
    void OnCollision(Object* obj);
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

inline void Boss::Draw()
{
    anim->Draw(x, y, z, GravityGuy::totalScale);
}

inline float Boss::Height()
{
    return tileSet->TileHeight() * GravityGuy::totalScale;
}

inline float Boss::Width()
{
    return tileSet->TileWidth() * GravityGuy::totalScale;
}

inline float Boss::Bottom()
{
    return y + (this->Height() / 2.0f);
}

inline float Boss::Top()
{
    return y - (this->Height() / 2.0f);
}

inline float Boss::Right()
{
    return x + (this->Width() / 2.0f);
}

inline float Boss::Left()
{
    return x - (this->Width() / 2.0f);
}

// ---------------------------------------------------------------------------------

#endif