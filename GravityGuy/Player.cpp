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

#include "Player.h"
#include "GravityGuy.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/sprite.png", 65, 134, 7, 7);
    anim = new Animation(tileset, 0.120f, true);


    uint stoped[7] = { 0,1,2,3,4,5,6 };

    anim->Add(0, stoped, 7);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    // inicializa estado do player
    gravity = NORMAL;  
    level = 0;

    // posição inicial
    MoveTo(window->CenterX(), 24.0f, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::MIDDLE);
    gravity = NORMAL;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == FINISH)
    {
        // chegou ao final do nível
        level++;
    }
    else
    {
        // mantém personagem em cima da plataforma
        if (gravity == NORMAL)
            MoveTo(window->CenterX(), obj->Y() - 65);
        else
            MoveTo(window->CenterX(), obj->Y() + 65);
    }

    // ----------------------------------------------------------
    // Processa teclas pressionadas
    // ----------------------------------------------------------
    // jogador só pode alterar a gravidade enquanto estiver
    // em cima de uma plataforma, não é possível a mudança no ar
    // ----------------------------------------------------------

    if (window->KeyPress(VK_SPACE))
    {
        gravity = !gravity;

        // toca efeito sonoro
        GravityGuy::audio->Play(TRANSITION);

        // tira player da plataforma para evitar 
        // detecção de colisão no quadro seguinte
        if (gravity == NORMAL)
            Translate(0, 12);
        else
            Translate(0 , -12);
    }
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // ação da gravidade sobre o personagem
    if (gravity == NORMAL)    
        Translate(0, 300 * gameTime);
    else
        Translate(0, -300 * gameTime);

    // atualiza animação
    anim->Select(gravity);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------