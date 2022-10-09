/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case SMALL:  platform = new Sprite("Resources/SmallGray.png"); type = SMALL; break;
    case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); type = MEDIUM; break;
    case LARGE:  platform = new Sprite("Resources/LongGray.png"); type = LARGE; break;
    case CHECKPOINT: platform = new Sprite("Resources/Finish.png"); type = CHECKPOINT; break;
	case FLOOR: platform = new Sprite("Resources/floor.png"); type = FLOOR; break;//sprite do chão
    }
    
    BBox(new Rect(( - platform->Width() / 2.0f) * GravityGuy::totalScale,
                    ( -platform->Height()/2.0f) * GravityGuy::totalScale,
                      ( platform->Width()/2.0f) * GravityGuy::totalScale,
                     ( platform->Height()/2.0f) * GravityGuy::totalScale ));
	
    MoveTo(( posX + ( platform->Width() / 2.0f )), posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    //esquerda da plataforma (com escala inclusa)
    float platLeft = x - (( platform->Width() * GravityGuy::totalScale ) / 2.0f );  

    //direita da plataforma (com escala inclusa)
    float platRight = x + ((platform->Width() * GravityGuy::totalScale) / 2.0f);
    
    //esquerda da tela
    float windowLeft = window->CenterX() - (window->Width() / 2.0f);                
    
    float playerDist = GravityGuy::player->X() - window->CenterX();

    if (playerDist < 0)
        playerDist = -playerDist;

    //os objetos se movem apenas se o jogador estiver proximo do centro da tela
    if (playerDist <= 2.0f) {
        if (type == FLOOR) {
            
            if ( platRight > window->Width()) {

                GravityGuy::playerRgtVel = 0.0f;//player não se moverá
                
                if (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))
                    Translate(-500.0f * gameTime, 0);
            }
            else {
                GravityGuy::playerRgtVel = 200.0f;
            }

            if ( platLeft < 0 ) {

                GravityGuy::playerLftVel = 0.0f;//player não se moverá

                if (window->KeyDown(VK_LEFT) || window->KeyDown('A'))
                    Translate(500.0f * gameTime, 0);
            }
            else {
                GravityGuy::playerLftVel = 200.0f;
            }
        }
        else {
            if ( GravityGuy::playerRgtVel == 0.0f && ( window->KeyDown(VK_RIGHT) || window->KeyDown('D') ))
                Translate(-500.0f * gameTime, 0);
            if ( GravityGuy::playerRgtVel == 0.0f && ( window->KeyDown(VK_LEFT) || window->KeyDown('A') ))
                Translate(500.0f * gameTime, 0);
        }
    }
    else {
        GravityGuy::playerRgtVel = 200.0f;
        GravityGuy::playerLftVel = 200.0f;
    }
	
}

// -------------------------------------------------------------------------------
