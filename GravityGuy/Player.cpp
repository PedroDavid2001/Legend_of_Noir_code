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

#include "Player.h"
#include "Platform.h"
#include "Timer.h"
#include "GravityGuy.h"
#include "Level1.h"
#include "BossLVL1.h"
#include "Bullet.h"
#define PLAYER_VELOCITY	400.0f

// ---------------------------------------------------------------------------------

Player::Player(float scale)
{
	this->scale = scale;
	type = PLAYER;
	hp = 4;
    tileset = new TileSet("Resources/player.png", 70, 70, 9, 36);
    anim = new Animation(tileset, 0.16f, true);
	
	uint idle[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	uint idleInv[9] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	uint run[8] = { 18, 19, 20, 21, 22, 23, 24, 25 };
	uint runInv[8] = { 28, 29, 30, 31, 32, 33, 34, 35 };
	
	anim->Add(MOVE, run, 8);
	anim->Add(IDLE, idle, 9);
	anim->Add(MOVE_INV, runInv, 8);
	anim->Add(IDLE_INV, idleInv, 9);
	anim->Add(ATACK, idle, 9);
	anim->Add(JUMP, idle, 9);

    // cria bounding box
    BBox( new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));
    
    // inicializa estado do player
	state = IDLE;
	gravity = 0.0f;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	shootTimer.Start();

    // posição inicial
    MoveTo( 200.0f * scale, ( 560.0f * scale ) - ( this->Height() / 2.0f ), Layer::MIDDLE);

	//starta a posição inicial no arquivo main
	GravityGuy::playerPos = this->X();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial 
	MoveTo( 200.0f * scale, (560.0f * scale) - (this->Height() / 2.0f), Layer::MIDDLE);
	state = IDLE;
	gravity = 0.0f;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	shootTimer.Start();

	//restarta a posição inicial no arquivo main
	GravityGuy::playerPos = this->X();
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	if (obj->type == PLATFORM) {
		Platform* plat = (Platform*)obj;

		float lftDiff = this->Right() - plat->Left();
		float rgtDiff = this->Left() - plat->Right();
		
		if (rgtDiff < 0)
			rgtDiff = -rgtDiff;

		if (lftDiff < 0)
			lftDiff = -lftDiff;
		
		//down (dentro das extremidades)
		if (this->Bottom() >= plat->Top() && this->Left() >= plat->Left() && this->Right() <= plat->Right()) {
			if (state != JUMP) {
				MoveTo(x, (plat->Top() - (this->Height() / 2.0f)));
				canJump = true;
			}

			if (plat->platType == PLAT_150X50_MOBILE_H && (state == IDLE || state == IDLE_INV))
				Translate(100.0f * plat->direcao * gameTime, 0);
		}
		//down (além das extremidades)
		else if (this->Y() <= plat->Top() && this->Bottom() <= plat->Y()) {
			if (state != JUMP) {
				gravity = 0.0f;
				MoveTo(x, (plat->Top() - (this->Height() / 2.0f)));
				canJump = true;
			}
			if (plat->platType == PLAT_150X50_MOBILE_H && (state == IDLE || state == IDLE_INV))
				Translate(100.0f * plat->direcao * gameTime, 0);
		}
		//right
		else if (this->Right() >= plat->Left() && this->Left() < plat->Left()) {
			if (state != JUMP)
				MoveTo((plat->Left() - this->Width() / 2.0f), y);
			
			right = false;
		}
		//left
		else if (this->Left() <= plat->Right() && this->Right() > plat->Right()) {
			if (state != JUMP)
				MoveTo((plat->Right() + this->Width() / 2.0f), y);
			
			left = false;
		}
		
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	//controla o delay dos diferentes estados 
	if (state == IDLE || state == IDLE_INV)
		anim->Delay(0.16f);
	else if (state == MOVE || state == MOVE_INV)
		anim->Delay(0.08f);
	
	//impede de sair da tela
	if (this->Left() <= 0) {
		left = false;
	}
	if (this->Right() >= window->Width()) {
		right = false;
	}

	// ------------------------------------------------------------------------
	// detecção de movimento
	// ------------------------------------------------------------------------
	
	if ((window->KeyDown(VK_RIGHT) || window->KeyDown('D')) && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {
		//parado
		if (state != JUMP) {
			if (direction)
				state = IDLE;
			else
				state = IDLE_INV;
		}

		GravityGuy::platform_velocity = 0;
	}
	else if (right && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))) {
		
		if (state != JUMP)
			state = MOVE;
		direction = true;

		if (GravityGuy::playerRgt)
			Translate(PLAYER_VELOCITY * gameTime, 0);
		else {
			GravityGuy::platform_velocity = -200.0f * GravityGuy::totalScale;			
		}

		GravityGuy::playerPos += 200.0f * GravityGuy::totalScale * gameTime;//atualiza a posição relativa do player

	}
	else if (left && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {
		
		if (state != JUMP)
			state = MOVE_INV;
		direction = false;
		
		if (GravityGuy::playerLft)
			Translate(-PLAYER_VELOCITY * gameTime, 0);
		else {
			GravityGuy::platform_velocity = 200.0f * GravityGuy::totalScale;
		}

		GravityGuy::playerPos -= 200.0f * GravityGuy::totalScale * gameTime;//atualiza a posição relativa do player
	}
	else {
		//parado
		if (state != JUMP) {
			if(direction)
				state = IDLE;
			else
				state = IDLE_INV;
		}
			
		GravityGuy::platform_velocity = 0;
	}
	
	// ------------------------------------------------------------------------
	// detecção de pulo
	// ------------------------------------------------------------------------
	
	if (state != JUMP) {

		//independente do estado, se o jogador apertar espaço, o boneco deve pular!!
		if (window->KeyPress(VK_SPACE) && canJump) {
			canJump = false;
			//setta estado do player
			state = JUMP;									
			jumpForce = 600.0f * this->scale;
			
			//inicia timer do pulo
			jumpTimer.Start();								
		}
	}
	else if (state == JUMP && jumpTimer.Elapsed() < 0.4f) {	
		Translate(0, -jumpForce * gameTime);
	
		//força do pulo vai decaindo a cada iteração
		jumpForce -= 300.0f * this->scale * gameTime;

	}
	else if (state == JUMP && jumpTimer.Elapsed(0.4f)) {
		//finalizou o pulo
		if (direction)
			state = IDLE;
		else
			state = IDLE_INV;

		jumpTimer.Stop();
		jumpTimer.Reset();
	}
	
	// ------------------------------------------------------------------------
	// detecção de disparo
	// ------------------------------------------------------------------------

	if ((window->KeyPress('Z') || window->KeyPress('K')) && state != ATACK) {
		
		if (state != JUMP)
			state = ATACK;
		
		shootTimer.Start();

		Bullet* bullet = nullptr;

		if (direction)
			bullet = new Bullet(true, scale);
		else
			bullet = new Bullet(false, scale);

		//verifica qual o level atual para decidir qual irá receber o objeto bullet
		if (GravityGuy::currentLvl == LEVEL_1 && bullet != nullptr)
			Level1::scene->Add(bullet, MOVING);
		else if (GravityGuy::currentLvl == BOSS_1 && bullet != nullptr)
			BossLVL1::scene->Add(bullet, MOVING);
	}

    if(state != JUMP )
		// ação da gravidade sobre o personagem 
		Translate(0, gravity * scale * gameTime);

	right = true;
	left = true;
	gravity = 500.0f;

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------