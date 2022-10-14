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

Platform::Platform(float posX, float posY, uint plat, Color tint) : color(tint)
{
    type = PLATFORM;
    switch (plat)
    {
    case FLOOR_2560X300:
        platform = new Sprite("Resources/floor2560x300.png"); platType = FLOOR_2560X300;
        break;
    case FLOOR_2560X150:  
        platform = new Sprite("Resources/floor2560x150.png"); platType = FLOOR_2560X150;
        break;
    case FLOOR_1280X300: 
        //o arquivo é plat, mas preferi deixar a constante como FLOOR pelo tamanho da plataforma
        platform = new Sprite("Resources/plat1280x300.png"); platType = FLOOR_1280X300;
        break;
    case PLAT_150X50_FIXED:  
        platform = new Sprite("Resources/plat150x50_fixed.png"); platType = PLAT_150X50_FIXED;
        break;
    case PLAT_150X50_MOBILE_H:  
        platform = new Sprite("Resources/plat150x50_mobile.png"); platType = PLAT_150X50_MOBILE_H;
        break;
    case PLAT_150X50_MOBILE_V:
        platform = new Sprite("Resources/plat150x50_mobile.png"); platType = PLAT_150X50_MOBILE_V;
        break;
    case PLAT_200X100:  
        platform = new Sprite("Resources/plat200x100.png"); platType = PLAT_200X100;
        break;
    case PLAT_400X100:  
        platform = new Sprite("Resources/plat400x100.png"); platType = PLAT_400X100;
        break;
    case PLAT_400X150:  
        platform = new Sprite("Resources/plat400x150.png"); platType = PLAT_400X150;
        break;
    case PLAT_400X400: 
        platform = new Sprite("Resources/plat400x400.png"); platType = PLAT_400X400;
        break;
    case PLAT_600X300:  
        platform = new Sprite("Resources/plat600x300.png"); platType = PLAT_600X300;
        break;
    case 11:
        platform = new Sprite("Resources/floor.png"); platType = 11;
        break;
    }
    
    BBox( new Rect( 
       -1.0f * this->Width() / 2.0f,
       -1.0f * this->Height() / 2.0f,
        this->Width() / 2.0f,
        this->Height() / 2.0f 
    ));

    xOrigin = posX * GravityGuy::totalScale;
    yOrigin = posY * GravityGuy::totalScale;
    velocity = PLATFORM_VELOCITY * altVel(mt);

    MoveTo( posX * GravityGuy::totalScale, posY * GravityGuy::totalScale, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    moving = GravityGuy::player->state;//IDLE = 0

    float playerDist = GravityGuy::player->X() - window->CenterX();

    if (playerDist < 0)
        playerDist = -playerDist;

    //os objetos se movem apenas se o jogador estiver proximo do centro da tela
    if (playerDist <= 2.0f) {
        if ( type == 11) {
            
            if ( this->Right() > window->Width() ) {

                GravityGuy::playerRgtVel = 0.0f;//player não se moverá
                
                if  ( (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) && moving != 0 )
                    Translate(-PLAYER_VELOCITY * gameTime, 0);
            }
            else {
                GravityGuy::playerRgtVel = PLAYER_VELOCITY;
            }

            if ( this->Left() < 0 ) {

                GravityGuy::playerLftVel = 0.0f;//player não se moverá

                if ( (window->KeyDown(VK_LEFT) || window->KeyDown('A')) && moving != 0 )
                    Translate(PLAYER_VELOCITY * gameTime, 0);
            }
            else {
                GravityGuy::playerLftVel = PLAYER_VELOCITY;
            }
        }
		else if (type == PLAT_150X50_MOBILE_V) {    //plataforma vertical

			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))))
				Translate(-PLAYER_VELOCITY * gameTime, 0);
			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))))
				Translate(PLAYER_VELOCITY * gameTime, 0);
			
		}
		else if (type == PLAT_150X50_MOBILE_H) {    //plataforma horizontal

			//ao invés de transladar, a plataforma tem sua origem alterada 
			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))))
				xOrigin -= PLAYER_VELOCITY * gameTime;
			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))))
				xOrigin += PLAYER_VELOCITY * gameTime;

		}
		else {
			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))))
				Translate(-PLAYER_VELOCITY * gameTime, 0);
			if (GravityGuy::playerRgtVel == 0.0f && (moving != 0 && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))))
				Translate(PLAYER_VELOCITY * gameTime, 0);
		}
    }
    else {
        GravityGuy::playerRgtVel = PLAYER_VELOCITY;
        GravityGuy::playerLftVel = PLAYER_VELOCITY;
    }

    if (type == PLAT_150X50_MOBILE_V ) {    //plataforma vertical

        float diff = this->Y() - yOrigin;

        if (diff < 0)
            diff = -diff;

        if ( diff >= (100.0f * GravityGuy::totalScale )) 
            direcao = -direcao;

		Translate(0, velocity * direcao * gameTime);
            
    }
    else if (type == PLAT_150X50_MOBILE_H ) {    //plataforma horizontal

        float diff = this->X() - xOrigin;

        if (diff < 0)
            diff = -diff;

        if (diff >= ( 100.0f * GravityGuy::totalScale )) 
            direcao = -direcao;

        Translate(PLATFORM_VELOCITY * direcao * gameTime, 0);
    }
}

// -------------------------------------------------------------------------------
