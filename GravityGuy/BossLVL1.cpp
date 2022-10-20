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
#include "Level1.h"
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
    //player se mexe normalmente na tela de boss
    GravityGuy::playerRgt = true;
    GravityGuy::playerLft = true;

    GravityGuy::currentLvl = BOSS_LEVEL;

    // cria gerenciador de cena
    scene = new Scene();

	//cria letreiro com o hp do boss
	bossHP = new Font("Resources/Digital80.png");
	bossHP->Spacing("Resources/Digital80.dat");

	//cria letreiro com o hp do player
	playerHp = new Font("Resources/Digital80.png");
	playerHp->Spacing("Resources/Digital80.dat");

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
    Platform* plat = new Platform(640.0f, 770.0f, FLOOR_1280X300, white);
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
        GravityGuy::NextLevel<Home>();   // trocar aqui pelas outras fases
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
	currentBossHP.str("");
	currentBossHP << "BOSS HP " << boss->hp;
	bossHP->Draw(1000.0f * GravityGuy::totalScale, 50.0f * GravityGuy::totalScale, currentBossHP.str(), Color{ 1,1,1,1 }, Layer::FRONT, (GravityGuy::totalScale / 2.0f), 0.0f);
    
	currentHp.str("");
	currentHp << "Life  " << (int)GravityGuy::player->hp;
	playerHp->Draw(100.0f * GravityGuy::totalScale, 650.0f * GravityGuy::totalScale, currentHp.str(), Color{ 1,1,1,1 }, Layer::FRONT, GravityGuy::totalScale, 0.0f);
	
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
	delete bossHP;
}

// ------------------------------------------------------------------------------
