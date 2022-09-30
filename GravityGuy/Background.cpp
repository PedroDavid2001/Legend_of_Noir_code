/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background(Color tint) : color(tint)
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    posC1 = posC2 = x;//inicializa a posição inicial

    // carrega nuvens
    clouds1 = new Sprite("Resources/clouds.png");
    clouds2 = new Sprite("Resources/clouds.png");

    // cria sprites do plano de fundo
    sky     = new Sprite("Resources/background.png");    
   
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete clouds1;
    delete clouds2;
    delete sky;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
    if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
        // move as nuvens quando estiver andando
        posC1 -= 100 * gameTime;
        posC2 -= 100 * gameTime;
    }
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha pano de fundo
    sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, color);

    clouds1->Draw(posC1, y, Layer::LOWER, 1.0f, 0.0f, color); //primeira leva de nuvens
    clouds2->Draw(posC2 + clouds1->Width(), y, Layer::LOWER, 1.0f, 0.0f, color); //segunda leva de nuvens
    
    // traz pano de fundo de volta para dentro da tela
    if (posC1 + clouds1->Width()/2.0f < 0)
        posC1 += clouds1->Width();

    if (posC2 + clouds2->Width() / 2.0f < 0)
        posC2 += clouds2->Width();

}

// -------------------------------------------------------------------------------
