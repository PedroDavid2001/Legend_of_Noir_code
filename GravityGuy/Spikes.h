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

#ifndef _GRAVITYGUY_SPIKES_H_
#define _GRAVITYGUY_SPIKES_H_

// ------------------------------------------------------------------------------

#include "Object.h"
#include "Animation.h"                  // animação de sprites
#include "TileSet.h"
#include "GravityGuy.h"
#include "Timer.h"

// ------------------------------------------------------------------------------

enum SpikeType {
    GROUND,
    FLOWER
};

// ------------------------------------------------------------------------------

class Spikes : public Object
{
private:
    TileSet* tileset;
    Timer growTimer;
    Animation* anim;
    bool direction;             //left = false; right = true
public:
    uint spykeType;
    bool touched;               //indica se encostou no player
    bool grow;
    Spikes(bool direction, float xx, float yy, uint spykeType);
    ~Spikes();
    void Update();
    void Draw();
    float Width();
    float Height();
};
// ------------------------------------------------------------------------------

inline void Spikes::Draw() { anim->Draw(x, y, z, GravityGuy::totalScale); }

inline float Spikes::Height()
{
    return tileset->TileHeight() * GravityGuy::totalScale;
}

inline float Spikes::Width()
{
    return tileset->TileWidth() * GravityGuy::totalScale;
}

// ------------------------------------------------------------------------------

#endif