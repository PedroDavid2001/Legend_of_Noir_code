/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     20 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Bullet.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

Bullet::Bullet(bool direction, float scale)
{
    type = BULLET;
    this->scale = scale;
    this->direction = direction;

    sprite = new Sprite("Resources/bullet.png");

    BBox(new Rect(
        -1.0f * this->Width() / 2.0f,
        -1.0f * this->Height() / 2.0f,
        this->Width() / 2.0f,
        this->Height() / 2.0f
    ));
    
    if(direction)
        MoveTo(GravityGuy::player->Right(), GravityGuy::player->Y(), Layer::FRONT);
    else
        MoveTo(GravityGuy::player->Left(), GravityGuy::player->Y(), Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Bullet::~Bullet()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Bullet::Update()
{
    if(direction)
        Translate(600.0f * gameTime, 0);
    else
        Translate(-600.0f * gameTime, 0);

    //deleta quando sair da tela
    if (x < 0 || x > window->Width())
        Level1::scene->Delete(this, MOVING);
}