/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
//
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Fim do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "NextLevel.h"
#include "GravityGuy.h"
#include "Level1.h"
#include "Home.h"
#include "BossLVL1.h"
#include "Level2.h"
#include "Level4.h"
#include "Level3.h"

// ------------------------------------------------------------------------------

Scene* NextLevel::scene = nullptr;

// ------------------------------------------------------------------------------

void NextLevel::Init()
{
    scene = new Scene();

    // cria objeto mouse
    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    // cria itens de menu
    menu[0] = new Item(window->CenterX(), 600 * GravityGuy::totalScale, 354, CONTINUE, "Resources/next_level.png",100);
    scene->Add(menu[0], STATIC);

    //cria letreiro com o hp do player
    score = new Font("Resources/Digital80.png");
    score->Spacing("Resources/Digital80.dat");

    title = new Sprite("Resources/background.png");
    scoreSpt = new Sprite("Resources/score.png");
}

// ----------------------------------------------------------------------

void NextLevel::Update()
{

    // atualiza objeto mouse
    mouse->Update();

    // Destaca item selecionado
    for (int i = 0; i < 1; ++i)
    {
        if (scene->Collision(mouse, menu[i]))
        {
            menu[i]->Select();

            if (mouse->Clicked())
            {
                if (menu[i]->Type() ==CONTINUE) {
                    
                    if(GravityGuy::currentLvl == LEVEL_1)
                        GravityGuy::NextLevel<Level2>();
                    else if (GravityGuy::currentLvl == LEVEL_2)
                        GravityGuy::NextLevel<Level3>();
                    else if (GravityGuy::currentLvl == LEVEL_3)
                        GravityGuy::NextLevel<Level4>();
                    else if (GravityGuy::currentLvl == LEVEL_4)
                        GravityGuy::NextLevel<BossLVL1>();
                    else if (GravityGuy::currentLvl == BOSS_LEVEL)
                        GravityGuy::NextLevel<Level1>();
                    break;
                }
            }
        }
        else
        {
            menu[i]->UnSelect();
        }

        menu[i]->Update();
    }

}

// ----------------------------------------------------------------------

void NextLevel::Draw()
{
    currentScore.str("");
    currentScore << (int)GravityGuy::player->score;
    score->Draw(window->CenterX() + 150 * GravityGuy::totalScale, window->CenterY() - 50 * GravityGuy::totalScale, currentScore.str(), Color{ 1,1,1,1 }, Layer::FRONT, GravityGuy::totalScale * 2, 0.0f);

    // desenha itens do menu
    scene->Draw();
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
    scoreSpt->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
}

// ----------------------------------------------------------------------

void NextLevel::Finalize()
{
    delete title;
    delete scene;
    delete score;
    delete scoreSpt;
}

// ----------------------------------------------------------------------

