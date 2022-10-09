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

// ----------------------------------------------------------------------

void GameOver::Init()
{
    title = new Sprite("Resources/GameOver.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
	//espaço para definir se o jogador que sair do level ou voltar para o ultimo checkpoint
    if (window->KeyPress(VK_RETURN))
        GravityGuy::NextLevel<Level1>();
	else if(window->KeyPress(VK_ESCAPE))
		GravityGuy::NextLevel<Home>();

}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK, GravityGuy::totalScale);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
}

// ----------------------------------------------------------------------

