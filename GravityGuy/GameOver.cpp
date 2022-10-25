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
#include "GameOver.h"
#include "GravityGuy.h"
#include "Level1.h"
#include "Home.h"

// ------------------------------------------------------------------------------

Scene* GameOver::scene = nullptr;

// ------------------------------------------------------------------------------

void GameOver::Init()
{
    scene = new Scene();
    // cria objeto mouse
    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    // cria itens de menu
    menu[0] = new Item(window->CenterX(), 500 * GravityGuy::totalScale, 350, TRYAGAIN, "Resources/try_again.png", 125.0f);
    menu[1] = new Item(window->CenterX(), 600 * GravityGuy::totalScale, 105, BACKMENU, "Resources/quit.png");

    //cria letreiro com o hp do player
    score = new Font("Resources/Digital80.png");
    score->Spacing("Resources/Digital80.dat");

    for (int i = 0; i < 2; ++i)
        scene->Add(menu[i], STATIC);

    title = new Sprite("Resources/background.png");
    scoreSpt = new Sprite("Resources/score.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
    
    // atualiza objeto mouse
    mouse->Update();

    // Destaca item selecionado
    for (int i = 0; i < 2; ++i)
    {
        if (scene->Collision(mouse, menu[i]))
        {
            menu[i]->Select();

            if (mouse->Clicked())
            {
                if (menu[i]->Type() == TRYAGAIN) {
                    GravityGuy::player->hp = 4;
                    GravityGuy::player->score = 0;

                    GravityGuy::NextLevel<Level1>();
                    break;
                }
                else if (menu[i]->Type() == BACKMENU) {
                    GravityGuy::NextLevel<Home>();
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

void GameOver::Draw()
{
    currentScore.str("");
    currentScore << (int)GravityGuy::player->score;
    score->Draw(window->CenterX() + 150 * GravityGuy::totalScale, window->CenterY() - 50 * GravityGuy::totalScale, currentScore.str(), Color{1,1,1,1}, Layer::FRONT, GravityGuy::totalScale * 2, 0.0f);

    // desenha itens do menu
    scene->Draw();
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
    scoreSpt->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
    delete scene;
    delete score;
    delete scoreSpt;
}

// ----------------------------------------------------------------------

