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
#include "Spikes.h"

// ---------------------------------------------------------------------------------

Boss::Boss(uint boss)
{
	type = BOSS;
	this->boss = boss;
	atkTimer.Start();

	switch (boss) {
	case BANSHEE:
		
		tileSet = new TileSet("Resources/boss_level1.png", 200, 400, 3, 5);
		anim = new Animation(tileSet, 0.120f, true);

		uint idle[5] = { 0, 1, 2, 3, 4 };

		anim->Add(0, idle, 5);

		// cria bounding box
		BBox(new Rect(
			-1.0f * this->Width() / 2.0f,
			-1.0f * this->Height() / 2.0f,
			this->Width() / 2.0f,
			this->Height() / 2.0f
		));
		hp = 200;
		direction = false;
		// posição inicial da banshee
		MoveTo(window->Width() - (this->Width() / 2.0f), ( 420.0f * GravityGuy::totalScale ), 0.55f);
		
		break;
	}
	
}

// ---------------------------------------------------------------------------------

Boss::~Boss()
{
	delete anim;
	delete tileSet;
}

// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------

void Boss::Update()
{
	if (atkTimer.Elapsed() > 3.0f) {
		Spikes* spk = new Spikes(direction, this->X());
		BossLVL1::scene->Add(spk, MOVING);
		atkTimer.Reset();
		atkTimer.Start();
	}

	// atualiza animação
	anim->Select(0);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------