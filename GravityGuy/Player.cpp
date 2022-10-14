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

// ---------------------------------------------------------------------------------

Player::Player(float scale)
{
	this->scale = scale;
	type = PLAYER;
	hp = 4;
    tileset = new TileSet("Resources/GravityGuy.png", 70, 80, 5, 5);
    anim = new Animation(tileset, 0.120f, true);
	
	uint moving[4] = { 1,2,3,4 };
	uint jump[1] = { 0 };
	uint idle[1] = { 0 };

	anim->Add(MOVE, moving, 4);
	anim->Add(IDLE, idle, 1);
	anim->Add(ATACK, idle, 1);
	anim->Add(JUMP, jump, 1);

    // cria bounding box
    BBox( new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));
    
    // inicializa estado do player
	state = IDLE;
	falling = false;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	shootTimer.Start();

    // posição inicial
    MoveTo( 200.0f * scale, ( 560.0f * scale ) - ( this->Height() / 2.0f ), Layer::MIDDLE);
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
	falling = false;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	shootTimer.Start();
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	if (obj->type == PLATFORM) {
		Platform* plat = (Platform*)obj;

		canJump = true;

		float botDiff = this->Bottom() - plat->Top();
		float rgtDiff = this->Right() - plat->Left();
		float lftDiff = this->Left() - plat->Right();

		if (rgtDiff < 0)
			rgtDiff = -rgtDiff;
		if (botDiff < 0)
			botDiff = -botDiff;
		if (lftDiff < 0)
			lftDiff = -lftDiff;


		if (plat->Type() != 11) {

			//right
			if (this->Right() >= plat->Left() && this->Left() < plat->Left() && botDiff > 30.0f * scale) {
				MoveTo((plat->Left() - this->Width() / 2.0f), y);
				right = false;
			}
			//left
			else if (this->Left() <= plat->Right() && this->Right() > plat->Right() && botDiff > 30.0f * scale) {
				MoveTo((plat->Right() + this->Width() / 2.0f), y);
				left = false;
			}
			//down
			else if (rgtDiff > 10.0f * scale && lftDiff > 10.0f * scale && botDiff <= 10.0f * scale) {
				if (state != JUMP)
					MoveTo(x, plat->Top() - (this->Height() / 2.0f));
				falling = false;
			}
		}
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (jumpTimer.Elapsed(0.4f)){
		state = IDLE;
	}
	else {
		canJump = false;//não pode pular novamente até finalizar o atual
	}
	
	// ----------------------------------------------------------
	// Processa teclas pressionadas
	// ----------------------------------------------------------

	if (state != JUMP) {
		if (right && (window->KeyDown(VK_RIGHT) || window->KeyDown('D' ))) {
			
			direction = true;
			
			//impede o jogador de atravessar a tela
			if (this->Right() < window->Width())
				Translate( GravityGuy::playerRgtVel * gameTime, 0 );

			state = MOVE;

		}
		else if (left && (window->KeyDown(VK_LEFT) || window->KeyDown('A' ))) {
			
			direction = false;

			//impede o jogador de atravessar a tela
			if (this->Left() > 0)
				Translate( -GravityGuy::playerLftVel * gameTime, 0 );
			
			state = MOVE;
		}
		else {
			state = IDLE;
		}

		//independente do estado, se o jogador apertar espaço, o boneco deve pular!!
		if (window->KeyPress(VK_SPACE) && canJump) {
			
			//setta estado do player
			state = JUMP;									
			jumpForce = PLAYER_VELOCITY * 2.0f;
			
			//inicia timer do pulo
			jumpTimer.Start();								
		}

		//detecção de disparo
		if ((window->KeyDown('Z') || window->KeyDown('K')) && shootTimer.Elapsed(0.5f)) {
			state = ATACK;
			shootTimer.Start();
			
			Bullet* bullet = nullptr;

			if (direction)
				bullet = new Bullet(true, this->scale);
			else
				bullet = new Bullet(false, this->scale);

			//verifica qual o level atual para decidir qual irá receber o objeto bullet
			if (GravityGuy::currentLvl == LEVEL_1 && bullet != nullptr)
				Level1::scene->Add(bullet, MOVING);
			else if (GravityGuy::currentLvl == BOSS_1 && bullet != nullptr)
				BossLVL1::scene->Add(bullet, MOVING);
		}
	}
	else if (state == JUMP) {
		Translate(0, -jumpForce * gameTime);
		falling = true; //pode cair, quando terminar o pulo

		//força do pulo vai decaindo a cada iteração
		jumpForce -= (PLAYER_VELOCITY / 2.0f) * gameTime;						

		//se estiver pulando, e, se mover em uma direção, vai alterar apenas a posição relativa
		if (right && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))) {
			
			direction = true;
			
			//impede o jogador de atravessar a tela
			if (this->Right() < window->Width())
				Translate(GravityGuy::playerRgtVel * gameTime, 0);
		}
		else if (left && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {
			
			direction = false;

			//impede o jogador de atravessar a tela
			if (this->Left() > 0)
				Translate(-GravityGuy::playerLftVel * gameTime, 0);
		}

		//detecção de disparo
		if ((window->KeyDown('Z') || window->KeyDown('K')) && shootTimer.Elapsed(0.5f)) {
			shootTimer.Start();

			Bullet* bullet = nullptr;

			if (direction)
				bullet = new Bullet(true, this->scale);
			else
				bullet = new Bullet(false, this->scale);

			//verifica qual o level atual para decidir qual irá receber o objeto bullet
			if (GravityGuy::currentLvl == LEVEL_1 && bullet != nullptr)
				Level1::scene->Add(bullet, MOVING);
			else if (GravityGuy::currentLvl == BOSS_1 && bullet != nullptr)
				BossLVL1::scene->Add(bullet, MOVING);
		}
	}

    if(state != JUMP && falling)
		// ação da gravidade sobre o personagem não afeta durante o pulo
		Translate(0, PLAYER_VELOCITY * 2.0f * gameTime);
	
	falling = true;
	right = true;
	left = true;

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------