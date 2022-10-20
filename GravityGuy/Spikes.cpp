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

#include "Spikes.h"
#include "BossLVL1.h"

// ---------------------------------------------------------------------------------

Spikes::Spikes(bool direction, float xx)
{
    type = SPIKE;
    this->direction = direction;
    touched = false;

    tileset = new TileSet("Resources/spike.png", 100, 40, 2, 28);
    anim = new Animation(tileset, 0.06f, true);

    uint normal[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    uint inv[14] = { 15, 14, 17, 16, 19, 18, 21, 20, 23, 22, 25, 24, 27, 26 };

    anim->Add( 0, inv, 14);
    anim->Add( 1, normal, 14);

    BBox(new Rect(
        -1.0f * this->Width() / 2.0f,
        -1.0f * this->Height() / 2.5f,
        this->Width() / 3.5f,
        this->Height() / 2.0f
    ));

    MoveTo(xx, 600.0f * GravityGuy::totalScale, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Spikes::~Spikes()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Spikes::Update()
{
    /*if (direction)
        Translate(500.0f * gameTime, 0);
    else*/
        Translate(-300.0f * gameTime, 0);

    if(( x + (this->Width() / 2.0f) < 0 ) || ( x - (this->Width() / 2.0f ) > window->Width() ))
        BossLVL1::scene->Delete(this, MOVING);

    anim->Select( (uint)(!direction));
    anim->NextFrame();
}