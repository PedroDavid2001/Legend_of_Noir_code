/**********************************************************************************
// Level2 (Código Fonte)
//
// Criação:     27 Set 2021
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 2 do jogo
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "BossLVL1.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene* BossLVL1::scene = nullptr;

// ------------------------------------------------------------------------------

void BossLVL1::Init()
{
    GravityGuy::currentLvl = BOSS_1;

    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    Color dark{ 0.4f, 0.4f, 0.4f, 1.0f };
    backg = new Background(dark);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(GravityGuy::player, MOVING);

    // adiciona boss na cena
    boss = new Boss( BANSHEE );
    scene->Add(boss, MOVING);

    // ----------------------
    // piso
    // ----------------------
    Color white{ 1,1,1,1 };
    Platform* plat = new Platform(640.0f, 645.0f, FLOOR_1280X300, white);
    scene->Add(plat, MOVING);

    // ----------------------

    GravityGuy::audio->Frequency(MUSIC, 1.00f);
    GravityGuy::audio->Frequency(TRANSITION, 0.85f);
}

// ------------------------------------------------------------------------------

void BossLVL1::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress('N'))
    {
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<Home>();
        GravityGuy::player->Reset();
    }
    else if ( GravityGuy::player->hp <= 0 )
    {
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<GameOver>();
        GravityGuy::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void BossLVL1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (GravityGuy::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void BossLVL1::Finalize()
{
    scene->Remove(GravityGuy::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
