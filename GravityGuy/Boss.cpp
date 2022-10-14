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

#include "Boss.h"
#include "Platform.h"
#include "Timer.h"
#include "GravityGuy.h"
#include "Bullet.h"
#include "BossLVL1.h"

// ---------------------------------------------------------------------------------

Boss::Boss(uint boss)
{
	type = BOSS;

	tileSet = new TileSet("Resources/boss_level1.png", 150, 300, 1, 1);
	anim = new Animation(tileSet, 0.120f, true);

	uint idle[1] = { 0 };

	anim->Add(0, idle, 1);

	// cria bounding box
	BBox(new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));
	hp = 100;
	// posição inicial
	MoveTo(window->Width() - (this->Width() / 2.0f), window->Height() - (this->Height() / 2.0f), 0.55f);
}

// ---------------------------------------------------------------------------------

Boss::~Boss()
{
	delete anim;
	delete tileSet;
}

// ---------------------------------------------------------------------------------

void Boss::OnCollision(Object* obj)
{
	if (type == BULLET) {
		hp -= 1;

		//verifica qual o level atual 
		if (GravityGuy::currentLvl == 1 )
			BossLVL1::scene->Delete(obj, MOVING);
	}
}

// ---------------------------------------------------------------------------------

void Boss::Update()
{
	// atualiza animação
	anim->Select(0);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------