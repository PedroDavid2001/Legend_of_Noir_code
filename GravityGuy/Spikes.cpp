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
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

// ---------------------------------------------------------------------------------

Spikes::Spikes(bool direction, float xx, float yy, uint spykeType)
{
    this->spykeType = spykeType;
    this->direction = direction;
    touched = false;
    grow = false;

    if (spykeType == GROUND) {
        type = SPIKE;
        tileset = new TileSet("Resources/spike.png", 150, 60, 2, 28);
        anim = new Animation(tileset, 0.06f, true);

        uint normal[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        uint inv[14] = { 15, 14, 17, 16, 19, 18, 21, 20, 23, 22, 25, 24, 27, 26 };

        anim->Add(0, inv, 14);
        anim->Add(1, normal, 14);

        BBox(new Rect(
            -1.0f * this->Width() / 3.0f,
            -1.0f * this->Height() / 4.0f,
            this->Width() / 4.0f,
            this->Height() / 2.0f
        ));
    }
    if(spykeType == FLOWER) {
        tileset = new TileSet("Resources/flower.png", 80, 300, 39, 39);
        anim = new Animation(tileset, 0.06f, false);
        
        BBox(new Rect(
            -1.0f * this->Width() / 2.0f,
            -1.0f * this->Height() / 2.0f,
            this->Width() / 2.0f,
            this->Height() / 2.0f
        ));

        growTimer.Start();
    }
    
    MoveTo(xx, yy * GravityGuy::totalScale, Layer::FRONT);
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
    if (spykeType == GROUND) {
        Translate(-300.0f * gameTime, 0);

        if ((x + (this->Width() / 2.0f) < 0) || (x - (this->Width() / 2.0f) > window->Width()))
            BossLVL1::scene->Delete();

        anim->Select((uint)(!direction));
    }
    if (spykeType == FLOWER) {
        if (anim->Frame() >= 20) {
            type = SPIKE;
        }
        if (growTimer.Elapsed(3.5f)) {
            if (GravityGuy::currentLvl == LEVEL_1)
                Level1::scene->Delete();
            else if (GravityGuy::currentLvl == LEVEL_2)
                Level2::scene->Delete();
            else if (GravityGuy::currentLvl == LEVEL_3)
                Level3::scene->Delete();
            else if (GravityGuy::currentLvl == LEVEL_4)
                Level4::scene->Delete();
            else if (GravityGuy::currentLvl == BOSS_LEVEL)
                BossLVL1::scene->Delete();
        }
    }
    
    anim->NextFrame();
}