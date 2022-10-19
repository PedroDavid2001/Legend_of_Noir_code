/**********************************************************************************
// Platform (Código Fonte)
//
// Criação:     21 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Enemies.h"

// ---------------------------------------------------------------------------------

Enemies::Enemies(float posX, float posY, uint enem, Color tint) : color(tint)
{

	uint idle[5] = { 0, 1, 2, 3, 4 };
	uint idleInv[5] = { 9, 10, 11, 12, 13 };

	

	switch (enem)
	{

	case ENEMY:
		tileSet = new TileSet("Resources/enemy.png", 70, 80, 5, 5);
		anim = new Animation(tileSet, 0.120f, true);

		anim->Add(IDLE_I, idle, 5);
		anim->Add(IDLE_INV_I, idleInv, 5);

		break;

	case ENEMY_FLY:
		tileSet = new TileSet("Resources/Fly Enemy.png", 80, 40, 6, 6);
		anim = new Animation(tileSet, 0.120f, true);

		break;
	}

	BBox(new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));

	state = IDLE_I;
	xOrigin = posX * GravityGuy::totalScale;
	yOrigin = posY * GravityGuy::totalScale;
	velocity = 80.0f * altVel(mt);

	MoveTo(posX * GravityGuy::totalScale, posY * GravityGuy::totalScale, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Enemies::~Enemies()
{
	delete anim;
	delete tileSet;
}

// -------------------------------------------------------------------------------

void Enemies::Update()
{


	if (enemyType == ENEMY) {

		//além invés de transladar, a plataforma tem sua origem alterada 
		if (!GravityGuy::playerRgt)
			xOrigin += GravityGuy::platform_velocity * gameTime;
		if (!GravityGuy::playerLft)
			xOrigin += GravityGuy::platform_velocity * gameTime;
	}


	if (!GravityGuy::playerRgt)
		Translate(GravityGuy::platform_velocity * gameTime, 0);
	if (!GravityGuy::playerLft)
		Translate(GravityGuy::platform_velocity * gameTime, 0);


	if (enemyType == ENEMY) {    

		float diff = x - xOrigin;

		if (diff < 0) {
			diff = -diff;
		}

		if (diff >= (150.0f * GravityGuy::totalScale)) {
			direcao = -direcao;
			state = state == IDLE_I ? IDLE_INV_I : IDLE_I;

		}

		Translate(100.0f * direcao * gameTime, 0);
	}
	else if (enemyType == ENEMY_FLY) {

		

		

		Translate(100.0f * direcao * gameTime, 0);
	}

	anim->Select(state);
	anim->NextFrame();
}

// -------------------------------------------------------------------------------
