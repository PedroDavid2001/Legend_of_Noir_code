/**********************************************************************************
// Home (Código Fonte) 
// 
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de abertura do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "Level1.h"
#include "Level3.h"
#include "Level4.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

Scene* Home::scene = nullptr;

// ------------------------------------------------------------------------------

void Home::Init()
{
    scene = new Scene();

    // cria objeto mouse
    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    // cria itens de menu
    menu[0] = new Item(window->CenterX(), 550 * GravityGuy::totalScale, 150, START, "Resources/start.png");
    menu[1] = new Item(window->CenterX(), 650 * GravityGuy::totalScale, 105, QUIT, "Resources/quit.png");

    for (int i = 0; i < 2; ++i)
        scene->Add(menu[i], STATIC);

    backg = new Sprite("Resources/background.png");
    title = new Sprite("Resources/title.png");
    
    posB11 = posB12 = window->CenterX();
    posB21 = posB22 = window->CenterX();
    posB31 = posB32 = window->CenterX();

    build_11 = new Sprite("Resources/city.png");
    build_12 = new Sprite("Resources/city.png");
    build_21 = new Sprite("Resources/city2.png");
    build_22 = new Sprite("Resources/city2.png");
    build_31 = new Sprite("Resources/city3.png");
    build_32 = new Sprite("Resources/city3.png");
    
    GravityGuy::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
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
                if (menu[i]->Type() == START) {
                    GravityGuy::audio->Stop(MENU);
                    GravityGuy::NextLevel<Level1>();
                    break;
                }
                else if (menu[i]->Type() == QUIT) 
                    window->Close();
            }
        }
        else
        {
            menu[i]->UnSelect();
        }

        menu[i]->Update();
    }
    
    posB11 -= 200.0f * gameTime;
    posB12 -= 200.0f * gameTime;

    posB21 -= 100.0f * gameTime;
    posB22 -= 100.0f * gameTime;

    posB31 -= 50.0f * gameTime;
    posB32 -= 50.0f * gameTime;

}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    // desenha itens do menu
    scene->Draw();

    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
    title->Draw(window->CenterX(), window->CenterY(), Layer::FRONT, GravityGuy::totalScale);

    float buildWidth = GravityGuy::totalScale * build_11->Width();

    //primeira camada de predios
    build_11->Draw(posB11, window->CenterY(), 0.6f, GravityGuy::totalScale);
    build_12->Draw(posB12 + buildWidth, window->CenterY(), 0.6f, GravityGuy::totalScale);

    //segunda camada de predios
    build_21->Draw(posB21, window->CenterY(), 0.65f, GravityGuy::totalScale);
    build_22->Draw(posB22 + buildWidth, window->CenterY(), 0.65f, GravityGuy::totalScale);

    //terceira camada de predios
    build_31->Draw(posB31, window->CenterY(), 0.7f, GravityGuy::totalScale);
    build_32->Draw(posB32 + buildWidth, window->CenterY(), 0.7f, GravityGuy::totalScale);

    if (posB11 + buildWidth / 2.0f < 0)
        posB11 += buildWidth;

    if (posB12 + buildWidth / 2.0f < 0)
        posB12 += buildWidth;
    else if (posB11 - buildWidth / 2.0f > 0)
        posB12 -= buildWidth;

    if (posB21 + buildWidth / 2.0f < 0)
        posB21 += buildWidth;

    if (posB22 + buildWidth / 2.0f < 0)
        posB22 += buildWidth;
    else if (posB21 - buildWidth / 2.0f > 0)
        posB22 -= buildWidth;

    if (posB31 + buildWidth / 2.0f < 0)
        posB31 += buildWidth;

    if (posB32 + buildWidth / 2.0f < 0)
        posB32 += buildWidth;
    else if (posB31 - buildWidth / 2.0f > 0)
        posB32 -= buildWidth;
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete scene;
    delete backg;
    delete title;
    delete build_11;
    delete build_12;
    delete build_21;
    delete build_22;
    delete build_31;
    delete build_32;
}

// ------------------------------------------------------------------------------