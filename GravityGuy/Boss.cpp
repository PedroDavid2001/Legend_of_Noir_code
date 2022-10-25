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
	state = IDLE_B_INV;
	spikesUsed = false;

	switch (boss) {
	case BANSHEE:
		
		tileSet = new TileSet("Resources/boss_level1.png", 200, 400, 5, 20);
		anim = new Animation(tileSet, 0.120f, true);

		uint idleInv[5] = { 0, 1, 2, 3, 4 };
		uint idle[5] = { 9, 8, 7, 6, 5 };
		
		anim->Add(IDLE_B, idle, 5);
		anim->Add(IDLE_B_INV, idleInv, 5);

		// cria bounding box
		BBox(new Rect(
			-1.0f * this->Width() / 2.0f,
			-1.0f * this->Height() / 2.0f,
			this->Width() / 2.0f,
			this->Height() / 2.0f
		));
		hp = 100;
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
	state = direction ? IDLE_B : IDLE_B_INV;

	if (atkTimer.Elapsed(2.0f) && !spikesUsed) {
		Spikes* spk = new Spikes(direction, this->X(), 590.0f, GROUND);
		BossLVL1::scene->Add(spk, MOVING);
		spikesUsed = true;
	}
	else if (atkTimer.Elapsed(6.5f)) {
		Spikes* spk = new Spikes(direction, 600.0f, 490.0f, FLOWER);
		BossLVL1::scene->Add(spk, MOVING);

		spk = new Spikes(direction, 100.0f, 490.0f, FLOWER);
		BossLVL1::scene->Add(spk, MOVING);

		spk = new Spikes(direction, 1100.0f, 490.0f, FLOWER);
		BossLVL1::scene->Add(spk, MOVING);

		spikesUsed = false;
		atkTimer.Reset();
	}

	// atualiza animação
	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------