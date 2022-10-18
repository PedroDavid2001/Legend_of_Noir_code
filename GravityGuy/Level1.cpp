/**********************************************************************************
// Level1 (Código Fonte) 
// 
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "Level1.h"
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

Scene * Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    //setta o level atual na classe principal
    GravityGuy::currentLvl = LEVEL_1;

    // cria gerenciador de cena
    scene = new Scene();

    //cria letreiro com o hp do player
    playerHp = new Font("Resources/Digital80.png");
    playerHp->Spacing("Resources/Digital80.dat");
    
    timer.Start();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(GravityGuy::player, MOVING);

	
	Platform* plat;
	Color white{ 1,1,1,1 };
	
    // ----------------------
    // plataformas
    // ----------------------

    float posX, posY;
    uint  platType;
    ifstream fin;
    fin.open("Level1.txt");
    fin >> posX;

    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, white);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    // ----------------------

    // inicia com música
    GravityGuy::audio->Frequency(MUSIC, 1.0f);
    GravityGuy::audio->Frequency(TRANSITION, 1.0f);
    GravityGuy::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    float start = window->CenterX();
    
    if (GravityGuy::playerPos < start) {
        GravityGuy::playerRgt = true;
        GravityGuy::playerLft = true;
    }else if(GravityGuy::playerPos >= start) {
        GravityGuy::playerRgt = false;
        GravityGuy::playerLft = false;
    }

    if (timer.Elapsed() > 0.2f) {
        snow = new Snow();
        scene->Add(snow, STATIC);
        timer.Reset();
    }

    if (window->KeyPress(VK_ESCAPE))
    {
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<Home>();
        GravityGuy::player->Reset();
    }
    else if ( GravityGuy::player->Top() > window->Height() )
    {
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<GameOver>();
        GravityGuy::player->Reset();
    }
    else if (window->KeyPress('N'))
    {
        GravityGuy::NextLevel<BossLVL1>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }    
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    currentHp.str("");
    currentHp << "Life  " << (int)GravityGuy::player->hp;
    playerHp->Draw(100.0f * GravityGuy::totalScale, 650.0f * GravityGuy::totalScale, currentHp.str(), Color{1,1,1,1}, Layer::FRONT, GravityGuy::totalScale, 0.0f);

    backg->Draw();
    scene->Draw();

    if (GravityGuy::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(GravityGuy::player, MOVING);
    delete scene;
    delete playerHp;
}

// ------------------------------------------------------------------------------
