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

#ifndef _GRAVITYGUY_BULLET_H_
#define _GRAVITYGUY_BULLET_H_

// ------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite* sprite = nullptr;
    bool direction;             //left = false; right = true
    float scale;
public:
    Bullet(bool direction, float scale);
    ~Bullet();
    void Update();
    void Draw();
    float Width();
    float Height();
};
// ------------------------------------------------------------------------------

inline void Bullet::Draw() { sprite->Draw(x, y, z, scale); }

inline float Bullet::Height()
{
    return sprite->Height() * scale;
}

inline float Bullet::Width()
{
    return sprite->Width() * scale;
}

// ------------------------------------------------------------------------------

#endif