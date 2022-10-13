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
    case FLOOR_2560X300:
        platform = new Sprite("Resources/floor2560x300.png"); type = FLOOR_2560X300;
        break;
    case FLOOR_2560X150:  
        platform = new Sprite("Resources/floor2560x150.png"); type = FLOOR_2560X150; 
        break;
    case FLOOR_1280X300: 
        //o arquivo é plat, mas preferi deixar a constante como FLOOR pelo tamanho da plataforma
        platform = new Sprite("Resources/plat1280x300.png"); type = FLOOR_1280X300; 
        break;
    case PLAT_150X50_FIXED:  
        platform = new Sprite("Resources/plat150x50_fixed.png"); type = PLAT_150X50_FIXED; 
        break;
    case PLAT_150X50_MOBILE_H:  
        platform = new Sprite("Resources/plat150x50_mobile.png"); type = PLAT_150X50_MOBILE_H; 
        break;
    case PLAT_150X50_MOBILE_V:
        platform = new Sprite("Resources/plat150x50_mobile.png"); type = PLAT_150X50_MOBILE_V;
        break;
    case PLAT_200X100:  
        platform = new Sprite("Resources/plat200x100.png"); type = PLAT_200X100; 
        break;
    case PLAT_400X100:  
        platform = new Sprite("Resources/plat400x100.png"); type = PLAT_400X100; 
        break;
    case PLAT_400X150:  
        platform = new Sprite("Resources/plat400x150.png"); type = PLAT_400X150; 
        break;
    case PLAT_400X400: 
        platform = new Sprite("Resources/plat400x400.png"); type = PLAT_400X400; 
        break;
    case PLAT_600X300:  
        platform = new Sprite("Resources/plat600x300.png"); type = PLAT_600X300; 
        break;
    case 11:
        platform = new Sprite("Resources/floor.png"); type = 11;
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
    //esquerda da plataforma (com escala inclusa)
    float platLeft = x - ( platform->Width() / 2.0f );  

    //direita da plataforma (com escala inclusa)
    float platRight = x + ( platform->Width() / 2.0f );
    
    //esquerda da tela
    float windowLeft = window->CenterX() - (window->Width() / 2.0f);                
    
    float playerDist = GravityGuy::player->X() - window->CenterX();

    if (playerDist < 0)
        playerDist = -playerDist;

    //os objetos se movem apenas se o jogador estiver proximo do centro da tela
    if (playerDist <= 10.0f) {
        if (type == 11) {
            
            if ( platRight > window->Width()) {

                GravityGuy::playerRgtVel = 0.0f;//player não se moverá
                
                if (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))
                    Translate(-PLAYER_VELOCITY * gameTime, 0);
            }
            else {
                GravityGuy::playerRgtVel = PLAYER_VELOCITY;
            }

            if ( platLeft < 0 ) {

                GravityGuy::playerLftVel = 0.0f;//player não se moverá

                if (window->KeyDown(VK_LEFT) || window->KeyDown('A'))
                    Translate(PLAYER_VELOCITY * gameTime, 0);
            }
            else {
                GravityGuy::playerLftVel = PLAYER_VELOCITY;
            }
        }
        else if( type != PLAT_150X50_MOBILE_V && type != PLAT_150X50_MOBILE_H) {
            if ( GravityGuy::playerRgtVel == 0.0f && ( window->KeyDown(VK_RIGHT) || window->KeyDown('D') ))
                Translate(-PLAYER_VELOCITY * gameTime, 0);
            if ( GravityGuy::playerRgtVel == 0.0f && ( window->KeyDown(VK_LEFT) || window->KeyDown('A') ))
                Translate(PLAYER_VELOCITY * gameTime, 0);
        }
    }
    else {
        GravityGuy::playerRgtVel = PLAYER_VELOCITY;
        GravityGuy::playerLftVel = PLAYER_VELOCITY;
    }

    if (type == PLAT_150X50_MOBILE_V) {    //plataforma vertical

        float diff = this->Y() - yOrigin;

        if (diff < 0)
            diff = -diff;

        if ( diff >= (100.0f * GravityGuy::totalScale )) //move-se 150px para baixo e para cima
            direcao = -direcao;

        if (GravityGuy::playerRgtVel == 0.0f && (window->KeyDown(VK_RIGHT) || window->KeyDown('D')))
            Translate(-PLAYER_VELOCITY * gameTime, velocity * direcao * gameTime);
        else if (GravityGuy::playerRgtVel == 0.0f && (window->KeyDown(VK_LEFT) || window->KeyDown('A')))
            Translate(PLAYER_VELOCITY * gameTime, velocity * direcao * gameTime);
        else
            Translate(0, velocity * direcao * gameTime);
    }
    else if (type == PLAT_150X50_MOBILE_H) {    //plataforma horizontal

        //ao invés de transladar, a plataforma tem sua origem alterada 
        if (GravityGuy::playerRgtVel == 0.0f && (window->KeyDown(VK_RIGHT) || window->KeyDown('D')))
            xOrigin -= PLAYER_VELOCITY * gameTime;
        else if (GravityGuy::playerRgtVel == 0.0f && (window->KeyDown(VK_LEFT) || window->KeyDown('A')))
            xOrigin += PLAYER_VELOCITY * gameTime;

        float diff = this->X() - xOrigin;

        if (diff < 0)
            diff = -diff;

        if (diff >= ( 100.0f * GravityGuy::totalScale )) //move-se 250px para esquerda e para direita
            direcao = -direcao;

        Translate(PLATFORM_VELOCITY * direcao * gameTime, 0);
    }
}

// -------------------------------------------------------------------------------
